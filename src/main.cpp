// Human-Machine interface communication
// Yevhenii Shmonin
// 12.11.2026
// bugs: ~

#include <iostream>
#include <sstream>
#include <string>

#include "ConveyorController.h"

const char* stateName(ConveyorState state)
{
    switch (state)
    {
    case ConveyorState::STOPPED:
        return "STOPPED";
    case ConveyorState::RUNNING:
        return "RUNNING";
    case ConveyorState::PAUSED:
        return "PAUSED";
    }

    return "UNKNOWN";
}

int main()
{
    ConveyorController conveyor;
    std::string line;

    std::cout << "Conveyor Control Simulator\n";
    std::cout << "Commands: start, stop, both, status, sensor_on, "
             "sensor_off, tick <ms>, exit\n";
    std::cout << "Simulation time advances only with tick.\n";

    while (std::cout << "> " && std::getline(std::cin, line))
    {
        std::istringstream input(line);
        std::string command;
        std::string extra;
        int elapsedMs = 0;

        if (!(input >> command))
        {
            continue;
        }

        if (command == "tick")
        {
            if (!(input >> elapsedMs) || elapsedMs < 0)
            {
                std::cout << "Use: tick <non-negative integer ms>\n";
                continue;
            }
        }

        if (input >> extra)
        {
            std::cout << "Unexpected extra input\n";
            continue;
        }

        if (command == "exit")
        {
            break;
        }
        else if (command == "start")
        {
            conveyor.processButtons(true, false);
            conveyor.processButtons(false, false);
        }
        else if (command == "stop")
        {
            conveyor.processButtons(false, true);
            conveyor.processButtons(false, false);
        }
        else if (command == "both")
        {
            conveyor.processButtons(true, true);
            conveyor.processButtons(false, false);
        }
        else if (command == "sensor_on")
        {
            conveyor.setPartSensor(true);
        }
        else if (command == "sensor_off")
        {
            conveyor.setPartSensor(false);
        }
        else if (command == "tick")
        {
            conveyor.advanceTime(elapsedMs);
        }
        else if (command != "status")
        {
            std::cout << "Unknown command\n";
            continue;
        }

        std::cout << "State: " << stateName(conveyor.getState())
                  << " | Motor: "
                  << (conveyor.isRunning() ? "ON" : "OFF")
                  << '\n';
    }

    return 0;
}