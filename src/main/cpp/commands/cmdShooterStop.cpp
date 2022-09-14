// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/cmdShooterStop.h"
#include "Robot.h"

cmdShooterStop::cmdShooterStop() {
    // Use addRequirements() here to declare subsystem dependencies.
    subShooter = Robot::GetInstance()->robotShooter;
    AddRequirements(subShooter);
}

// Called when the command is initially scheduled.
void cmdShooterStop::Initialize()
{
    subShooter->stop();
}

// Called repeatedly when this Command is scheduled to run
void cmdShooterStop::Execute() {}

// Called once the command ends or is interrupted.
void cmdShooterStop::End(bool interrupted)
{
}

// Returns true when the command should end.
bool cmdShooterStop::IsFinished() {
    return true;
}
