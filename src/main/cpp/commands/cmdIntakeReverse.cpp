// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/cmdIntakeReverse.h"
#include "Robot.h"

cmdIntakeReverse::cmdIntakeReverse()
{
    // Use addRequirements() here to declare subsystem dependencies.
    subIntake = Robot::GetInstance()->robotIntake;
    AddRequirements(subIntake);
}
cmdIntakeReverse::cmdIntakeReverse(ballmngintake* t_subsystem) : subIntake(t_subsystem)
{
    // Use addRequirements() here to declare subsystem dependencies.
    AddRequirements(t_subsystem);
}

// Called when the command is initially scheduled.
void cmdIntakeReverse::Initialize()
{
    subIntake->move(ballmngdir::OUT, RobotSettings::IntakeMotorSpeedReverse);
}

// Called repeatedly when this Command is scheduled to run
void cmdIntakeReverse::Execute() {}

// Called once the command ends or is interrupted.
void cmdIntakeReverse::End(bool interrupted)
{
    subIntake->stop();
}

// Returns true when the command should end.
bool cmdIntakeReverse::IsFinished() {
    return false;
}
