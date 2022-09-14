// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/cmdTowerIntakeForward.h"
#include "Robot.h"

cmdTowerIntakeForward::cmdTowerIntakeForward()
{
    // Use addRequirements() here to declare subsystem dependencies.
    subTowerIntake = Robot::GetInstance()->robotTower;
    AddRequirements(subTowerIntake);
}
cmdTowerIntakeForward::cmdTowerIntakeForward(ballmngtwr* t_subsystem) : subTowerIntake(t_subsystem)
{
    // Use addRequirements() here to declare subsystem dependencies.
    AddRequirements(t_subsystem);
}

// Called when the command is initially scheduled.
void cmdTowerIntakeForward::Initialize()
{
    subTowerIntake->move(ballmngdir::IN, RobotSettings::TowerIntakeMotorTopSpeedForward, RobotSettings::TowerIntakeMotorBottomSpeedForward);
}

// Called repeatedly when this Command is scheduled to run
void cmdTowerIntakeForward::Execute() {}

// Called once the command ends or is interrupted.
void cmdTowerIntakeForward::End(bool interrupted)
{
    subTowerIntake->stop();
}

// Returns true when the command should end.
bool cmdTowerIntakeForward::IsFinished() {
    return (subTowerIntake->cargocheck() != cargoStatus::None);
}
