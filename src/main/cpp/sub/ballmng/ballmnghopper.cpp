#include "ballmnghopper.h"

ballmnghopper::ballmnghopper(unsigned int motorid)
// :hoppermotorid(motorid)
{
    hoppermotor = new rev::CANSparkMax(motorid, rev::CANSparkMaxLowLevel::MotorType::kBrushless);
    hopperencoder = new rev::SparkMaxRelativeEncoder(hoppermotor->GetEncoder());
    
    myThrottle = 0;
}

ballmnghopper::~ballmnghopper()
{
    delete hoppermotor;
    delete hopperencoder;
}

void ballmnghopper::move(ballmngdir dir, float t_speed)
{
    float mySpeed = dir * t_speed;

    float dt = 0.02;
    myThrottle += EvaluatePid(&pid, mySpeed - hopperencoder->GetVelocity(), dt) * dt;

    printf("hopper:    %f -> %f @@ %f\n", hopperencoder->GetVelocity(), mySpeed, myThrottle);


    // Limit to [-1, 1]
    if (myThrottle > 1) {myThrottle = 1;}
    if (myThrottle < -1) {myThrottle = -1;}
    // Start motor
    hoppermotor->Set(myThrottle);
}
void ballmnghopper::stop()
{
    hoppermotor->Set(0);
}