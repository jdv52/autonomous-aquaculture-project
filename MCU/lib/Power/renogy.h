#ifndef RENOGY_H
#define RENOGY_H

// functional modbus implementation. very messy. replaces previous library which filled 0s to failed reads.

#include <Arduino.h>
#include <ModbusMaster.h>

// A struct to hold the controller data
struct Controller_data {
    uint8_t battery_soc;               // percent
    float battery_voltage;             // volts
    float battery_charging_amps;       // amps
    uint8_t battery_temperature;       // celcius
    uint8_t controller_temperature;    // celcius
    float load_voltage;                // volts
    float load_amps;                   // amps
    uint8_t load_watts;                // watts
    float solar_panel_voltage;         // volts
    float solar_panel_amps;            // amps
    uint8_t solar_panel_watts;         // watts
    float min_battery_voltage_today;   // volts
    float max_battery_voltage_today;   // volts
    float max_charging_amps_today;     // amps
    float max_discharging_amps_today;  // amps
    uint8_t max_charge_watts_today;    // watts
    uint8_t max_discharge_watts_today; // watts
    uint8_t charge_amphours_today;     // amp hours
    uint8_t discharge_amphours_today;  // amp hours
    uint8_t charge_watthours_today;    // watt hours
    uint8_t discharge_watthours_today; // watt hours
    uint8_t controller_uptime_days;    // days
    uint8_t total_battery_overcharges; // count
    uint8_t total_battery_fullcharges; // count

    // convenience values
    float battery_temperatureF;        // fahrenheit
    float controller_temperatureF;     // fahrenheit
    float battery_charging_watts;      // watts. 
    long last_update_time;             // millis() of last update time
    bool controller_connected;         // bool if we successfully read data from the controller
};

// A struct to hold the controller info params
struct Controller_info {
    uint8_t voltage_rating;            // volts
    uint8_t amp_rating;                // amps
    uint8_t discharge_amp_rating;      // amps
    uint8_t type;
    uint8_t controller_name;
    char software_version[40];
    char hardware_version[40];
    char serial_number[40];
    uint8_t modbus_address;

    float wattage_rating;
    long last_update_time;           // millis() of last update time
};

class RenogyMPPT {
public:
    RenogyMPPT(int modbus_address = 255);
    void renogy_read_data_registers();
    void renogy_read_info_registers();
    
    Controller_data renogyData;
    Controller_info renogyInfo;
private:
    ModbusMaster node;
    const uint32_t num_data_registers = 35;
    const uint32_t num_info_registers = 17;
};

// TODO: LOAD CONTROLLER

#endif // RENOGY_H