#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "sub/climber/subClimber.h"
#include "RobotSettings.h"

class cmdClimberExtend : public frc2::CommandHelper<frc2::CommandBase, cmdClimberExtend> {
    public:
        cmdClimberExtend(subClimber* t_subsystem);
        void Initialize() override;
        void Execute() override;
        void End(bool interrupted) override;
        bool IsFinished() override;
    private:
        subClimber* subSystem;
        std::chrono::steady_clock::time_point chronoStart;
        int64_t m_MilliDelay = 500;
};
