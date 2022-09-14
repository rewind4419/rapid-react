// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/cmdTurretStop.h"
#include "Robot.h"

cmdTurretStop::cmdTurretStop() {
    // Use addRequirements() here to declare subsystem dependencies.
    subTurret = Robot::GetInstance()->robotTurret;
    AddRequirements(subTurret);
}

// Called when the command is initially scheduled.
void cmdTurretStop::Initialize()
{
    subTurret->Stop();
}

// Called repeatedly when this Command is scheduled to run
void cmdTurretStop::Execute() {}

// Called once the command ends or is interrupted.
void cmdTurretStop::End(bool interrupted)
{
}

// Returns true when the command should end.
bool cmdTurretStop::IsFinished() {
    return true;
}
