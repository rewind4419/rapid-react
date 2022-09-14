// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commandgroup/grpAim.h"
#include "commands/cmdTurretAim.h"
#include "commands/cmdHoodPosition.h"

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/stable/docs/software/commandbased/convenience-features.html
grpAim::grpAim(float t_TurretTarget, float t_HoodTarget) {
  // Add your commands here, e.g.
  // AddCommands(FooCommand(), BarCommand());
  AddCommands(cmdTurretAim(t_TurretTarget), cmdHoodPosition(t_HoodTarget));
}
