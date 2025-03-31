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
#include "CraneState.h"

// macros
#define NUM_WINCHES 10

// Forward declaration
class CraneState;

class Crane
{
private:
    CraneState *currentState;
    bool liftFlag[NUM_WINCHES];
    double height;
    double power_placeholder;
    int img[1]; // the size of this is dependent on user choice probably
    unsigned long lastDevSwitchTime;
    JsonDocument doc;
    // data structure to hold crane's power measurements, and the time at which they were taken
public:
    Crane()
    {
        this->currentState = new Both();
    }
    ~Crane();

    void initialize();

    void changeState(CraneState *newState)
    {
        delete currentState;
        currentState = newState;
    }
};

#endif // CRANE_H