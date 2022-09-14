#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "../cpp/sub/ballmng/ballmnghopper.h"
#include "RobotSettings.h"

class cmdHopperStop : public frc2::CommandHelper<frc2::CommandBase, cmdHopperStop> {
    public:
        cmdHopperStop();
        cmdHopperStop(ballmnghopper* subsystem);
        void Initialize() override;
        void Execute() override;
        void End(bool interrupted) override;
        bool IsFinished() override;
    private:
        ballmnghopper* subHopper;
};
