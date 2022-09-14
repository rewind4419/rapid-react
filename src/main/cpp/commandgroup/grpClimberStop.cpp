// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commandgroup/grpClimberStop.h"
#include "commands/cmdClimberStop.h"

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/stable/docs/software/commandbased/convenience-features.html
grpClimberStop::grpClimberStop() {
  // Add your commands here, e.g.
  // AddCommands(FooCommand(), BarCommand());
  subClimber* subLeft = Robot::GetInstance()->robotClimberLeft;
  subClimber* subRight = Robot::GetInstance()->robotClimberRight;
  AddCommands(cmdClimberStop(subLeft), cmdClimberStop(subRight));
}
