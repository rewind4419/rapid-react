// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "sub/ballmng/ballmngHood.h"
#include <frc/Servo.h>

ballmngHood::ballmngHood(int t_HoodChannel /*, int t_HoodRightChannel */)
{
    servoHood = new frc::Servo(t_HoodChannel);
    // servoHoodRight = new frc::Servo(t_HoodRightChannel);
    servoHood->SetBounds(2.0, 1.8, 1.5, 1.2, 1.0);
    // servoHoodRight->SetBounds(2.0, 1.8, 1.5, 1.2, 1.0);
}
ballmngHood::~ballmngHood()
{
    delete servoHood; //Left;
    // delete servoHoodRight;
}

// This method will be called once per scheduler run
void ballmngHood::Periodic() {}

void ballmngHood::Set(float t_percent)
{
    // Left
    servoHood->Set(t_percent);
    // servoHoodRight->Set(t_percent);
}
