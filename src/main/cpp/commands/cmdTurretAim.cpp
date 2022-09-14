// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/cmdTurretAim.h"
#include "Robot.h"

cmdTurretAim::cmdTurretAim(float t_Target) {
    // Use addRequirements() here to declare subsystem dependencies.
    subTurret = Robot::GetInstance()->robotTurret;
    AddRequirements(subTurret);

    m_Target = t_Target;
    m_Speed = RobotSettings::TurretSpeed;
    m_DirectionCW = true;
    if (m_Target < subTurret->GetPositionPercent()) {
        m_Speed = -m_Speed;
        m_DirectionCW = false;
    }
}

// Called when the command is initially scheduled.
void cmdTurretAim::Initialize()
{
    subTurret->Move(m_Speed);
}

// Called repeatedly when this Command is scheduled to run
void cmdTurretAim::Execute() {}

// Called once the command ends or is interrupted.
void cmdTurretAim::End(bool interrupted)
{
    subTurret->Stop();
}

// Returns true when the command should end.
bool cmdTurretAim::IsFinished() {
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
