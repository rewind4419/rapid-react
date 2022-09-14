// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/cmdHoodPosition.h"
#include "Robot.h"

cmdHoodPosition::cmdHoodPosition(float t_Target) {
    // Use addRequirements() here to declare subsystem dependencies.
    subHood = Robot::GetInstance()->robotHood;
    AddRequirements(subHood);

    m_Target = t_Target;
}

// Called when the command is initially scheduled.
void cmdHoodPosition::Initialize()
{
    subHood->Set(m_Target);
}

// Called repeatedly when this Command is scheduled to run
void cmdHoodPosition::Execute() {}

// Called once the command ends or is interrupted.
void cmdHoodPosition::End(bool interrupted) {}

// Returns true when the command should end.
bool cmdHoodPosition::IsFinished() {
    return true;
}
