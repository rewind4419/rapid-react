// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/cmdTowerIntakeReverse.h"
#include "Robot.h"

cmdTowerIntakeReverse::cmdTowerIntakeReverse()
{
    // Use addRequirements() here to declare subsystem dependencies.
    subTowerIntake = Robot::GetInstance()->robotTower;
    AddRequirements(subTowerIntake);
}
cmdTowerIntakeReverse::cmdTowerIntakeReverse(ballmngtwr* t_subsystem) : subTowerIntake(t_subsystem)
{
    // Use addRequirements() here to declare subsystem dependencies.
    AddRequirements(t_subsystem);
}

// Called when the command is initially scheduled.
void cmdTowerIntakeReverse::Initialize()
{
    subTowerIntake->move(ballmngdir::OUT, RobotSettings::TowerIntakeMotorTopSpeedReverse, RobotSettings::TowerIntakeMotorBottomSpeedReverse);
}

// Called repeatedly when this Command is scheduled to run
void cmdTowerIntakeReverse::Execute() {}

// Called once the command ends or is interrupted.
void cmdTowerIntakeReverse::End(bool interrupted)
{
    subTowerIntake->stop();
}

// Returns true when the command should end.
bool cmdTowerIntakeReverse::IsFinished() {
    return false;
}
