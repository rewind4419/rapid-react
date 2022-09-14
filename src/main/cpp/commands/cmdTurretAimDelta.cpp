// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/cmdTurretAimDelta.h"
#include "Robot.h"

cmdTurretAimDelta::cmdTurretAimDelta(float t_TargetDelta) {
    // Use addRequirements() here to declare subsystem dependencies.
    subTurret = Robot::GetInstance()->robotTurret;
    AddRequirements(subTurret);

    m_Initial = subTurret->GetPositionPercent();
    m_Target = m_Initial + t_TargetDelta;
    m_Speed = RobotSettings::TurretSpeed;
    m_DirectionCW = true;
    if (m_Target < subTurret->GetPositionPercent()) {
        m_Speed = -m_Speed;
        m_DirectionCW = false;
    }
}

// Called when the command is initially scheduled.
void cmdTurretAimDelta::Initialize()
{
    subTurret->Move(m_Speed);
}

// Called repeatedly when this Command is scheduled to run
void cmdTurretAimDelta::Execute() {}

// Called once the command ends or is interrupted.
void cmdTurretAimDelta::End(bool interrupted)
{
    subTurret->Stop();
}

// Returns true when the command should end.
bool cmdTurretAimDelta::IsFinished() {
    bool myReturn = 
        ((m_DirectionCW == true) && (
            (subTurret->GetPositionPercent() >= m_Target)
            ||
            (subTurret->GetRightLS())
        ))
        || 
        ((m_DirectionCW == false) && (
            (subTurret->GetPositionPercent() <= m_Target)
            ||
            (subTurret->GetLeftLS())
        ));
    return myReturn;
}
