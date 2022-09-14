#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "../cpp/sub/ballmng/ballmngintake.h"
#include "RobotSettings.h"

class cmdIntakeForward : public frc2::CommandHelper<frc2::CommandBase, cmdIntakeForward> {
    public:
        cmdIntakeForward();
        cmdIntakeForward(ballmngintake* subsystem);
        void Initialize() override;
        void Execute() override;
        void End(bool interrupted) override;
        bool IsFinished() override;
    private:
        ballmngintake* subIntake;
};
