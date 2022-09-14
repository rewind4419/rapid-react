#include "sub/climber/subClimber.h"



subClimber::subClimber(unsigned int motorid, unsigned int LSid, float upMultiplier)
{
    // ~BeforeRun
    climberMotor = new VictorSPX(motorid);
    this->upMultiplier = upMultiplier;
    climberLS = new frc::DigitalInput(LSid);
}
subClimber::~subClimber()
{
    delete climberMotor;
    delete climberLS;
}
void subClimber::Periodic() {}
void subClimber::move(float t_speed)
{
    float mySpeed = t_speed * upMultiplier;

    if (check()) {
        if (t_speed < 0)
            mySpeed = 0;
    }

    // Limit to [-1, 1]
    if (mySpeed > 1) {mySpeed = 1;}
    if (mySpeed < -1) {mySpeed = -1;}

    // ~Todo subsystem use check to stop moving down

    // Start motor
    climberMotor->Set(ControlMode::PercentOutput, mySpeed);
}
void subClimber::stop()
{
    climberMotor->Set(ControlMode::PercentOutput, 0);
}
bool subClimber::check()
{
    return !climberLS->Get();
}
