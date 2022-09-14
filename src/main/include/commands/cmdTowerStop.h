#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "../cpp/sub/ballmng/ballmngtwr.h"
#include "RobotSettings.h"

class cmdTowerStop : public frc2::CommandHelper<frc2::CommandBase, cmdTowerStop> {
    public:
        cmdTowerStop();
        cmdTowerStop(ballmngtwr* subsystem);
        void Initialize() override;
        void Execute() override;
        void End(bool interrupted) override;
        bool IsFinished() override;
    private:
        ballmngtwr* subTower;
};
