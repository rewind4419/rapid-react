// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.
#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/Servo.h>

class ballmngHood : public frc2::SubsystemBase
{
    public:
        ballmngHood(int t_HoodChannel /*, int t_HoodRightChannel */);
        ~ballmngHood();

        /**
         * Will be called periodically whenever the CommandScheduler runs.
         */
        void Periodic() override;
        void Set(float t_percent);

    private:
    // Components (e.g. motor controllers and sensors) should generally be
    // declared private and exposed only through public methods.
        frc::Servo* servoHood; //Left;
        // frc::Servo* servoHoodRight;
};
