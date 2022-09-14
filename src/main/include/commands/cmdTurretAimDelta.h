#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "sub/ballmng/ballmngTurret.h"
#include "RobotSettings.h"

class cmdTurretAimDelta : public frc2::CommandHelper<frc2::CommandBase, cmdTurretAimDelta> {
    public:
        cmdTurretAimDelta(float t_TargetDelta);
        void Initialize() override;
        void Execute() override;
        void End(bool interrupted) override;
        bool IsFinished() override;
    private:
        ballmngTurret* subTurret;
        float m_Initial;
        float m_Speed;
        float m_Target;
        bool m_DirectionCW;
};
