#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "sub/ballmng/ballmngTurret.h"
#include "RobotSettings.h"

class cmdTurretLeft : public frc2::CommandHelper<frc2::CommandBase, cmdTurretLeft> {
    public:
        cmdTurretLeft(bool t_init);
        void Initialize() override;
        void Execute() override;
        void End(bool interrupted) override;
        bool IsFinished() override;
    private:
        ballmngTurret* subTurret;
        float m_Speed;
};
