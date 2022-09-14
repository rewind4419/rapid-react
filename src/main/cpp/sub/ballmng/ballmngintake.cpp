#include "ballmngintake.h"
#include "RobotMap.h"
#include <chrono>
#include <thread>

#include <frc/smartdashboard/SmartDashboard.h>

ballmngintake::ballmngintake(unsigned int motorid, unsigned int solenoid_extend_id, unsigned int solenoid_retract_id)
: intakemotorid(motorid), intakesolenoid_extend_id(solenoid_extend_id), intakesolenoid_retract_id(solenoid_retract_id)
{
    intakemotor = new rev::CANSparkMax(motorid, rev::CANSparkMaxLowLevel::MotorType::kBrushless);
    intakesolenoid = new frc::DoubleSolenoid(RobotMap::canPCM, frc::PneumaticsModuleType::CTREPCM, solenoid_extend_id, solenoid_retract_id);
    intakemotorSAFE = false;

    intakeencoder = new rev::SparkMaxRelativeEncoder(intakemotor->GetEncoder());

    InitPid(&pid);
    myThrottle = 0;
}

ballmngintake::~ballmngintake()
{
    delete intakemotor;
    delete intakesolenoid;
    delete intakeencoder;
}

void ballmngintake::move(ballmngdir dir, float t_speed)
{
    float mySpeed = -dir * t_speed;

    float dt = 0.02;

    // ~Todo global delta time variable
    myThrottle += EvaluatePid(&pid, mySpeed - intakeencoder->GetVelocity(), dt) * dt;

    // printf("intake:    %f -> %f @@ %f\n", intakeencoder->GetVelocity(), mySpeed, myThrottle);

    // Limit to [-1, 1]
    if (myThrottle > 1) {myThrottle = 1;}
    if (myThrottle < -1) {myThrottle = -1;}

    // Extend
    intakesolenoid->Set(frc::DoubleSolenoid::kForward);
    // If not already extended, wait a beat before starting motors
    if (!intakemotorSAFE)
    {
        //Delay a beat to allow the solenoid to extend
        // std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    intakemotorSAFE = true;
    // Start motor
    intakemotor->Set(myThrottle); 
}
void ballmngintake::stop()
{
    // Stop motor
    intakemotor->Set(0);
    // Retract
    intakesolenoid->Set(frc::DoubleSolenoid::kReverse);
    intakemotorSAFE = false;
}
