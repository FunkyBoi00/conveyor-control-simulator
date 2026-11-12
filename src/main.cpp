// Human-Machine interface communication
// Yevhenii Shmonin
// 12.11.2026
// bugs: ~

#include <iostream>
#include <string>

#include "ConveyorController.h"

int main()
{
    ConveyorController conveyor;
    std::string command;

    std::cout << "Conveyor Control Simulator\n";
    std::cout << "Commands: start, stop, status, exit\n";

    while (std::cout << "> " && std::cin >> command)
    {
        if (command == "exit")
        {
            break;
        }
        else if (command == "start")
        {
            conveyor.start();
        }
        else if (command == "stop")
        {
            conveyor.stop();
        }
        else if (command != "status")
        {
            std::cout << "Unknown command\n";
            continue;
        }

        std::cout << "Motor: "
                  << (conveyor.isRunning() ? "ON" : "OFF")
                  << '\n';
    }

    return 0;
}