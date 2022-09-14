#pragma once
#include <frc2/command/SubsystemBase.h>
// #include <frc/motorcontrol/PWMVictorSPX.h>
#include <frc/DigitalInput.h>

#include <ctre/phoenix/motorcontrol/can/VictorSPX.h>
// woah
using namespace ctre::phoenix::motorcontrol::can;
using namespace ctre::phoenix::motorcontrol;


class subClimber : public frc2::SubsystemBase
{
    public: 
        subClimber(unsigned int motorid, unsigned int LSid, float upMultiplier);
        ~subClimber();
        void move(float t_speed);
        void stop();
        // true == limit switch activated, false == no magnet force
        bool check(); 
        void Periodic() override;

    private:
        float upMultiplier;
        VictorSPX* climberMotor;
        frc::DigitalInput* climberLS;
};
