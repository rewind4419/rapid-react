#pragma once

// Change numbers as appropriate.

namespace RobotMap
{
    // F = front, B = back, L = left, R = right

    // CAN IDs
    // PCM (Pneumatics Control Module)
    const int canPCM = 0;
    // Swerve drive motor controllers
    // In each corner, there's one for driving and one for steering
    const int canSwerveDriveFL = 5;
    const int canSwerveSteerFL = 2;

    const int canSwerveDriveFR = 4;
    const int canSwerveSteerFR = 7;
    
    const int canSwerveDriveBL = 3;
    const int canSwerveSteerBL = 12;
    
    const int canSwerveDriveBR = 11;
    const int canSwerveSteerBR = 10;
    
    
    // Swerve drive magnetic encoder (for direction)    
    // @Note(sean): these are the Cancoders
    const int canSwerveMagneticEncoderFL = 33;
    const int canSwerveMagneticEncoderFR = 32;
    const int canSwerveMagneticEncoderBL = 31;
    const int canSwerveMagneticEncoderBR = 34;
    
    // Intake
    const int canIntake = 35;
    
    // Hopper
    const int canHopper = 6;
    
    // Tower
    const int canTowerTop = 30;
    const int canTowerBottom = 13;

    // Shooter
    const int canShooter1 = 40;
    const int canShooter2 = 42;
    
    // Turret
    const int canTurret = 8;
    
    // Climber
    const int canClimberLeft = 36;
    const int canClimberRight = 35;

    // PWM (Pulse Width Modulation)
    const int pwmHood = 0;
    // const int pwmHoodRight = 2;

    // DIO (Digital Inputs and Outputs)
    // Turret limit switches can go straight into the motor controller
    const int dioTurretLeft = 1;
    const int dioTurretRight = 2;
    // Climber
    const int dioClimberLeft = 3;
    const int dioClimberRight = 4;

    // PNEUMATICS
    const int pcmIntakeExtend = 7;
    const int pcmIntakeRetract = 0;

    // I2C
    // No addressing allowed for the REV color sensors.

    // Buttons
    // Turret
    const int btnTurretLeft = 5;
    const int btnTurretRight = 6;
    // Intake/Hopper
    const int btnLoadForward = 1;
    const int btnLoadReverse = 2;
}
