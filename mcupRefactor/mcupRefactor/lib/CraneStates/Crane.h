/**
 * @file Crane.h
 * @author Daniel Reeves (dtr@vt.edu)
 * @brief Main class for the crane. Context class for the state machine.
 * @version 0.1
 * @date 2025-03-24
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef CRANE_H
#define CRANE_H
#include "ArduinoJson.h"

// macros
#define NUM_WINCHES 10

// Forward declaration
class CraneState;

// Include the full definition
#include "CraneState.h"


class Crane
{
private:
    CraneState *currentState;

public:
    Crane(CraneState *state) : currentState(nullptr)
    {
        this->transitionTo(state);
    }
    ~Crane()
    {
        delete this->currentState;
    }

    void initialize();
    std::string getState()
    {
        return this->currentState->getState();
    }

    void transitionTo(CraneState *newState)
    {
        if (this->currentState != nullptr)
        {
            delete this->currentState;
        }
        this->currentState = newState;
        this->currentState->set_context(this);
    }
};

#endif // CRANE_H