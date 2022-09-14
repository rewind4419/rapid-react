#pragma once
#include "ballmngcore.h"
#include <frc2/command/SubsystemBase.h>
#include <frc/motorcontrol/PWMVictorSPX.h>
#include "rev/CANSparkMax.h"
#include "rev/ColorSensorV3.h"
#include "rev/ColorMatch.h"

#include "pid.h"

class ballmngtwr : public frc2::SubsystemBase
{
public:
    ballmngtwr(unsigned int motortopid, unsigned int motorbottomid); //sets motorids
    ~ballmngtwr(); //deinits and frees the motorids
    void move(ballmngdir dir, float t_speedtop, float t_speedbottom); // Just moves the ball in the tower
    void stop();
    cargoStatus cargocheck();

private: 
    // int motorids[2];
    // float speed;
    rev::CANSparkMax* twrmotortop;
    rev::CANSparkMax* twrmotorbottom;
    rev::SparkMaxRelativeEncoder* twrencodertop;
    rev::SparkMaxRelativeEncoder* twrencoderbottom;
    // frc::PWMVictorSPX* twrmotorbottom;
    rev::ColorSensorV3* twrcolor;
    rev::ColorMatch* twrcolormatch;

    frc::Color kRedTarget = frc::Color(0.45, 0.39, 0.17);
    frc::Color kBlueTarget = frc::Color(0.17, 0.45, 0.39);

    PID topPid = { 0.0001, 0, 0 };
    PID bottomPid = { 0.0001, 0, 0 };

    float myThrottleTop;
    float myThrottleBottom;
};
