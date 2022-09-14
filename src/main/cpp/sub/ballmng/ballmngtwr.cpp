#include "ballmngtwr.h"
#include <frc/DriverStation.h>

ballmngtwr::ballmngtwr(unsigned int  motortopid, unsigned int motorbottomid)
// : motorids{towermotorid0, towermotorid1}
{
    twrmotortop = new rev::CANSparkMax(motortopid, rev::CANSparkMaxLowLevel::MotorType::kBrushless);
    // twrmotorbottom = new frc::PWMVictorSPX(motorbottomid);
    twrmotorbottom = new rev::CANSparkMax(motorbottomid, rev::CANSparkMaxLowLevel::MotorType::kBrushless);
 
    twrencodertop    = new rev::SparkMaxRelativeEncoder(twrmotortop->GetEncoder());
    twrencoderbottom = new rev::SparkMaxRelativeEncoder(twrmotorbottom->GetEncoder());
 
    twrcolor = new rev::ColorSensorV3(frc::I2C::Port::kOnboard);
    twrcolormatch = new rev::ColorMatch();

    twrcolormatch->SetConfidenceThreshold(0.9);

    // Add colors to the color matcher.
    twrcolormatch->AddColorMatch(kBlueTarget);
    twrcolormatch->AddColorMatch(kRedTarget);

    
    myThrottleTop = 0;
    myThrottleBottom = 0;
}

ballmngtwr::~ballmngtwr()
{
    delete twrmotortop;
    delete twrmotorbottom;
    delete twrcolor;
    delete twrcolormatch;
}

cargoStatus ballmngtwr::cargocheck()
{
    frc::Color myColorActual = twrcolor->GetColor();
    // printf("%lf, %lf, %lf\n", myColorActual.red, myColorActual.green, myColorActual.blue);
    std::optional<frc::Color> myColorMatched = twrcolormatch->MatchColor(myColorActual);

    // Check from Driver Station which alliance we're on
    frc::DriverStation::Alliance myDSAlliance = frc::DriverStation::GetAlliance();
    frc::Color myAlliance;
    frc::Color myOpponent;

    if (myDSAlliance == frc::DriverStation::Alliance::kRed)
    {
        myAlliance = kRedTarget;
        myOpponent = kBlueTarget;
    }
    else
    {
        myAlliance = kBlueTarget;
        myOpponent = kRedTarget;
    }

    // Determine what our cargo status is: Good (matches alliance), Bad (matches opponent), None (no match)
    cargoStatus myCargoStatus = cargoStatus::None;
    if (myColorMatched == myAlliance) myCargoStatus = cargoStatus::Good;
    if (myColorMatched == myOpponent) myCargoStatus = cargoStatus::Bad;

    return myCargoStatus;
}

void ballmngtwr::move(ballmngdir dir, float t_speedtop, float t_speedbottom)
{
    float mySpeedTop = dir * t_speedtop;
    float mySpeedBottom = -dir * t_speedbottom;


    float dt = 0.02;    
    // myThrottleTop    += EvaluatePid(&topPid, mySpeedTop - twrencodertop->GetVelocity(), dt) * dt;
    // myThrottleBottom += EvaluatePid(&bottomPid, mySpeedBottom - twrencoderbottom->GetVelocity(), dt) * dt;

    //
    // printf("twr top:    %f -> %f @@ %f\n", twrencodertop->GetVelocity(), mySpeedTop, myThrottleTop);
    // printf("twr bottom: %f -> %f @@ %f\n", twrencoderbottom->GetVelocity(), mySpeedBottom, myThrottleBottom);

    // Limit to [-1, 1]
    if (mySpeedBottom > 1) {mySpeedBottom = 1;}
    if (mySpeedBottom < -1) {mySpeedBottom = -1;}
    if (mySpeedTop > 1) {mySpeedTop = 1;}
    if (mySpeedTop < -1) {mySpeedTop = -1;}
    // Start motor
    twrmotortop->Set(mySpeedTop);
    twrmotorbottom->Set(mySpeedBottom);
}

void ballmngtwr::stop()
{
    twrmotortop->Set(0);
    twrmotorbottom->Set(0);
}
