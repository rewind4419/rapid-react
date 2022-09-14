// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/cmdTowerStop.h"
#include "Robot.h"

cmdTowerStop::cmdTowerStop()
{
    // Use addRequirements() here to declare subsystem dependencies.
    subTower = Robot::GetInstance()->robotTower;
    AddRequirements(subTower);
}
cmdTowerStop::cmdTowerStop(ballmngtwr* t_subsystem) : subTower(t_subsystem)
{
    // Use addRequirements() here to declare subsystem dependencies.
    AddRequirements(t_subsystem);
}

// Called when the command is initially scheduled.
void cmdTowerStop::Initialize()
{
    subTower->stop();
}

// Called repeatedly when this Command is scheduled to run
void cmdTowerStop::Execute() {}

// Called once the command ends or is interrupted.
void cmdTowerStop::End(bool interrupted)
{
}

// Returns true when the command should end.
bool cmdTowerStop::IsFinished() {
    return true;
}
