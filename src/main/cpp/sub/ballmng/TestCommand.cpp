// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "sub/ballmng/TestCommand.h"

TestCommand::TestCommand() {
  // Use addRequirements() here to declare subsystem dependencies.
  subTurret = Robot::GetInstance()->robotTurret;
  AddRequirements(subTurret);
}

// Called when the command is initially scheduled.
void TestCommand::Initialize() {
  printf("Command executed!\n");
    // subTurret->Move(RobotSettings::TurretSpeed);
  printf("Initialize %d position of turret\n", 0);

}

// Called repeatedly when this Command is scheduled to run
void TestCommand::Execute() {
  printf("Execute %d position of turret\n", subTurret->GetPosition());

}

// Called once the command ends or is interrupted.
void TestCommand::End(bool interrupted) {
  // subTurret->Stop();
  printf("End %d position of turret\n", subTurret->GetPosition());
}

// Returns true when the command should end.
bool TestCommand::IsFinished() {
  return false;
}
