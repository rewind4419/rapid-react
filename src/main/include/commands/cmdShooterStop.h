#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "sub/ballmng/ballmngShooter.h"
#include "RobotSettings.h"

class cmdShooterStop : public frc2::CommandHelper<frc2::CommandBase, cmdShooterStop> {
    public:
        cmdShooterStop();
        void Initialize() override;
        void Execute() override;
        void End(bool interrupted) override;
        bool IsFinished() override;
    private:
        ballmngShooter* subShooter;
};
