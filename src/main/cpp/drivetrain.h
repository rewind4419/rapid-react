#pragma once

#include "maths.h"

#include <rev/CANSparkMax.h>
#include <ctre/phoenix/sensors/CANCoder.h>
using namespace ctre::phoenix::sensors;


struct SwerveDriveModule
{
    //  @Note(sean): This has to be a CANCoder pointer because they're using OOP
    //  and we cant ensure this is a value type
    CANCoder* directionEncoder; // absolute encoder
    rev::CANSparkMax* driveMotor;
    rev::CANSparkMax* steerMotor;
    rev::SparkMaxRelativeEncoder* steerEncoder; // relative encoder
    rev::SparkMaxRelativeEncoder* driveEncoder;

    float initialPositionOffset;


    float previousDriveEnocder;

    v2 initialVector;
    v2 currentVector;

    v2 tangentVector;
    v2 centerOffset;
};

enum DrivetrainSwerveModule
{
    DrivetrainSwerve_FL = 0,
    DrivetrainSwerve_FR,
    DrivetrainSwerve_BL,
    DrivetrainSwerve_BR,

    DrivetrainSwerve_Count
};

struct Drivetrain
{
    SwerveDriveModule swerveDrives[4];

    v2 origin;
    float rotation;
};

void InitDrivetrain(Drivetrain* drivetrain);
void DrivetrainUpdate(Drivetrain* drivetrain, v2 direction, float rotation, float deltaTime);
