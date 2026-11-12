// Conveyor Controller
// Yevhenii Shmonin
// 12.11.2026
// bugs: ~

#pragma once

enum class ConveyorState
{
    STOPPED,
    RUNNING,
    PAUSED
};

class ConveyorController
{
public:
    void processButtons(bool startPressed, bool stopPressed)
    {
        const bool startRisingEdge = startPressed && !previousStart;
        previousStart = startPressed;

        if (stopPressed)
        {
            stop();
        }
        else if (startRisingEdge)
        {
            start();
        }
    }

    void start()
    {
        if (state == ConveyorState::STOPPED)
        {
            state = ConveyorState::RUNNING;
        }
    }

    void stop()
    {
        state = ConveyorState::STOPPED;
        remainingPauseMs = 0;
    }

    void setPartSensor(bool active)
    {
        const bool risingEdge = active && !previousSensor;
        previousSensor = active;

        if (state == ConveyorState::RUNNING && risingEdge)
        {
            state = ConveyorState::PAUSED;
            remainingPauseMs = pauseDurationMs;
        }
    }

    void advanceTime(int elapsedMs)
    {
        if (elapsedMs <= 0 || state != ConveyorState::PAUSED)
        {
            return;
        }

        if (elapsedMs >= remainingPauseMs)
        {
            remainingPauseMs = 0;
            state = ConveyorState::RUNNING;
        }
        else
        {
            remainingPauseMs -= elapsedMs;
        }
    }

    bool isRunning() const
    {
        return state == ConveyorState::RUNNING;
    }

    ConveyorState getState() const
    {
        return state;
    }

private:
    static constexpr int pauseDurationMs = 3000;

    ConveyorState state = ConveyorState::STOPPED;
    bool previousSensor = false;
    bool previousStart = false;
    int remainingPauseMs = 0;
};