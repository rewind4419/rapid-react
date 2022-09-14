// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/cmdHopperStop.h"
#include "Robot.h"

cmdHopperStop::cmdHopperStop()
{
    // Use addRequirements() here to declare subsystem dependencies.
    subHopper = Robot::GetInstance()->robotHopper;
    AddRequirements(subHopper);
}
cmdHopperStop::cmdHopperStop(ballmnghopper* t_subsystem) : subHopper(t_subsystem)
{
    // Use addRequirements() here to declare subsystem dependencies.
    AddRequirements(t_subsystem);
}

// Called when the command is initially scheduled.
void cmdHopperStop::Initialize()
{
    subHopper->stop();
}

// Called repeatedly when this Command is scheduled to run
void cmdHopperStop::Execute() {}

// Called once the command ends or is interrupted.
void cmdHopperStop::End(bool interrupted)
{
}

// Returns true when the command should end.
bool cmdHopperStop::IsFinished() {
    return true;
}
