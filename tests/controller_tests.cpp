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

    std::cout << "Failed tests: " << failedTests << '\n';

    return failedTests == 0 ? 0 : 1;                          // returns the programme’s exit code: 0 if all checks are successful, or 1 if an error occurs.
}