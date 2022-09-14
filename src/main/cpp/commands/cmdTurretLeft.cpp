// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/cmdTurretLeft.h"
#include "Robot.h"

cmdTurretLeft::cmdTurretLeft(bool t_init = false) {
    // Use addRequirements() here to declare subsystem dependencies.
    subTurret = Robot::GetInstance()->robotTurret;
    AddRequirements(subTurret);

    if (t_init)
    {
        m_Speed = RobotSettings::TurretSpeedInitialization;
    }
    else
    {
        m_Speed = RobotSettings::TurretSpeed;
    }
}

// Called when the command is initially scheduled.
void cmdTurretLeft::Initialize()
{
    subTurret->Move(-m_Speed);
}

// Called repeatedly when this Command is scheduled to run
void cmdTurretLeft::Execute() {}

// Called once the command ends or is interrupted.
void cmdTurretLeft::End(bool interrupted)
{
    subTurret->Stop();
    // if (not interrupted)
    // {
    //     subTurret->SetEncoderLeft();
    // }
}

// Returns true when the command should end.
bool cmdTurretLeft::IsFinished() {
    return subTurret->GetLeftLS();
}
