// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/cmdTurretRight.h"
#include "Robot.h"

cmdTurretRight::cmdTurretRight(bool t_init = false) {
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
void cmdTurretRight::Initialize()
{
    subTurret->Move(m_Speed);
}

// Called repeatedly when this Command is scheduled to run
void cmdTurretRight::Execute() {}

// Called once the command ends or is interrupted.
void cmdTurretRight::End(bool interrupted)
{
    subTurret->Stop();
    // if (not interrupted)
    // {
    //     subTurret->SetEncoderRight();
    // }
}

// Returns true when the command should end.
bool cmdTurretRight::IsFinished() {
    return subTurret->GetRightLS();
}
