#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "../cpp/sub/ballmng/ballmngtwr.h"
#include "RobotSettings.h"

class cmdTowerIntakeReverse : public frc2::CommandHelper<frc2::CommandBase, cmdTowerIntakeReverse> {
    public:
        cmdTowerIntakeReverse();
        cmdTowerIntakeReverse(ballmngtwr* subsystem);
        void Initialize() override;
        void Execute() override;
        void End(bool interrupted) override;
        bool IsFinished() override;
    private:
        ballmngtwr* subTowerIntake;
};
