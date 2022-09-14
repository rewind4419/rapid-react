// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/cmdHopperReverse.h"
#include "Robot.h"

cmdHopperReverse::cmdHopperReverse()
{
    // Use addRequirements() here to declare subsystem dependencies.
    subHopper = Robot::GetInstance()->robotHopper;
    AddRequirements(subHopper);
}
cmdHopperReverse::cmdHopperReverse(ballmnghopper* t_subsystem) : subHopper(t_subsystem)
{
    // Use addRequirements() here to declare subsystem dependencies.
    AddRequirements(t_subsystem);
}

// Called when the command is initially scheduled.
void cmdHopperReverse::Initialize()
{
    subHopper->move(ballmngdir::OUT, RobotSettings::HopperMotorSpeedReverse);
}

// Called repeatedly when this Command is scheduled to run
void cmdHopperReverse::Execute() {}

// Called once the command ends or is interrupted.
void cmdHopperReverse::End(bool interrupted)
{
    subHopper->stop();
}

// Returns true when the command should end.
bool cmdHopperReverse::IsFinished() {
    return false;
}
