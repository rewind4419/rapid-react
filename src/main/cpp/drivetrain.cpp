#include "drivetrain.h"
#include <frc/Joystick.h>
#include <rev/CANSparkMax.h>
#include <RobotMap.h>

#include "pid.h"

#include <math.h>

// Dont even bother w/ deinitialization tbh,
// the roborio literally closes and reopens the program
// the only memory leak stuff we need to worry about is constant allocation, 
// this should be fine tho

PID steeringPid = { 1, 0, 0 };
PID drivingPid  = { 0.05, 0, 0 };

void InitDrivetrain(Drivetrain* drivetrain)
{
	InitPid(&steeringPid);
	InitPid(&drivingPid);

    drivetrain->rotation = 0;
    drivetrain->origin = v2 { };

    float horiz = 22.68;
    float vert = 24.68;

    // ﻿﻿﻿﻿﻿﻿ 0 -- 1.501767
    // ﻿﻿﻿﻿﻿﻿ 1 -- 0.955670
    // ﻿﻿﻿﻿﻿﻿ 2 -- 2.119961
    // ﻿﻿﻿﻿﻿﻿ 3 -- 4.816700 


    const float FL_OFFSET = -1.501767;
    const float FR_OFFSET = -0.955670;
    const float BL_OFFSET = -2.119961;
    const float BR_OFFSET = -4.816700;


    SwerveDriveModule fl;
    fl.directionEncoder = new CANCoder(RobotMap::canSwerveMagneticEncoderFL);
    fl.driveMotor       =   new rev::CANSparkMax(RobotMap::canSwerveDriveFL, rev::CANSparkMaxLowLevel::MotorType::kBrushless);
    fl.steerMotor       =   new rev::CANSparkMax(RobotMap::canSwerveSteerFL, rev::CANSparkMaxLowLevel::MotorType::kBrushless);
    fl.initialPositionOffset = FL_OFFSET; //  - M_PI;
    fl.tangentVector = v2 { -10, 10 };
    fl.centerOffset = v2 { -horiz / 2.0f, vert / 2.0f };
    drivetrain->swerveDrives[DrivetrainSwerve_FL] = fl;

    SwerveDriveModule fr;
    fr.directionEncoder = new CANCoder(RobotMap::canSwerveMagneticEncoderFR);
    fr.driveMotor       =   new rev::CANSparkMax(RobotMap::canSwerveDriveFR, rev::CANSparkMaxLowLevel::MotorType::kBrushless);
    fr.steerMotor       =   new rev::CANSparkMax(RobotMap::canSwerveSteerFR, rev::CANSparkMaxLowLevel::MotorType::kBrushless);
    fr.initialPositionOffset = FR_OFFSET; //  - M_PI;
    fr.tangentVector = v2 { 10, 10 };
    fr.centerOffset = v2 { horiz / 2.0f, vert / 2.0f };
    drivetrain->swerveDrives[DrivetrainSwerve_FR] = fr;

    SwerveDriveModule bl; // heh
    bl.directionEncoder = new CANCoder(RobotMap::canSwerveMagneticEncoderBL);
    bl.driveMotor       =   new rev::CANSparkMax(RobotMap::canSwerveDriveBL, rev::CANSparkMaxLowLevel::MotorType::kBrushless);
    bl.steerMotor       =   new rev::CANSparkMax(RobotMap::canSwerveSteerBL, rev::CANSparkMaxLowLevel::MotorType::kBrushless);
    bl.initialPositionOffset = BL_OFFSET; //  - M_PI;
    bl.tangentVector = v2 { -10, -10 };
    bl.centerOffset = v2 { -horiz / 2.0f, -vert / 2.0f };
    drivetrain->swerveDrives[DrivetrainSwerve_BL] = bl;

    SwerveDriveModule br;
    br.directionEncoder = new CANCoder(RobotMap::canSwerveMagneticEncoderBR);
    br.driveMotor       =   new rev::CANSparkMax(RobotMap::canSwerveDriveBR, rev::CANSparkMaxLowLevel::MotorType::kBrushless);
    br.steerMotor       =   new rev::CANSparkMax(RobotMap::canSwerveSteerBR, rev::CANSparkMaxLowLevel::MotorType::kBrushless);
    br.initialPositionOffset = BR_OFFSET; //  - M_PI;
    br.tangentVector = v2 {  10, -10 };
    br.centerOffset = v2 { horiz / 2.0f, -vert / 2.0f };
    drivetrain->swerveDrives[DrivetrainSwerve_BR] = br;


    // @Note hopefully the cancoders are initialized by this point
    // otherwise we should figure out when to zero

    for (int i = 0; i < DrivetrainSwerve_Count; i++)
    {
        // int i = DrivetrainSwerve_FL;
        SwerveDriveModule* module = &drivetrain->swerveDrives[i];
        
        module->steerEncoder = new rev::SparkMaxRelativeEncoder(module->steerMotor->GetEncoder()); 
        module->driveEncoder = new rev::SparkMaxRelativeEncoder(module->driveMotor->GetEncoder()); 

        float initialPosition = -module->directionEncoder->GetAbsolutePosition() * M_PI / 180 - module->initialPositionOffset;


        // Convert the zero position into a vector to not worry about 
        // @Incomplete: figure out which way the 0 angle is of the CANCoders and if positive is clockwise or not
        module->initialVector = Rotate(v2 { 0, 1 }, initialPosition);

        // printf("Initial vector ,, %f", -module->directionEncoder->GetAbsolutePosition() * M_PI / 180 - module->initialPositionOffset);

        

        // zero the relative encoders
        module->steerEncoder->SetPosition(0);
        module->driveEncoder->SetPosition(0);
    }
}

#include "Robot.h"

void DrivetrainUpdate(Drivetrain* drivetrain, v2 translation, float rotation, float deltaTime)
{
    const float SWERVE_DRIVE_STEER_GEAR_RATIO = 12.8;
    const float TARGET_VECTOR_EPSILON = 0.05;

    v2 targetVectors[DrivetrainSwerve_Count];

    v2 travelVectors[DrivetrainSwerve_Count];

    // Calculate the target vectors of each wheel
    // (Magnitude is the speed of the wheel and direction is the direction)
    for (int i = 0; i < DrivetrainSwerve_Count; i++)
    {
        SwerveDriveModule* module = &drivetrain->swerveDrives[i];
        v2 tangentVector = Normalize(RightPerpendicular(module->tangentVector));

        targetVectors[i] = translation + tangentVector * v2 { rotation, rotation };
        // printf("%d -> %f %f\n", i, targetVectors[i].x, targetVectors[i].y);

    }

    // Normalize the wheel target vectors by dividing by them by the longest vector's magnitude
	float wheelSpeedNormalizeMaximum = 1;
	for (int i = 0; i < DrivetrainSwerve_Count; i++)
	{
		float speed = Length(targetVectors[i]);
		if (wheelSpeedNormalizeMaximum < speed) 
			wheelSpeedNormalizeMaximum = speed;
	}


    for (int i = 0; i < DrivetrainSwerve_Count; i++)
    {
        // int i = DrivetrainSwerve_FL;

        SwerveDriveModule* module = &drivetrain->swerveDrives[i];


        // @Todo: figure out what the deal with gear ratios is
        float steerRotation = -module->steerEncoder->GetPosition() / SWERVE_DRIVE_STEER_GEAR_RATIO * (M_PI * 2);
        module->currentVector = Rotate(module->initialVector, steerRotation);


        // @Incomplete: add a PID loop!

        float turnAngle = 0;
        float rightness = 0;

        // if the move vector is below a certain amount, dont bother moving the wheel to avoid super small numbers causing weird rotations
        // TARGET_VECTOR_EPSILON should be pretty small
        if (Length(targetVectors[i]) > TARGET_VECTOR_EPSILON)
        { 
            v2 directionVector = Normalize(targetVectors[i]); 

            turnAngle = acos(Dot(directionVector, Normalize(module->currentVector)));
            rightness = Dot(directionVector, RightPerpendicular(module->currentVector));

            // if we are going left,
            // Sign(rightness) == -1
            // so the turn angle becomes negative
            turnAngle *= Sign(rightness); 
            
        }


		// Debug thing
            // printf("%f\n", module->driveEncoder->GetVelocity());
            // printf("initialVector-> %f\n", Length(module->initialVector));
            // printf("currentVector-> %f\n", Length(module->currentVector));
            // printf("steerRotation-> %f\n", steerRotation);\


            // @Calibration
            // printf("%d -- %f\n", i, module->directionEncoder->GetAbsolutePosition() * M_PI / 180);


        // // simple P loop

        float steerThrottle = -turnAngle / M_PI; // EvaluatePid(&steeringPid, -turnAngle / M_PI, deltaTime);
        if (steerThrottle >  .5) steerThrottle =  .5;
        if (steerThrottle < -.5) steerThrottle = -.5;
        module->steerMotor->Set(steerThrottle);

		
		float driveSpeed = wheelSpeedNormalizeMaximum;

		// float driveEncoderVelocity = module->driveEncoder->GetVelocity();
		// float driveVelocity = driveSpeed * 100; // in Rpm

        // float driveThrottle = EvaluatePid(&drivingPid, driveVelocity - driveEncoderVelocity, deltaTime);
        // if (driveThrottle >  1) driveThrottle =  1;
        // if (driveThrottle < -1) driveThrottle = -1;
        // module->driveMotor->Set(driveThrottle);

        float v = Length(targetVectors[i]);
        if (v > 1) v = 1;
        if (v < -1) v = -1;
        v = v*v;
        module->driveMotor->Set(0.8 * v);


        // float cancoderPosition = module->directionEncoder->GetAbsolutePosition() * M_PI / 180;

        // if (i == DrivetrainSwerve_BL) printf("BL: ");
        // if (i == DrivetrainSwerve_FL) printf("FL: ");
        // if (i == DrivetrainSwerve_BR) printf("BR: ");
        // if (i == DrivetrainSwerve_FR) printf("FR: ");
        // printf("%f\n", cancoderPosition - module->initialPositionOffset);

        float SWERVE_DRIVE_DRIVE_RATIO = 6.75f;
        float DRIVE_WHEEL_RADIUS = 4; // inches

        float drivePosition = module->driveEncoder->GetPosition();
        float driveDelta = (drivePosition - module->previousDriveEnocder) / SWERVE_DRIVE_DRIVE_RATIO * DRIVE_WHEEL_RADIUS;
        travelVectors[i] = module->currentVector * v2 { driveDelta, driveDelta };
        module->previousDriveEnocder = drivePosition;
    }

    // localization
    {
        v2 origin {};

        for (int i = 0; i < DrivetrainSwerve_Count; i++)
        {
            SwerveDriveModule* module = &drivetrain->swerveDrives[i];

            
            // float initialPosition = module->steerEncoder->GetPosition();
            // printf("(test) CANcoder #%d: %f", i, initialPosition);

            origin = origin + (module->centerOffset + travelVectors[i]) / v2 { DrivetrainSwerve_Count, DrivetrainSwerve_Count };
        }

        v2 forward0 = (drivetrain->swerveDrives[DrivetrainSwerve_FL].centerOffset + travelVectors[DrivetrainSwerve_FL]) - (drivetrain->swerveDrives[DrivetrainSwerve_BL].centerOffset + travelVectors[DrivetrainSwerve_BL]);
        v2 forward1 = (drivetrain->swerveDrives[DrivetrainSwerve_FR].centerOffset + travelVectors[DrivetrainSwerve_FR]) - (drivetrain->swerveDrives[DrivetrainSwerve_BR].centerOffset + travelVectors[DrivetrainSwerve_BR]);

        v2 right0 = (drivetrain->swerveDrives[DrivetrainSwerve_FR].centerOffset + travelVectors[DrivetrainSwerve_FR]) - (drivetrain->swerveDrives[DrivetrainSwerve_FL].centerOffset + travelVectors[DrivetrainSwerve_FL]);
        v2 right1 = (drivetrain->swerveDrives[DrivetrainSwerve_BR].centerOffset + travelVectors[DrivetrainSwerve_BR]) - (drivetrain->swerveDrives[DrivetrainSwerve_BL].centerOffset + travelVectors[DrivetrainSwerve_BL]);
        
        v2 forward = Normalize((forward0 + forward1) / v2 { 2.0, 2.0 });
        v2 right = Normalize((right0 + right1) / v2 { 2.0, 2.0 });
        
        float forwardBasedAngle = acos(Dot(forward, v2 {0, 1}));
        if (forward.x < 0)
            forwardBasedAngle *= -1;
        float rightBasedAngle = acos(Dot(right, v2 {1, 0}));
        if (right.y > 0)
            rightBasedAngle *= -1;
        
        float angle = (forwardBasedAngle + rightBasedAngle) / 2;

        drivetrain->origin = drivetrain->origin + origin; //  * v2 { deltaTime, deltaTime };
        drivetrain->rotation += angle; // @IMU

        // printf("<%f, %f> ^^ %f (%f <> %f)\n", drivetrain->origin.x, drivetrain->origin.y, drivetrain->rotation, forwardBasedAngle, rightBasedAngle);
    }
}
