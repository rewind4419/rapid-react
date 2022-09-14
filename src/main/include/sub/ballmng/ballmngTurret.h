#pragma once

#include <frc2/command/SubsystemBase.h>
#include "rev/CANSparkMax.h"
#include "rev/SparkMaxLimitSwitch.h"
#include <frc/DigitalInput.h>
#include "pid.h"
// #include "rev/CANDigitalInput.h"

class ballmngTurret : public frc2::SubsystemBase {
    public:
        // Limit switches will be connected directly to the motor controller
        ballmngTurret(unsigned int motortopid, unsigned int leftLSid, unsigned int rightLSid);
        // ballmngTurret(unsigned int motortopid);
        ~ballmngTurret();

        void Periodic() override;
        float GetPositionPercent();
        int GetPosition();
        bool GetLeftLS();
        bool GetRightLS();
        void Move(float t_speed);
        void Stop();
        void SetEncoderLeft();
        void SetEncoderRight();

        void DoInitialization();
        void DoAim();

        float aim;

        void PushBackToCenterIfOutOfBounds();

        bool isInitialized;
        bool initLeft;

    private:
        PID initPid = { 0.02, 0.0, 0.0 };
        float initThrottle;
        PID aimPid = { 0.05, 0.005, 0.0 };
        
        rev::CANSparkMax* turretMotor;
        // Limit switches will be connected directly to the motor controller
        frc::DigitalInput* turretLSleft;
        frc::DigitalInput* turretLSright;
        // rev::SparkMaxLimitSwitch turretLSleft {turretMotor->GetReverseLimitSwitch(rev::SparkMaxLimitSwitch::Type::kNormallyClosed)};
        // rev::SparkMaxLimitSwitch turretLSright {turretMotor->GetForwardLimitSwitch(rev::SparkMaxLimitSwitch::Type::kNormallyClosed)};
        // rev::SparkMaxRelativeEncoder turretEncoder {turretMotor->GetEncoder(rev::SparkMaxRelativeEncoder::Type::kQuadrature, 8192)};
        // rev::SparkMaxLimitSwitch* turretLSleft;
        // rev::SparkMaxLimitSwitch* turretLSright;
        rev::SparkMaxRelativeEncoder* turretEncoder;
        int turretEncoderLeft = -999999;
        int turretEncoderRight = 999999;
};
