// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/cmdTowerShooterForward.h"
#include "Robot.h"

cmdTowerShooterForward::cmdTowerShooterForward()
{
    // Use addRequirements() here to declare subsystem dependencies.
    subTowerShooter = Robot::GetInstance()->robotTower;
    AddRequirements(subTowerShooter);
}
cmdTowerShooterForward::cmdTowerShooterForward(ballmngtwr* t_subsystem) : subTowerShooter(t_subsystem)
{
    // Use addRequirements() here to declare subsystem dependencies.
    AddRequirements(t_subsystem);
}

// Called when the command is initially scheduled.
void cmdTowerShooterForward::Initialize()
{
    subTowerShooter->move(ballmngdir::IN, RobotSettings::TowerShooterMotorTopSpeedForward, RobotSettings::TowerShooterMotorBottomSpeedForward);
}

// Called repeatedly when this Command is scheduled to run
void cmdTowerShooterForward::Execute() {}

// Called once the command ends or is interrupted.
void cmdTowerShooterForward::End(bool interrupted)
{
    subTowerShooter->stop();
}

// Returns true when the command should end.
bool cmdTowerShooterForward::IsFinished() {
    return false;
}
