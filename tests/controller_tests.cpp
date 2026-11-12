// Automatic Controller Test
// Yevhenii Shmonin
// 12.11.2026
// bugs: ~

#include <iostream>
#include "../src/ConveyorController.h"

int failedTests = 0;

void check(bool condition, const char* testName)
{
    if (condition)
    {
        std::cout << "[PASS] " << testName << '\n';
    }
    else
    {
        std::cout << "[FAIL] " << testName << '\n';
        ++failedTests;
    }
}

int main()
{
    {
        ConveyorController conveyor;
        check(!conveyor.isRunning(),                          // !conveyor.isRunning() is true only when motor is disabled
              "Motor is OFF initially");
    }

    {
        ConveyorController conveyor;
        conveyor.start();
        check(conveyor.isRunning(),
              "START turns motor ON");
    }

    {
        ConveyorController conveyor;
        conveyor.start();
        conveyor.stop();
        check(!conveyor.isRunning(),
              "STOP turns running motor OFF");
    }

    {
        ConveyorController conveyor;
        conveyor.start();
        conveyor.start();
        check(conveyor.isRunning(),
              "Repeated START keeps motor ON");
    }

    {
        ConveyorController conveyor;
        conveyor.stop();
        conveyor.stop();
        check(!conveyor.isRunning(),
              "STOP while stopped keeps motor OFF");
    }

    {
        ConveyorController conveyor;
        conveyor.start();
        conveyor.stop();
        conveyor.start();
        check(conveyor.isRunning(),
              "START after STOP turns motor ON");
    }


    {
        ConveyorController conveyor;
        conveyor.start();
        conveyor.setPartSensor(true);

        check(conveyor.getState() == ConveyorState::PAUSED
                  && !conveyor.isRunning(),
              "Sensor rising edge pauses motor");

        conveyor.advanceTime(2999);
        check(conveyor.getState() == ConveyorState::PAUSED,
              "Pause remains active at 2999 ms");

        conveyor.advanceTime(1);
        check(conveyor.isRunning(),
              "Motor resumes at 3000 ms");

        conveyor.setPartSensor(true);
        check(conveyor.isRunning(),
              "Held sensor does not trigger another pause");

        conveyor.setPartSensor(false);
        conveyor.setPartSensor(true);
        check(conveyor.getState() == ConveyorState::PAUSED,
              "New sensor rising edge starts another pause");
    }

    {
        ConveyorController conveyor;
        conveyor.start();
        conveyor.setPartSensor(true);
        conveyor.advanceTime(1000);
        conveyor.stop();
        conveyor.advanceTime(2000);

        check(conveyor.getState() == ConveyorState::STOPPED
                  && !conveyor.isRunning(),
              "STOP cancels pause and prevents automatic restart");

        conveyor.start();
        conveyor.advanceTime(5000);
        check(conveyor.isRunning(),
              "New START works after cancelled pause");
    }

    {
        ConveyorController conveyor;
        conveyor.start();
        conveyor.setPartSensor(true);
        conveyor.advanceTime(1000);
        conveyor.start();

        check(conveyor.getState() == ConveyorState::PAUSED,
              "START cannot interrupt pause");

        conveyor.advanceTime(2000);
        check(conveyor.isRunning(),
              "START during pause does not reset timer");
    }

    {
        ConveyorController conveyor;
        conveyor.setPartSensor(true);
        conveyor.start();
        conveyor.setPartSensor(true);

        check(conveyor.isRunning(),
              "Sensor already active at START does not pause motor");

        conveyor.setPartSensor(false);
        conveyor.setPartSensor(true);
        check(conveyor.getState() == ConveyorState::PAUSED,
              "Sensor must clear and activate again after START");
    }

    {
        ConveyorController conveyor;
        conveyor.processButtons(true, true);

        check(conveyor.getState() == ConveyorState::STOPPED,
              "STOP overrides START while stopped");
    }

    {
        ConveyorController conveyor;
        conveyor.start();
        conveyor.processButtons(true, true);

        check(conveyor.getState() == ConveyorState::STOPPED,
              "STOP overrides START while running");
    }

    {
        ConveyorController conveyor;
        conveyor.start();
        conveyor.setPartSensor(true);
        conveyor.advanceTime(1000);

        conveyor.processButtons(true, true);
        conveyor.advanceTime(2000);

        check(conveyor.getState() == ConveyorState::STOPPED,
              "Simultaneous STOP and START cancel pause");
    }

    {
        ConveyorController conveyor;

        conveyor.processButtons(true, true);
        conveyor.processButtons(true, false);

        check(conveyor.getState() == ConveyorState::STOPPED,
              "Held START cannot restart after STOP release");

        conveyor.processButtons(false, false);
        conveyor.processButtons(true, false);

        check(conveyor.isRunning(),
              "Fresh START press restarts after STOP");
    }

    std::cout << "Failed tests: " << failedTests << '\n';

    return failedTests == 0 ? 0 : 1;                          // returns the programme’s exit code: 0 if all checks are successful, or 1 if an error occurs.
}