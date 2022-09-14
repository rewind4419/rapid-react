#include "Robot.h"
#include "commandgroup/grpTurretInitialize.h"

#include "error.h"

#include <frc/smartdashboard/SmartDashboard.h>


#include <stdio.h>
#include <rev/CANSparkMax.h>
#include <frc/Joystick.h>

#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <poll.h>

#include "../../../../fennec/src/fennec_common.h"

#define internal static
#define persist  static

internal int my_socket;
internal bool fennec_connected;


enum MyMotorType
{
    Motor_None = 0,
    Motor_SparkMax,
};

struct MyMotor
{
    MyMotorType type;

    union
    {
        rev::CANSparkMax* sparkMax;
    };
};

void SetMotorSpeed(MyMotor* motor, float speed)
{
    if (motor->type == Motor_SparkMax)
        motor->sparkMax->Set(speed);
}

internal struct 
{
    MyMotor motors[32];
} robot;

internal frc::Joystick driver_gamepad (0);
internal frc::Joystick mate_gamepad (1);


internal bool init_fennec()
{
    my_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (!my_socket)
    {
        perror("Failed to socket");
        return false;
    }

    fennec_connected = true;

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(4419);
    if(inet_pton(AF_INET, "10.44.19.11", &address.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        return false;
    }

    if (connect(my_socket, (const sockaddr*)&address, sizeof(address)))
    {
        perror("Failed to connect");
        return false;
    }

    // char* msg = "Yeet~";
    // send(my_socket, msg, 6, NULL);


    // char* text = "Say apple!";
    // send(my_socket, text, strlen(text) + 1, NULL);


    return true;
}


internal bool fn_recv_message(FennecMsg* msg)
{    
    // struct pollfd fd;
    // int ret;
    // fd.fd = my_socket; // socket handler 
    // fd.events = POLLIN;
    // ret = poll(&fd, 1, 1000); // 1 second for timeout
    // switch (ret) {
    //     case -1:
    //         // Error
    //         break;
    //     case 0:
    //         // Timeout 
    //         break;
    //     default:
    //         ssize_t size = recv(my_socket, &msg, sizeof(FennecMsg), NULL);
    //         if ((size != sizeof(FennecMsg))) {
    //             printf("[client] Msg recv failed!\n");
    //             // ~Todo deal with the error state somehow
    //             return false;
    //         }
    //         return true;
    // }
    // return false;


    ssize_t size = recv(my_socket, msg, sizeof(FennecMsg), NULL);
    if ((size != sizeof(FennecMsg))) {
        // printf("[client] Msg recv failed!\n");
        // if (size == -1);
        //     perror("error");
        // ~Todo deal with the error state somehow

        // ~Todo make this only happen if transport endpoint is not connected
        fennec_connected = false;

        return false;
    }
    return true;
}


void fn_send_message(FennecMsg msg)
{
    ssize_t size = send(my_socket, &msg, sizeof(FennecMsg), NULL);
    // if (size != sizeof(FennecMsg)) printf("[client] Msg send failed!\n");
}

internal void quit_fennec()
{
    close(my_socket);
}














// utilities


void FnSendHandoffRio()
{
    FennecMsg msg = {};
    msg.type = FennecMsgType_Handoff_Rio;
    fn_send_message(msg);
}

void FnSendGamepad(frc::Joystick* joystick, u32 gamepadId)
{
    
    Fennec_Gamepad gamepad;
    gamepad.leftTrigger = joystick->GetRawAxis(2);
    gamepad.rightTrigger = joystick->GetRawAxis(3);

    gamepad.leftX  = joystick->GetRawAxis(0);
    gamepad.leftY  = joystick->GetRawAxis(1);

    gamepad.rightX = joystick->GetRawAxis(4);
    gamepad.rightY = joystick->GetRawAxis(5);

    FennecMsg msg;
    msg.type = FennecMsgType_GamepadState_Rio;
    msg.gamepadState.gamepadId = gamepadId;
    msg.gamepadState.gamepad = gamepad;
    fn_send_message(msg);
}

//


void RegisterSparkMaxMotor(u32 canId)
{
    if (robot.motors[canId].type != Motor_None) { printf("[warn] Tried to create motor that already exists (can=%d)\n", canId); return; }
    robot.motors[canId].type = Motor_SparkMax;
    robot.motors[canId].sparkMax = new rev::CANSparkMax((int)canId, rev::CANSparkMaxLowLevel::MotorType::kBrushless);
}




internal void DoFennecCommunication()
{
    // ~Todo(sean) test if switching the recv-send order changes latency
    static int frame = 0;
    if (!fennec_connected)
    {
        // FnTryReconnect();
        if (frame++ > 200)
        {
            quit_fennec();
            init_fennec();
            frame = 0;
            printf("Fennec reconnecting...\n\n\n\n\n\n\n\n\n\n");
        }
    }


    // FnSendGamepad(&my_gamepad, 0);

    FnSendHandoffRio();
    // printf("Handoff!\n");

    
    FennecMsg recvMsg = {};
    while (true)
    {
        if (!fn_recv_message(&recvMsg))
        {
            return;
        }

        if (recvMsg.type == FennecMsgType_Handoff_Host)
            break;
        
        if (recvMsg.type == FennecMsgType_SparkMax_SetSpeed_Host)
        {
            SetMotorSpeed(&robot.motors[recvMsg.sparkMax_setSpeed.canId], recvMsg.sparkMax_setSpeed.motorSpeed);
        }
    }
}



///////////////////////// ROBOT CODE START ///////////////////////////////////


#include "rev/CANSparkMax.h"


Robot* Robot::robotInstance = nullptr;

#include "drivetrain.h"

internal Drivetrain drivetrain;


// FILE* logFile;

void Robot::RobotInit()
{
    // logFile = fopen("log.txt", "wb");

    // robotOI = new OperatorInterface();
    // Test the turret initialization out before adding to the robot init
    // frc2::Command* myTurretInitialization = new grpTurretInitialize();
    // myTurretInitialization->Schedule();
    // ************************************

    // Initiate compressor pressure control
    pcmCompressor = new frc::Compressor(RobotMap::canPCM, frc::PneumaticsModuleType::CTREPCM);
    // pcmCompressor->EnableDigital();
    pcmCompressor->Disable();

    // bool success = init_fennec();
    // printf("[client] Init fennec: %s\n", success ? "Succeeded" : "Failed");

    // RegisterSparkMaxMotor(3);
    // RegisterSparkMaxMotor(4);


    { //Initialize subsystems
        
        robotIntake = new ballmngintake(RobotMap::canIntake, RobotMap::pcmIntakeExtend, RobotMap::pcmIntakeRetract);
        
        robotHopper = new ballmnghopper(RobotMap::canHopper);
        
        // robotTower = new ballmngtwr(RobotMap::canTowerTop, RobotMap::pwmTowerBottom);
        
        robotTower = new ballmngtwr(RobotMap::canTowerTop, RobotMap::canTowerBottom);

    //     // Limit switches will be connected directly to the motor controller
        // robotTurret = new ballmngTurret(RobotMap::canTurret, RobotMap::dioTurretLeft, RobotMap::dioTurretRight);
        // robotTurret = new ballmngTurret(RobotMap::canTurret);
        // robotShooter = new ballmngShooter(RobotMap::canShooter1, RobotMap::canShooter2);
        // robotHood = new ballmngHood(RobotMap::pwmHood); // , RobotMap::pwmHoodRight);
        // robotClimberLeft = new subClimber(RobotMap::canClimberLeft, RobotMap::dioClimberLeft, 1);
        // robotClimberRight = new subClimber(RobotMap::canClimberRight, RobotMap::dioClimberRight, -1);
    }

    InitDrivetrain(&drivetrain);

    // frc::SmartDashboard::PutNumber("Auto Waypoint Threshold", 10);
    // frc::SmartDashboard::PutNumber("Auto Horiz", -4.0F);
    // frc::SmartDashboard::PutNumber("Auto Shunt (Forward)", 12.0F * 2.0F);
    // frc::SmartDashboard::PutNumber("Auto Rotate", 0);

    frc::SmartDashboard::PutNumber("Y Shoot Hood", 0.30); // 0.36
    frc::SmartDashboard::PutNumber("Y Shoot Speed", 1500); // 4000
}

// internal rev::CANSparkMax motorA = rev::CANSparkMax(8, rev::CANSparkMaxLowLevel::MotorType::kBrushless);

// internal rev::CANSparkMax motorB = rev::CANSparkMax(5, rev::CANSparkMaxLowLevel::MotorType::kBrushless);

#include <math.h>
#include <frc2/command/CommandScheduler.h>

// #include "logger.h"

// LogPacket logPacket {};
// LogPacket* Log() { return &logPacket; }



internal ControllerButton GetControllerButton(int x, frc::Joystick* joystick)
{
    ControllerButton button;
    button.down = joystick->GetRawButtonPressed(x);
    button.up   = joystick->GetRawButtonReleased(x);
    button.held = joystick->GetRawButton(x);
    return button;
}

internal void DoControllerInput(ControllerInput* ctrl, frc::Joystick* joystick)
{
    ctrl->joystickLeft.x = joystick->GetRawAxis(0);
    ctrl->joystickLeft.y = -joystick->GetRawAxis(1);

    ctrl->triggerLeft = joystick->GetRawAxis(2);
    ctrl->triggerRight = joystick->GetRawAxis(3);

    ctrl->joystickRight.x = joystick->GetRawAxis(4);
    ctrl->joystickRight.y = -joystick->GetRawAxis(5);

    ctrl->bumperLeft = GetControllerButton(5, joystick);
    ctrl->bumperRight = GetControllerButton(6, joystick);

    ctrl->a = GetControllerButton(1, joystick);
    ctrl->b = GetControllerButton(2, joystick);
    ctrl->x = GetControllerButton(3, joystick);
    ctrl->y = GetControllerButton(4, joystick);
}




void Robot::RobotPeriodic()
{
    DoControllerInput(&input.driver, &driver_gamepad);
    DoControllerInput(&input.mate, &mate_gamepad);



    // DoFennecCommunication();
    
    
    //step the scheduler
    // frc2::CommandScheduler::GetInstance().Run();

    // #if !USE_DRIVETRAIN
    // float intakeThrottle = 0.5; // 0 to 1
    // motorA.Set(intakeThrottle * (fabsf(joystick.GetRawAxis(1)) * joystick.GetRawAxis(1)));
    // #endif


    // printf("%d, %d\n", robotClimberLeft->check() ? 1 : 0, robotClimberRight->check() ? 1 : 0);

    // printf("L: %f, %f\n", input.driver.joystickLeft.x, input.driver.joystickLeft.y);
    // printf("R: %f, %f\n", input.driver.joystickRight.x, input.driver.joystickRight.y);

    // motorB.Set(0.5 * (fabsf(joystick.GetRawAxis(5)) * joystick.GetRawAxis(5)));
}


enum AutoState {
    AUTO_PREPARE = 0,   // spins up the shooter wheel,
    AUTO_SHOOT,         // shoots the ball
    AUTO_EXIT,          // moves forward
    AUTO_YEET_NEXT,     // moves back again while spinning up the shooter wheel,
    AUTO_RETURN_TO_YEET,// shoots the ball
}; 


static AutoState autoState = AUTO_PREPARE;

float autoTimer = 0;

void Robot::AutonomousInit() 
{
    drivetrain.origin = v2 { 0,0 };
    autoState = AUTO_PREPARE;
    drivetrain.rotation = 0;
    autoTimer = 0;
}



rev::CANSparkMax shooter_motor1 {
  40,
  rev::CANSparkMax::MotorType::kBrushless
};
rev::CANSparkMax shooter_motor2 {
  42,
  rev::CANSparkMax::MotorType::kBrushless
};
rev::CANSparkMax hood_motor(1, rev::CANSparkMax::MotorType::kBrushless);



const float DRIVE_TO_THRESHOLD = 5;
const float DRIVE_TO_ROTATE_THRESHOLD = 0.2;
float DRIVE_WAYPOINT_RADIUS = 10;
const float DRIVE_MIN_SPEED = 0.3;
internal void DriveTo(v2 target, float targetRotation, float speed, float rotateSpeed)
{
    float dt = 0.02;

    v2 translate { 0, 0 };
    translate.x = target.x - drivetrain.origin.x;
    translate.y = target.y - drivetrain.origin.y;
    
    
    translate = translate / v2 { DRIVE_TO_THRESHOLD, DRIVE_TO_THRESHOLD };
    if (translate.x > 1) translate.x = 1;
    if (translate.x < -1) translate.x = -1;
    if (translate.y > 1) translate.y = 1;
    if (translate.y < -1) translate.y = -1;

    float rotater = targetRotation - drivetrain.rotation;

    rotater /= DRIVE_TO_ROTATE_THRESHOLD;
    if (rotater > 1) rotater = 1;
    if (rotater < -1) rotater = -1;

    
    // driver-oriented (as opposed to robot-oriented)
    translate = Rotate(translate, -drivetrain.rotation * M_PI);
    translate = translate * v2 { speed, speed };

    // float tLen = Length(translate) / speed * (speed - DRIVE_MIN_SPEED) + DRIVE_MIN_SPEED;
    // translate = translate; // * v2 { tLen, tLen };

    // DrivetrainUpdate(&drivetrain, translate, rotater * rotateSpeed, dt);   
}

void Robot::AutonomousPeriodic() {
    return;

    DRIVE_WAYPOINT_RADIUS = frc::SmartDashboard::GetNumber("Auto Waypoint Threshold", 10);
    float dt = 0.02;

    frc::SmartDashboard::PutNumber("Auto State", autoState);

    if (autoState == AUTO_PREPARE)
    {
        autoTimer += dt;
    
        // prepare        
        robotHood->Set(0.10);
        robotShooter->move(3200);


        if (autoTimer >= 3.0) {
            autoTimer = 0;
            autoState = AUTO_SHOOT;
        }
    }
    else if (autoState == AUTO_SHOOT)
    {
       autoTimer += dt;

        // continue prepare
        robotHood->Set(0.10);
        robotShooter->move(3300);

        // yeet    
        robotHopper->move(ballmngdir::IN, RobotSettings::HopperMotorSpeedForward);
        robotTower->move(ballmngdir::IN, RobotSettings::TowerIntakeMotorTopSpeedForward, RobotSettings::TowerIntakeMotorBottomSpeedForward);


        if (autoTimer >= 1.7) {
            autoTimer = 0;
            autoState = AUTO_EXIT;
        }
    }
    else if (autoState == AUTO_EXIT)
    {
        
        robotShooter->move(0);

        {
            v2 inputTranslation = v2 { 0, 0 };

            v2 target = {
                    frc::SmartDashboard::GetNumber("Auto Horiz", -4.0F),
                    frc::SmartDashboard::GetNumber("Auto Shunt (Forward)", 12.0F * 2.0F) 
                };

            float angle = frc::SmartDashboard::GetNumber("Auto Rotate", 0);
        
            
            DriveTo(target, angle, 0.60, 0.5);

            if (Length( target - drivetrain.origin ) > DRIVE_WAYPOINT_RADIUS)
            {
            }
            else {
                autoState = AUTO_YEET_NEXT;
                autoTimer = 0;
            }


        }

        robotHopper->stop();
        robotTower->stop();

        robotIntake->move(ballmngdir::IN, RobotSettings::IntakeMotorSpeedForward);
    }
    else if (autoState == AUTO_YEET_NEXT)
    {
        autoTimer += dt;
        
        // prepare        
        robotHood->Set(0.10);
        robotShooter->move(3200);

        if (autoTimer > 0.1)
        {
            autoTimer = 0;
            autoState = AUTO_RETURN_TO_YEET;
        }
    }
    else if (autoState == AUTO_RETURN_TO_YEET)
    {
        robotHood->Set(0.10);
        robotShooter->move(3200);

        autoTimer += dt;
        {
            float dt = 0.02;

            v2 target = { 0, 0 };
            DriveTo(target, 0, 0.60, 0.5);
            if (Length( target - drivetrain.origin ) > DRIVE_WAYPOINT_RADIUS)
            {
            }
            else
            {   
                if (autoTimer > 1) {
                    robotIntake->stop();
                }
                
                if (autoTimer > 3) {
                    robotHopper->move(ballmngdir::IN, RobotSettings::HopperMotorSpeedForward);
                    robotTower->move(ballmngdir::IN, RobotSettings::TowerIntakeMotorTopSpeedForward, RobotSettings::TowerIntakeMotorBottomSpeedForward);
                }
            }
        }
    }
}

void Robot::TeleopInit() {}



void Robot::TeleopPeriodic() {
    // if (!robotTurret->isInitialized) {
    //     robotTurret->DoInitialization();
    // }


    // cargoStatus status = robotTower->cargocheck();

    // if (status == cargoStatus::Good)
    //     printf("Good!\n");
    // else if (status == cargoStatus::Bad)
    //     printf("Bad\n");
    // else if (status == cargoStatus::None)
    //     printf("None!\n");

    // if (mate_gamepad.GetRawButton(5)) // left bumper 
    // {
    //     robotClimberLeft->move(0.5);
    //     robotClimberRight->move(0.5);
    // }
    // else if (mate_gamepad.GetRawButton(6)) // right bumper
    // {
    //     robotClimberLeft->move(0.5);
    //     robotClimberRight->move(0.5);
    // }
    // else 
    
    // {
    //     robotClimberLeft->move(0.7 * input.mate.joystickLeft.x * fabsf(input.mate.joystickLeft.x));
    //     robotClimberRight->move(0.7 * input.mate.joystickLeft.y * fabsf(input.mate.joystickLeft.y));
    // }



    {
        float dt = 0.02;

        v2 inputTranslation = v2 { input.driver.joystickLeft.x, input.driver.joystickLeft.y };

        
        float currSpeed = 0.5;

        if (driver_gamepad.GetRawButton(6)) { // right bumper
            currSpeed = 0.2; // surgery
        }
        else {
            inputTranslation = inputTranslation * v2 { Length(inputTranslation), Length(inputTranslation) };
        }

        if (driver_gamepad.GetRawButton(5)) { // left bumper
            currSpeed = 1; // sprint
        }

        // driver-oriented (as opposed to robot-oriented)
        inputTranslation = Rotate(inputTranslation, -drivetrain.rotation * M_PI); // fix this

        if (driver_gamepad.GetRawButton(4)) {
            drivetrain.rotation = 0;
        }


        inputTranslation = inputTranslation * v2 { currSpeed, currSpeed };

        DrivetrainUpdate(&drivetrain, inputTranslation, input.driver.joystickRight.x * fabsf(input.driver.joystickRight.x) * currSpeed, dt);
    }


    // printf("trigger right: %f   --- trigger left: %f\n", input.driver.triggerRight, input.driver.triggerLeft);
    

    

    // if (input.mate.triggerRight > 0.2)
    // {
    //     robotHopper->move(ballmngdir::IN, RobotSettings::HopperMotorSpeedForward);
    //     robotTower->move(ballmngdir::IN, RobotSettings::TowerIntakeMotorTopSpeedForward, RobotSettings::TowerIntakeMotorBottomSpeedForward);
    // }
    // else if (input.mate.triggerLeft > 0.2) // outtake
    // {
    //     robotHopper->move(ballmngdir::OUT, RobotSettings::HopperMotorSpeedReverse);
    //     robotTower->move(ballmngdir::OUT, RobotSettings::TowerIntakeMotorTopSpeedReverse, RobotSettings::TowerIntakeMotorBottomSpeedReverse);
    // }
    // else
    // {
    //     robotHopper->stop();
    //     robotTower->stop();
    // }


    // // // intake
    // if (input.driver.triggerRight > 0.2)
    // {
    //     robotIntake->move(ballmngdir::IN, RobotSettings::IntakeMotorSpeedForward * input.driver.triggerRight);
    // }
    // else if (input.driver.triggerLeft > 0.2) // outtake
    // {
    //     robotIntake->move(ballmngdir::OUT, RobotSettings::IntakeMotorSpeedReverse * input.driver.triggerLeft);
    // }
    // else
    // {
    //     robotIntake->stop();
    // }




    // if (robotTurret->isInitialized)
    // {
    //     robotTurret->aim = 50; //100 * (input.mate.joystickRight.x / 2.0 + 0.5);
    //     robotTurret->DoAim();
    //     robotTurret->PushBackToCenterIfOutOfBounds();
    // }
    

    // static float shooterSpeed = 0;
    // shooterSpeed += 0.001 * input.mate.joystickRight.y;
    // if (shooterSpeed > 1) shooterSpeed = 1;
    // if (shooterSpeed < 0) shooterSpeed = 0;

    // robotShooter->move(RobotSettings::ShooterSpeedGood * shooterSpeed);

    // printf("shooter speed:%f\n", shooterSpeed * RobotSettings::ShooterSpeedGood);


    hood_motor.Set(input.mate.joystickRight.y * 0.4);
    shooter_motor1.Set(input.mate.triggerRight);
    shooter_motor2.Set(input.mate.triggerRight);



    // static float hoodPos = 0;   
    // hoodPos += 0.001 * input.mate.joystickLeft.y;
    // if (hoodPos > 1) hoodPos = 1;
    // if (hoodPos < 0) hoodPos = 0;
    // printf("Hood is @ : %f\n", hoodPos);
    // robotHood->Set(hoodPos);


    // A = 24
    // B = 72
    // X = 96
    // Y = 120

    // if (input.mate.a.held) { // 24 in
    //     robotHood->Set(0.12);
    //     robotShooter->move(3300);
    // }
    // else if (input.mate.b.held) { // 72 in
    //     robotHood->Set(0.40);
    //     robotShooter->move(3500);
    // }
    // else if (input.mate.x.held) { // 96 in
    //     robotHood->Set(0.44);
    //     robotShooter->move(3419);
    // }
    // else if (input.mate.y.held) { // 120 in
    //     robotHood->Set(frc::SmartDashboard::GetNumber("Y Shoot Hood", 0.30)); // 0.36
    //     robotShooter->move(frc::SmartDashboard::GetNumber("Y Shoot Speed", 1500)); // 4000
    // }
    // else
    // {
    //     robotShooter->stop();
    // }

    

    // Log()->joyLeftX = (float)joystick.GetRawAxis(0);
    // Log()->joyLeftY = (float)joystick.GetRawAxis(1);
    // Log()->joyRightX = (float)joystick.GetRawAxis(4);
    // Log()->joyRightY = (float)joystick.GetRawAxis(5);

    // printf("%d <-- compressor \n", pcmCompressor->GetPressureSwitchValue() ? 1 : 0);

    // DumpLogPacket(*Log(), logFile);
}

void Robot::DisabledInit() {}
void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}
void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
    return frc::StartRobot<Robot>();
}
#endif
