#ifndef FSM_H
#define FSM_H
#include <Arduino.h>
#include <Wire.h>
#include "interrupts.h"
#include "LoRa.h"
#include "ArduinoJson.h"

#define DEBUG true

enum State
{
    NORMAL,
    LOW_POWER,
    NO_CONNECTION,
    LOW_POWER_NO_CONNECTION
};

enum device
{
    BMS,
    MPPT,
    RADIO,
}; // victron bms, renogy mppt, LoRA module.

struct data
{
    static const size_t img_size = 10; // Assuming the size of the array is 10, you can adjust it as needed
    static const size_t numWinches = 10;

    bool liftFlag[numWinches];
    // bool lowerFlag[numWinches];
    State state;
    double height;
    double power_placeholder;
    int img[img_size];
    device currentDevice;
    unsigned long lastDevSwitchTime;
    JsonDocument doc;
};

#define POWER_THRESHOLD 0.5

// Emergency Lift Lowering
#define TIME_UNTIL_EMERGENCY_LIFT_LOWER_HRS 4

// main function
void FSM(data &d);

// initialization functions
void initializeStartup(data &d);
void initializeNormalFSM(data &d);
void initializeLPM(data &d);
void initializeNCM(data &d);
void initializeLPMandNCM(data &d);
// interrupt initialization functions
void initializeCheckPower();
void initializeReconnection();
void initializeEmergencyLiftLowering();

// Main Loop
void sleep();
void checkPowerHandler(data &d);
void commsHandler(data &d);
void emergencyLiftHandler(data &d);

// power helpers
double checkPower(data &d);

void getIntoLowPowerMode(data &d);
void getOutOfLowPowerMode(data &d);

void powerStateChange(data &d);

// comms helpers
void RFConnectedCase(data &d);
/**
 * @brief TODO: This doesnt exist yet.
 *
 * @param d
 */
void RFDisconnectedCase(data &d);

/**
 * @brief Reads Json and runs the commands in the json doc.\n
 * Should probably clear the JSON doc after running the commands.\n
 *
 * TODO: Only LIFT is coded rn
 * @param doc
 * @return int returns 0 if the command is successfully run.\n
 */
int runCommands(data &d);

// Logan functions

// Sensor Controls
int *getImg();
double getHeight();

// Winch Controls

void winchControl(data &d);

// Debugging
void initializeDebug();

/**
 * @brief No longer applicable.
 *
 * @param d
 */
void CellularConnectedCase(data &d);
void CellularDisconnectedCase(data &d);

#endif // FSM_H