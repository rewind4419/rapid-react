// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/cmdHopperForward.h"
#include "Robot.h"

cmdHopperForward::cmdHopperForward()
{
    // Use addRequirements() here to declare subsystem dependencies.
    subHopper = Robot::GetInstance()->robotHopper;
    AddRequirements(subHopper);
}
cmdHopperForward::cmdHopperForward(ballmnghopper* t_subsystem) : subHopper(t_subsystem)
{
    // Use addRequirements() here to declare subsystem dependencies.
    AddRequirements(t_subsystem);
}

// Called when the command is initially scheduled.
void cmdHopperForward::Initialize()
{
    subHopper->move(ballmngdir::IN, RobotSettings::HopperMotorSpeedForward);
}

// Called repeatedly when this Command is scheduled to run
void cmdHopperForward::Execute() {}

// Called once the command ends or is interrupted.
void cmdHopperForward::End(bool interrupted)
{
    subHopper->stop();
}

// Returns true when the command should end.
bool cmdHopperForward::IsFinished() {
    return false;
}
