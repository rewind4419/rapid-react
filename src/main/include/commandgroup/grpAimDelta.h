// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/ParallelCommandGroup.h>

class grpAimDelta
    : public frc2::CommandHelper<frc2::ParallelCommandGroup,
                                 grpAimDelta> {
 public:
  grpAimDelta(float t_TurretTargetDelta, float t_HoodTarget);
};