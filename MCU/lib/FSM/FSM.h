#pragma once

#ifndef FSM_H
#define FSM_H

#include <Arduino.h>
#include <vector>
#include <ArduinoJson.h>
#include "pins.h"
#include <Base64.h>
#include "interrupts.h"
#include "LoRa.h"
#include "Sensors/camera_handler.h"
#include "Sensors/pot_handler.h"
#include "Sensors/temperature_sensor.h"
#include "winch.h"
#include "powerInfo.h"  // for all power information
#include "timer.h"

#define DEBUG true

enum State
{
    NORMAL,
    LOW_POWER,
    NO_CONNECTION,
    LOW_POWER_NO_CONNECTION
};

struct data
{
    // Assuming the size of the array is 10, you can adjust it as needed
    static const size_t numWinches = 10;

    LoraRadio *lora; // a class to hold all the lora variables.
    winchData *winch;
    CameraHandler *cam;

    bool liftFlag[numWinches];
    bool liftStarted;
    // bool lowerFlag[numWinches];
    State state;

    double height[numWinches];
    std::vector<double> power; // stores power readings for each device
    std::vector<double> temp;  // stores temperature readings for each device

    JsonDocument doc;

    powerInfo powerData;    // stores power readings for each device
    time t;                 // a value in minutes and seconds; need a better representation maybe.
    byte last;
};

#define POWER_THRESHOLD 11.8
#define MAX_HEIGHT 3.5

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
 * @brief TODO: Disconnected state will occur when the device fails to recieve a transmission within
 * SIGN_OF_LIFE_TIMEOUT.\n
 *
 * @param d
 */
void RFDisconnectedCase(data &d);

bool sendData(data &d);

/**
 * @brief Reads Json and runs the commands in the json doc.\n
 * Should probably clear the JSON doc after running the commands.\n
 *
 * TODO: Only LIFT is coded rn
 * @param doc
 * @return int returns 0 if the command is successfully run.\n
 */
int runCommands(data &d);

JsonDocument jsonify(data &d);

bool sendImage(data &d);

// Sensor Controls
bool getAndSendImg(data &d);

// Temp sensor
void updateTemp(data &d);

// DEBUG CONTROLS
typedef struct debug_sim {
    bool battery;
    bool solar;
    bool height;
    bool temp;
} ds;

/**
 * @brief a function to test the FSM
 *
 * @param d FSM data struct
 * @param ds decide whether to simulate values in place of missing systems. values are power and sensors.
 * @param params in the form p=#
 *      h - height
 *      t - temp
 *      b - battery
 *      s = solar PV
 */
void testState(data& d, debug_sim ds, std::vector<std::string> params);
void parseParams(data& d, debug_sim ds, std::vector<std::string> params);
void updateTime(data& d);


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