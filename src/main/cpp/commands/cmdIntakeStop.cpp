// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/cmdIntakeStop.h"
#include "Robot.h"

cmdIntakeStop::cmdIntakeStop()
{
    // Use addRequirements() here to declare subsystem dependencies.
    subIntake = Robot::GetInstance()->robotIntake;
    AddRequirements(subIntake);
}
cmdIntakeStop::cmdIntakeStop(ballmngintake* t_subsystem) : subIntake(t_subsystem)
{
    // Use addRequirements() here to declare subsystem dependencies.
    AddRequirements(t_subsystem);
}

// Called when the command is initially scheduled.
void cmdIntakeStop::Initialize()
{
    subIntake->stop();
}

// Called repeatedly when this Command is scheduled to run
void cmdIntakeStop::Execute() {}

// Called once the command ends or is interrupted.
void cmdIntakeStop::End(bool interrupted)
{
}

// Returns true when the command should end.
bool cmdIntakeStop::IsFinished() {
    return true;
}
