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
#include "CraneState.h"
#include "ArduinoJson.h"
// macros
#define NUM_WINCHES 10

class Crane
{
public:
    Crane();
    ~Crane();

    void initialize();

    void changeState(CraneState &newState)
    {
        delete currentState;
        currentState = &newState;
    }

private:
    CraneState *currentState;
    bool liftFlag[NUM_WINCHES];
    double height;
    double power_placeholder;
    int img[1]; // the size of this is dependent on user choice probably
    unsigned long lastDevSwitchTime;
    JsonDocument doc;
    // data structure to hold crane's power measurements, and the time at which they were taken
};

#endif // CRANE_H