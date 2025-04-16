#include "victronFunctions.h"

bool victronChecksum(uint8_t* serialData, size_t dataSize) {
    int checksum = 0;
    for (size_t i = 0; i < dataSize; i++) {
        if (serialData[i] != '\0') {
            checksum = (checksum + serialData[i]) & 255;
        }
        else {
            break;  // buffer isn't full, exit loop.
        }
    }
    return (!checksum);
};

// Clear the stale smartshunt data before reading new data.
void clear(ShuntPowerData& data) {
    data.fields.clear();
    data.labels.clear();
}


void victronParse(ShuntPowerData& data, uint8_t* buffer, size_t buffer_size) {
    std::string label = "";
    std::string field = "";
    clear(data);

    for (size_t i = 0; i < buffer_size; i++) {
        label = "";
        field = "";

        if (buffer[i] == NEWLINE) {
            i++;
            while (i < buffer_size) {
                if (buffer[i] == TAB) {
                    i++;
                    break;
                }
                label += buffer[i];
                i++;
            }
            data.labels.push_back(label);

            if (!label.compare("Checksum")) {
                continue;  // checksum value is not guarenteed to be a char.
            }

            while (i < buffer_size) {
                if (buffer[i] == CRETURN) {
                    break;
                }
                field += buffer[i];
                i++;
            }
            data.fields.push_back(field);
        }
    }
}