#include "sub/ballmng/ballmngTurret.h"

#include "RobotSettings.h"

// Limit switches will be connected directly to the motor controller
// ballmngTurret::ballmngTurret(unsigned int motortopid, unsigned int leftLSid, unsigned int rightLSid)
ballmngTurret::ballmngTurret(unsigned int motortopid, unsigned int leftLSid, unsigned int rightLSid)
{
    turretMotor = new rev::CANSparkMax(motortopid, rev::CANSparkMaxLowLevel::MotorType::kBrushless);
    turretLSleft = new frc::DigitalInput(leftLSid);
    turretLSright = new frc::DigitalInput(rightLSid);
    // turretLSleft = new rev::SparkMaxLimitSwitch(turretMotor->GetReverseLimitSwitch(rev::SparkMaxLimitSwitch::Type::kNormallyClosed));
    // turretLSright = new rev::SparkMaxLimitSwitch(turretMotor->GetForwardLimitSwitch(rev::SparkMaxLimitSwitch::Type::kNormallyClosed));

    printf("%d << turret foo \n", motortopid);

    turretEncoder = new rev::SparkMaxRelativeEncoder(turretMotor->GetEncoder());

    isInitialized = false;
    initLeft = true;

    initThrottle = 0;
    aim = 50;
}


ballmngTurret::~ballmngTurret()
{
    delete turretMotor;
    // delete turretLSleft;
    // delete turretLSright;
}


void ballmngTurret::DoInitialization() {
    float dt = 0.02;
    if (initLeft)
    {
        initThrottle += dt * EvaluatePid(&initPid, (-RobotSettings::TurretSpeedInitialization) - turretEncoder->GetVelocity(), dt);
        if (initThrottle > 0.1) initThrottle = 0.1;
        if (initThrottle < -0.1) initThrottle = -0.1;
        
        Move(initThrottle);

        if (GetLeftLS()) {
            SetEncoderLeft();
            initLeft = false;
            initThrottle = 0;
        }
    }
    else
    {
        initThrottle += dt * EvaluatePid(&initPid, RobotSettings::TurretSpeedInitialization - turretEncoder->GetVelocity(), dt);
        if (initThrottle > 0.1) initThrottle = 0.1;
        if (initThrottle < -0.1) initThrottle = -0.1;
        
        Move(initThrottle);
        
        if (GetRightLS()) {
            SetEncoderRight();
            isInitialized = true;
            initThrottle = 0;
            Move(0);
        }
    }
}

void ballmngTurret::DoAim()
{
    float dt = 0.02;
    float throttle = 0; //EvaluatePid(&aimPid, aim - GetPositionPercent(), dt);
    
    const float THRESHOLD = 5;
    if (GetPositionPercent() > aim + THRESHOLD)
    {
        throttle = -RobotSettings::TurretSpeed;
    }
    else if (GetPositionPercent() < aim - THRESHOLD)
    {
        throttle = RobotSettings::TurretSpeed;
    }
    
    // if (throttle < -0.2) throttle = -0.2;
    // if (throttle > 0.2) throttle = 0.2;
    // printf("turret throttle: %f\n", throttle);
    Move(throttle);
}



void ballmngTurret::PushBackToCenterIfOutOfBounds() {
    float mySpeed = 0;
    if (GetRightLS() || GetPosition() > turretEncoderRight) {
        mySpeed = -RobotSettings::TurretSpeed;
    }

    if (GetLeftLS() || GetPosition() < turretEncoderLeft) {
        mySpeed = RobotSettings::TurretSpeed;
    }

    Move(mySpeed);
}

void ballmngTurret::Periodic() {}

float ballmngTurret::GetPositionPercent()
{
    return 100.0f * (GetPosition() - turretEncoderLeft) / (turretEncoderRight - turretEncoderLeft);
}
int ballmngTurret::GetPosition()
{
    // flipped because motor is a gear apart
    return -turretEncoder->GetPosition();
}
bool ballmngTurret::GetLeftLS()
{
    return !turretLSleft->Get();
}
bool ballmngTurret::GetRightLS()
{
    return !turretLSright->Get();
}

void ballmngTurret::Move(float t_speed)
{
    float mySpeed = t_speed; // Positive is clockwise

    // printf("%d, %d\n", GetLeftLS() ? 1 : 0, GetRightLS() ? 1 : 0);

    if (GetRightLS() || GetPosition() > turretEncoderRight) {
        if (mySpeed > 0) mySpeed = 0;
    }

    if (GetLeftLS() || GetPosition() < turretEncoderLeft) {
        if (mySpeed < 0) mySpeed = 0;
    }

    // Limit to [-1, 1]
    if (mySpeed > 1) {mySpeed = 1;}
    if (mySpeed < -1) {mySpeed = -1;}
    
    // Start motor
    turretMotor->Set(-mySpeed); // flipped cause motor is on a gear
}

void ballmngTurret::Stop()
{
    turretMotor->Set(0);
}

void ballmngTurret::SetEncoderLeft()
{
    turretEncoderLeft = GetPosition();
}
void ballmngTurret::SetEncoderRight()
{
    turretEncoderRight = GetPosition();
}
