#include "camera_handler.h"
#include <ArduCAM.h>
#include <SPI.h>

// Camera instance
ArduCAM myCAM(CAM_TYPE, CS_PIN);

// Global buffer for captured image
uint8_t* capturedImage = nullptr;
size_t capturedImageSize = 0;

void initCamera() {
    Serial.println("[Camera] Initializing SPI...");
    pinMode(CS_PIN, OUTPUT);
    digitalWrite(CS_PIN, HIGH);
    SPI.begin();

    delay(100);

    Serial.println("[Camera] Resetting sensor...");
    myCAM.write_reg(0x07, 0x80);  // software reset
    delay(100);
    myCAM.write_reg(0x07, 0x00);
    delay(100);

    uint8_t sensorID = myCAM.read_reg(0x0A);
    Serial.print("[Camera] Sensor ID: 0x");
    Serial.println(sensorID, HEX);
    if (sensorID == 0 || sensorID == 0xFF) {
        Serial.println(" Camera not responding. Check wiring and power.");
        return;
    }

    Serial.println("[Camera] Setting JPEG format...");
    myCAM.set_format(JPEG);
    myCAM.InitCAM();
    myCAM.OV2640_set_JPEG_size(OV2640_1600x1200);  // Adjust resolution here
    delay(500);

    Serial.println("✅ Camera initialization complete.");
}

bool captureImage() {
    Serial.println("[Camera] Flushing FIFO...");
    myCAM.flush_fifo();
    myCAM.clear_fifo_flag();

    Serial.println("[Camera] Starting image capture...");
    myCAM.start_capture();

    unsigned long startTime = millis();
    while (!myCAM.get_bit(ARDUCHIP_TRIG, CAP_DONE_MASK)) {
        if (millis() - startTime > 5000) {
            Serial.println(" Timeout waiting for image capture.");
            return false;
        }
    }

    Serial.println("✅ Capture complete.");

    size_t imageSize = myCAM.read_fifo_length();
    Serial.print("[Camera] Image size: ");
    Serial.print(imageSize / 1024.0, 2);
    Serial.println(" KB");

    if (imageSize == 0 || imageSize > 30000) {
        Serial.println(" Invalid image size.");
        return false;
    }

    // Free previous buffer if needed
    if (capturedImage != nullptr) {
        free(capturedImage);
        capturedImage = nullptr;
    }

    capturedImage = (uint8_t*)malloc(imageSize);
    if (!capturedImage) {
        Serial.println(" Memory allocation failed.");
        return false;
    }

    myCAM.CS_LOW();
    myCAM.set_fifo_burst();
    for (size_t i = 0; i < imageSize; i++) {
        capturedImage[i] = SPI.transfer(0x00);
    }
    myCAM.CS_HIGH();

    capturedImageSize = imageSize;
    Serial.println("🖼️ Image captured and stored in memory.");
    return true;
}

bool sendCapturedImage() {
    if (capturedImage == nullptr || capturedImageSize == 0) {
        Serial.println("⚠️ No captured image to send.");
        return false;
    }

    Serial.println("📤 Sending image over serial...");
    Serial.write("IMG_START", 9);
    Serial.write(capturedImage, capturedImageSize);
    Serial.write("IMG_END", 7);
    Serial.println("✅ Image sent.");
    return true;
}
