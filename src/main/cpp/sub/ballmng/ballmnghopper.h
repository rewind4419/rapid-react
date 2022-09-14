#pragma once
#include "ballmngcore.h"
#include <frc2/command/SubsystemBase.h>
#include "rev/CANSparkMax.h"
#include "pid.h"

class ballmnghopper : public frc2::SubsystemBase
{
    public: 
    ballmnghopper(unsigned int motorid);
    ~ballmnghopper();
    void move(ballmngdir dir, float t_speed);
    void stop();

    private:
    // unsigned int hoppermotorid;
    // float speed = 0; // this needs to change again
    rev::CANSparkMax* hoppermotor;
    rev::SparkMaxRelativeEncoder* hopperencoder;
    PID pid = { 0.001, 0.0, 0.0 };

    float myThrottle;
};