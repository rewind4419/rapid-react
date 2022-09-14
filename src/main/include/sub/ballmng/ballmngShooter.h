#pragma once
#include <frc2/command/SubsystemBase.h>
#include "rev/CANSparkMax.h"

#include "pid.h"

class ballmngShooter : public frc2::SubsystemBase
{
    public: 
        ballmngShooter(unsigned int motorid0, unsigned int motorid1);
        ~ballmngShooter();
        void move(float t_speed);
        void stop();
        void Periodic() override;

    private:
        float myThrottle = 0;
        PID pid = { 0.00035, 0, 0 };
        rev::CANSparkMax* shooterMotor0;
        rev::CANSparkMax* shooterMotor1;
        rev::SparkMaxRelativeEncoder* encoder0;
        rev::SparkMaxRelativeEncoder* encoder1;
};
