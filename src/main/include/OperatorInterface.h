#pragma once

#include <frc/Joystick.h>
#include <frc2/command/button/JoystickButton.h>

// Change numbers as appropriate.

class OperatorInterface
{
    public:
        OperatorInterface();
        ~OperatorInterface();
        frc::Joystick* joyDriver;
        frc::Joystick* joyMate;
        frc2::JoystickButton* btnClimberExtend;
        frc2::JoystickButton* btnClimberRetract;
        frc2::JoystickButton* btnLoadForward;
        frc2::JoystickButton* btnLoadReverse;

        // ***********
        // TESTING
        const int intBtnTest1 = 5;
        const int intBtnTest2 = 6;
        frc2::JoystickButton* btnTest1;
        frc2::JoystickButton* btnTest2;
        // ***********

    private:
        // JOYSTICKS
        const int intJoyDriver = 0;
        const int intJoyMate = 1;

        // BUTTONS - **** will need updates ****
        // Intake/Hopper
        const int intBtnLoadForward = 1;
        const int intBtnLoadReverse = 2;
        // Tower/Turret/Shooter/Hood
        // const int intBtnOutGood = 4;
        // const int intBtnOutBad = 5;
        // const int intBtnOutStop = 6;
        // Climber
        const int intBtnClimberExtend = 7;
        const int intBtnClimberRetract = 8;
};
