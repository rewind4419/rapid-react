#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "sub/ballmng/ballmngHood.h"
// #include "RobotSettings.h"

class cmdHoodPosition : public frc2::CommandHelper<frc2::CommandBase, cmdHoodPosition> {
    public:
        cmdHoodPosition(float t_Target);
        void Initialize() override;
        void Execute() override;
        void End(bool interrupted) override;
        bool IsFinished() override;
    private:
        ballmngHood* subHood;
        float m_Target;
};
