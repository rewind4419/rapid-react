#pragma once

#include <frc/TimedRobot.h>
#include <rev/CANSparkMax.h>
#include <frc/Compressor.h>
#include "RobotMap.h"
#include "RobotSettings.h"
#include "OperatorInterface.h"
#include "../cpp/sub/ballmng/ballmngcore.h"
#include "../cpp/sub/ballmng/ballmngintake.h"
#include "../cpp/sub/ballmng/ballmnghopper.h"
#include "../cpp/sub/ballmng/ballmngtwr.h"
#include "sub/ballmng/ballmngTurret.h"
#include "sub/ballmng/ballmngShooter.h"
#include "sub/ballmng/ballmngHood.h"
#include "sub/climber/subClimber.h"


// #include "logger.h"
// LogPacket* Log();


#include "maths.h"

struct ControllerButton {
  bool down;
  bool held;
  bool up;
};

struct ControllerInput {
  v2 joystickLeft;
  v2 joystickRight;
  float triggerLeft;
  float triggerRight;

  ControllerButton x;
  ControllerButton y;
  ControllerButton a;
  ControllerButton b;
  
  ControllerButton bumperLeft;
  ControllerButton bumperRight;
};

struct Input
{
  ControllerInput driver;
  ControllerInput mate;
};

struct Robot : public frc::TimedRobot {
  // Robot() : frc::TimedRobot(0.02) {}
  Robot() : frc::TimedRobot(0.02) { robotInstance = this; }
  // Robot() : frc::TimedRobot(0.001) {}
  ~Robot() { robotInstance = nullptr; }

  Input input;

  // Robot
  static Robot* robotInstance;
  // static Robot* GetInstance();
  inline static Robot* GetInstance() { return robotInstance; }
  // inline static Robot* GetInstance() { return this; }

  // Subsystems
  ballmngintake* robotIntake;
  ballmnghopper* robotHopper;
  ballmngtwr* robotTower;
  ballmngTurret* robotTurret;
  ballmngShooter* robotShooter;
  ballmngHood* robotHood;
  subClimber* robotClimberLeft;
  subClimber* robotClimberRight;

  // Compressor
  frc::Compressor* pcmCompressor;

  // Operator interface
  OperatorInterface* robotOI;

  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void TestInit() override;
  void TestPeriodic() override;
};
