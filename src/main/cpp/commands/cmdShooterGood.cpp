// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/cmdShooterGood.h"
#include "Robot.h"

cmdShooterGood::cmdShooterGood() {
    // Use addRequirements() here to declare subsystem dependencies.
    subShooter = Robot::GetInstance()->robotShooter;
    AddRequirements(subShooter);
}

// Called when the command is initially scheduled.
void cmdShooterGood::Initialize()
{
    subShooter->move(RobotSettings::ShooterSpeedGood);
}

// Called repeatedly when this Command is scheduled to run
void cmdShooterGood::Execute() {}

// Called once the command ends or is interrupted.
void cmdShooterGood::End(bool interrupted)
{
    subShooter->stop();
}

// Returns true when the command should end.
bool cmdShooterGood::IsFinished() {
    return false;
}
