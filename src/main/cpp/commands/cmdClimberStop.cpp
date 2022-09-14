// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/cmdClimberStop.h"

cmdClimberStop::cmdClimberStop(subClimber* t_subsystem) : subSystem(t_subsystem)
{
    // Use addRequirements() here to declare subsystem dependencies.
    AddRequirements(t_subsystem);
}

// Called when the command is initially scheduled.
void cmdClimberStop::Initialize()
{
    subSystem->stop();
}

// Called repeatedly when this Command is scheduled to run
void cmdClimberStop::Execute() {}

// Called once the command ends or is interrupted.
void cmdClimberStop::End(bool interrupted)
{
}

// Returns true when the command should end.
bool cmdClimberStop::IsFinished() {
    return true;
}
