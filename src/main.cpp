#include <iostream>
#include <string>

int main()
{
    bool motorRunning = false;
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
            motorRunning = true;
        }
        else if (command == "stop")
        {
            motorRunning = false;
        }
        else if (command != "status")
        {
            std::cout << "Unknown command\n";
            continue;
        }

        std::cout << "Motor: "
                  << (motorRunning ? "ON" : "OFF")
                  << '\n';
    }

    return 0;
}