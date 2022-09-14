// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/cmdIntakeForward.h"
#include "Robot.h"

cmdIntakeForward::cmdIntakeForward()
{
    // Use addRequirements() here to declare subsystem dependencies.
    subIntake = Robot::GetInstance()->robotIntake;
    AddRequirements(subIntake);
}
cmdIntakeForward::cmdIntakeForward(ballmngintake* t_subsystem) : subIntake(t_subsystem)
{
    // Use addRequirements() here to declare subsystem dependencies.
    AddRequirements(t_subsystem);
}

// Called when the command is initially scheduled.
void cmdIntakeForward::Initialize()
{
    subIntake->move(ballmngdir::IN, RobotSettings::IntakeMotorSpeedForward);
}

// Called repeatedly when this Command is scheduled to run
void cmdIntakeForward::Execute() {}

// Called once the command ends or is interrupted.
void cmdIntakeForward::End(bool interrupted)
{
    subIntake->stop();
}

// Returns true when the command should end.
bool cmdIntakeForward::IsFinished() {
    return false;
}
