#ifndef POWERINFO_H
#define POWERINFO_H

// for accessing renogy MPPT
#include <renogy.h>

// for accessing victron SmartShunt
#include <victron.h>
#include <victronFunctions.h>

// misc info.
#include <ArduinoJson.h>    // formatting

#include "uartSwitch.h"



class powerInfo {
public:
    double batteryVoltage;
    double solarPanelVoltage;

    RenogyMPPT mppt;
    ShuntPowerData bms;
    JsonDocument data;

    int getData();
private:
    // 
    bool error(uint8_t index);
    void formatRenogyData();
    void formatVictronData();
    void hStatsVictron(uint8_t index);

};
#endif // POWERINFO_H