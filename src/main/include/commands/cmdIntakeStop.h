#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "../cpp/sub/ballmng/ballmngintake.h"
#include "RobotSettings.h"

class cmdIntakeStop : public frc2::CommandHelper<frc2::CommandBase, cmdIntakeStop> {
    public:
        cmdIntakeStop();
        cmdIntakeStop(ballmngintake* subsystem);
        void Initialize() override;
        void Execute() override;
        void End(bool interrupted) override;
        bool IsFinished() override;
    private:
        ballmngintake* subIntake;
};
