#pragma once
#include "ballmngcore.h"
#include <frc2/command/SubsystemBase.h>
#include "rev/CANSparkMax.h"
#include <frc/DoubleSolenoid.h>
#include "pid.h"

class ballmngintake : public frc2::SubsystemBase
{
    public:
    ballmngintake(unsigned int motorid, unsigned int solenoid_extend_id, unsigned int solenoid_retract_id);
    ~ballmngintake();
    void move(ballmngdir dir, float t_speed);
    void stop();

    private:
    PID pid = { 0.001, 0.0, 0.0 };
    float myThrottle = 0.0f;

    unsigned int intakemotorid;
    unsigned int intakesolenoid_extend_id;
    unsigned int intakesolenoid_retract_id;
    bool intakemotorSAFE = false;
    // int speed = 0; //change this
    rev::CANSparkMax* intakemotor;
    rev::SparkMaxRelativeEncoder* intakeencoder;
    frc::DoubleSolenoid* intakesolenoid;
};