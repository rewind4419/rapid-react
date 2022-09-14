#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "../cpp/sub/ballmng/ballmngintake.h"
#include "RobotSettings.h"

class cmdIntakeReverse : public frc2::CommandHelper<frc2::CommandBase, cmdIntakeReverse> {
    public:
        cmdIntakeReverse();
        cmdIntakeReverse(ballmngintake* subsystem);
        void Initialize() override;
        void Execute() override;
        void End(bool interrupted) override;
        bool IsFinished() override;
    private:
        ballmngintake* subIntake;
};
