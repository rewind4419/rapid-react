#pragma once


// Change numbers as appropriate.

namespace RobotSettings
{
    // RPM values (PID'd)
    const float IntakeMotorSpeedForward = 1500;
    const float IntakeMotorSpeedReverse = 1000;

    const float HopperMotorSpeedForward = -1000;
    const float HopperMotorSpeedReverse = -500;

    const float TurretSpeedInitialization = 5;
    //


    const float TowerIntakeMotorTopSpeedForward = -0.45;
    const float TowerIntakeMotorTopSpeedReverse = -0.45;

    const float TowerIntakeMotorBottomSpeedForward = 0.45;
    const float TowerIntakeMotorBottomSpeedReverse = 0.35;

    const float TowerShooterMotorTopSpeedForward = 0.3;
    const float TowerShooterMotorBottomSpeedForward = 0.3;

    const float TurretSpeed = 0.4;

    
    const float ShooterSpeedGood = 5200;
    
    const float ClimberSpeedExtend = 0.1;
    const float ClimberSpeedRetract = -0.1;
}
