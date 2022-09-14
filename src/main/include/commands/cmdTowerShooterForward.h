#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "../cpp/sub/ballmng/ballmngtwr.h"
#include "RobotSettings.h"

class cmdTowerShooterForward : public frc2::CommandHelper<frc2::CommandBase, cmdTowerShooterForward> {
    public:
        cmdTowerShooterForward();
        cmdTowerShooterForward(ballmngtwr* subsystem);
        void Initialize() override;
        void Execute() override;
        void End(bool interrupted) override;
        bool IsFinished() override;
    private:
        ballmngtwr* subTowerShooter;
};
