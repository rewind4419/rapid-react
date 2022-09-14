#include "sub/ballmng/ballmngShooter.h"

ballmngShooter::ballmngShooter(unsigned int motorid0, unsigned int motorid1)
{
    shooterMotor0 = new rev::CANSparkMax(motorid0, rev::CANSparkMaxLowLevel::MotorType::kBrushless);
    shooterMotor1 = new rev::CANSparkMax(motorid1, rev::CANSparkMaxLowLevel::MotorType::kBrushless);

    encoder0 = new rev::SparkMaxRelativeEncoder(shooterMotor0->GetEncoder());
    encoder1 = new rev::SparkMaxRelativeEncoder(shooterMotor1->GetEncoder());

    InitPid(&pid);
    myThrottle = 0;
}

ballmngShooter::~ballmngShooter()
{
    delete shooterMotor0;
    delete shooterMotor1;
}

void ballmngShooter::Periodic() {}

void ballmngShooter::move(float t_speed)
{
    float mySpeed = t_speed;
    float dt = 0.02;

    float currentSpeed = encoder1->GetVelocity();
    // (
    //     encoder1->GetVelocity() + (-encoder0->GetVelocity())
    // ) / 2.0f;

    myThrottle += dt * EvaluatePid(&pid, mySpeed - currentSpeed, dt);
    // printf("%f -> %f @@ %f\n", currentSpeed, mySpeed, myThrottle);

    // Limit to [-1, 1]
    if (myThrottle > 1) {myThrottle = 1;}
    if (myThrottle < -1) {myThrottle = -1;}
    // Start motor
    shooterMotor0->Set(-myThrottle);
    shooterMotor1->Set(myThrottle);
}

void ballmngShooter::stop()
{
    shooterMotor0->Set(0);
    shooterMotor1->Set(0);
}
