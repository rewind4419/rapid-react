#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "sub/climber/subClimber.h"

class cmdClimberStop : public frc2::CommandHelper<frc2::CommandBase, cmdClimberStop> {
    public:
        cmdClimberStop(subClimber* t_subsystem);
        void Initialize() override;
        void Execute() override;
        void End(bool interrupted) override;
        bool IsFinished() override;
    private:
        subClimber* subSystem;
};
