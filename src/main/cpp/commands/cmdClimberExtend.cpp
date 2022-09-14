// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/cmdClimberExtend.h"
#include <chrono>

cmdClimberExtend::cmdClimberExtend(subClimber* t_subsystem) : subSystem(t_subsystem)
{
    // Use addRequirements() here to declare subsystem dependencies.
    AddRequirements(t_subsystem);
}

// Called when the command is initially scheduled.
void cmdClimberExtend::Initialize()
{
    subSystem->move(RobotSettings::ClimberSpeedExtend);
    chronoStart = std::chrono::steady_clock::now();
}

// Called repeatedly when this Command is scheduled to run
void cmdClimberExtend::Execute() {}

// Called once the command ends or is interrupted.
void cmdClimberExtend::End(bool interrupted)
{
    subSystem->stop();
}

// Returns true when the command should end.
bool cmdClimberExtend::IsFinished() {
    // Since we expect to start with the limit switch active, 
    // let's give the motor the chance to move beyond the limit switch (hopefully in the right direction).
    std::chrono::steady_clock::time_point chronoStop = std::chrono::steady_clock::now();
    int64_t chronoElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(chronoStop - chronoStart).count();

    // Check the limit switch status only after we've been running the motor for a little bit.
    return (chronoElapsed >= m_MilliDelay) && subSystem->check();
}
