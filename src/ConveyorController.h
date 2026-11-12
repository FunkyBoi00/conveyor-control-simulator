#pragma once

class ConveyorController
{
public:
    void start()
    {
        motorRunning = true;
    }

    void stop()
    {
        motorRunning = false;
    }

    bool isRunning() const
    {
        return motorRunning;
    }

private:
    bool motorRunning = false;
};