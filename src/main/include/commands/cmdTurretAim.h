#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "sub/ballmng/ballmngTurret.h"
#include "RobotSettings.h"

class cmdTurretAim : public frc2::CommandHelper<frc2::CommandBase, cmdTurretAim> {
    public:
        cmdTurretAim(float t_Target);
        void Initialize() override;
        void Execute() override;
        void End(bool interrupted) override;
        bool IsFinished() override;
    private:
        ballmngTurret* subTurret;
        float m_Speed;
        float m_Target;
        bool m_DirectionCW;
};
