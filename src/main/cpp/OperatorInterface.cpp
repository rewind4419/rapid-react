#include "OperatorInterface.h"

#include "commandgroup/grpClimberExtend.h"
#include "commandgroup/grpClimberRetract.h"
#include "commandgroup/grpClimberStop.h"
#include "commandgroup/grpLoadForward.h"
#include "commandgroup/grpLoadReverse.h"
#include "commandgroup/grpLoadStop.h"

// ***********
// TESTING
#include "commands/cmdTurretStop.h"
#include "commands/cmdTurretLeft.h"
#include "commands/cmdTurretRight.h"
#include "commandgroup/grpTurretInitialize.h"
// ***********


// Intake
#include "commands/cmdIntakeForward.h"
#include "commands/cmdIntakeReverse.h"
#include "commands/cmdIntakeStop.h"
//

#include "sub/ballmng/TestCommand.h"


OperatorInterface::OperatorInterface()
{
    joyMate = new frc::Joystick(intJoyDriver);
    // ***********
    // TESTING
    btnTest1 = new frc2::JoystickButton(joyMate, intBtnTest1);
    btnTest1->WhenPressed(new TestCommand());
    // btnTest1->WhenReleased(new cmdTurretStop);
    // btnTest2 = new frc2::JoystickButton(joyMate, intBtnTest2);
    // btnTest2->WhenPressed(new cmdTurretRight(false));
    // btnTest2->WhenReleased(new cmdTurretStop);
    // ***********

    //Climber
    // btnClimberExtend = new frc2::JoystickButton(joyMate, intBtnClimberExtend);
    // btnClimberExtend->WhenPressed(new grpClimberExtend);
    // btnClimberExtend->WhenReleased(new grpClimberStop);
    // btnClimberRetract = new frc2::JoystickButton(joyMate, intBtnClimberRetract);
    // btnClimberRetract->WhenPressed(new grpClimberRetract);
    // btnClimberRetract->WhenReleased(new grpClimberStop);
    //Intake, Hopper, Tower
    // btnLoadForward = new frc2::JoystickButton(joyMate, intBtnLoadForward);
    // btnLoadForward->WhenPressed(new cmdIntakeForward);
    // btnLoadForward->WhenReleased(new cmdIntakeStop);
    // btnLoadReverse = new frc2::JoystickButton(joyMate, intBtnLoadReverse);
    // btnLoadReverse->WhenPressed(new cmdIntakeReverse);
    // btnLoadReverse->WhenReleased(new cmdIntakeStop);
}

OperatorInterface::~OperatorInterface()
{
    delete joyMate;
    delete btnClimberExtend;
    delete btnClimberRetract;
    delete btnLoadForward;
    delete btnLoadReverse;
    // ***********
    // TESTING
    delete btnTest1;
    delete btnTest2;
    // ***********
}
