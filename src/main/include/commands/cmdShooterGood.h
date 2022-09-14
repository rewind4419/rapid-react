#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "sub/ballmng/ballmngShooter.h"
#include "RobotSettings.h"

class cmdShooterGood : public frc2::CommandHelper<frc2::CommandBase, cmdShooterGood> {
    public:
        cmdShooterGood();
        void Initialize() override;
        void Execute() override;
        void End(bool interrupted) override;
        bool IsFinished() override;
    private:
        ballmngShooter* subShooter;
};
