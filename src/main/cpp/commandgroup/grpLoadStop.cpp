// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commandgroup/grpLoadStop.h"
#include "commands/cmdIntakeStop.h"
#include "commands/cmdHopperStop.h"
#include "commands/cmdTowerStop.h"

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/stable/docs/software/commandbased/convenience-features.html
grpLoadStop::grpLoadStop() {
  // Add your commands here, e.g.
  // AddCommands(FooCommand(), BarCommand());
  AddCommands(cmdIntakeStop(), cmdHopperStop(), cmdTowerStop());
}
