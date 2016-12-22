#include <Arduino.h>
#include <Wire.h>
#include <HardwareSerial.h>

#include "Types.h"
#include "Accel.h"
#include "Magn.h"
#include "Gyro.h"

//Prototype declaration
typedef void(*FunctionPointer)();

Sensor *sensors[3]; // The Sensor array index 0 = Accel, 1 = Magn, 2 = Gyro
FunctionPointer SerialSend;
bool stream = false;
unsigned long freq = 20;

void calculateLRC(byte *data, uint8_t size, byte *LRC) {
    DMSG("calculateLRC");
    *LRC = 0;
    for (uint8_t i = 0; i < size; i++) {
        *LRC ^= data[i];
    }
}

void I2C_Init() {
    Wire.begin();
}

void ByteSend() {
    byte *data = new byte[37]; // Data from sensors plus checksum
    uint8_t j = 0;
    for (int8_t i = 0; i < 36; i += 12) {
        byte *p = reinterpret_cast<byte *>(sensors[j++]->getXYZ()); // Reinterpret the data as bytes
        memcpy(&data[i], p, 12); // Copy to array
    }
    calculateLRC(data, 36, &data[37]); // Calculate the Longitudinal Reduncy Check
    Serial.write(data, 37); // Send data over UART
    delete[] data;
}

void TextSend() {
    //Serial.println("A:" + String(sensors[0]->getXYZ()[0]) + "," + String(sensors[0]->getXYZ()[1]) + "," +
    //               String(sensors[0]->getXYZ()[2]));
    //Serial.println("M:" + String(sensors[1]->getXYZ()[0]) + "," + String(sensors[1]->getXYZ()[1]) + "," +
    //               String(sensors[1]->getXYZ()[2]));
    Serial.println(/*"G:" + */String(sensors[2]->getXYZ()[0]) + "," + String(sensors[2]->getXYZ()[1]) + "," +
                   String(sensors[2]->getXYZ()[2]));
}

void SpeedProfile(uint8_t profile) {
    // Set the ADXL345 Range
    sensors[0]->SpeedProfile(profile);
}

void SetCalibrationProfile() {

}

void setup() {
    Serial.begin(OUTPUT__BAUD_RATE); // Init Serial

    // Init Status Led;
    pinMode(STATUS_LED_PIN, OUTPUT);

    for (int i = 0; i < 10; i++) {
        pinMode(STATUS_LED_PIN, LOW);
        delay(200);
        pinMode(STATUS_LED_PIN, HIGH);
        delay(200);
    }

    // Init Sensors
    delay(50); // Give sensors time to start up
    I2C_Init();
    sensors[0] = new Accel();
    sensors[1] = new Magn();
    sensors[2] = new Gyro();
    delay(20); // Give sensors time to collect data

    // Init the Serial Send function
    SerialSend = &ByteSend;
}

void loop() {
    if (Serial.available() >= 2) {
        if (Serial.read() == '#') { // Start of control message
            int command = Serial.read();
            switch (command) {
                case 102: //f -> request frame
                    for (uint8_t i = 0; i < 3; i++) { // Read the sensors
                        sensors[i]->read();
                    }
                    SerialSend(); // Send data over UART
                    break;
                case 116: //t -> request frame in text
                    SerialSend = &TextSend; // set function pointer to Text send function
                    break;
                case 98: //b -> request frame in binary
                    SerialSend = &ByteSend; // set function pointer to Byte send function
                    break;
                case 48: //0 -> stop stream
                    stream = false;
                    break;
                case 49: //1 -> start stream
                    stream = true;
                    break;
                case 75: //u -> set update frequency
                    freq = static_cast<unsigned long>(1000 / (Serial.read() + 1));
                    if (freq < 20) {
                        freq = 20;
                    }
                    break;
                case 115: //s -> set travelspeed of IMU is it attached to slow moving vehicle or fast moving
                    SpeedProfile(static_cast<int>(Serial.read()));
                    break;
                case 99: //c -> Calibration profile expect an array of 15 floats, format XYZ
                    SetCalibrationProfile();
                    break;
                default: // unknown command do nothing
                    break;

            }
        }
    }

    if (stream) {
        for (uint8_t i = 0; i < 3; i++) { // Read the sensors
            sensors[i]->read();
        }
        SerialSend(); // Send data over UART
    }
    delay(freq);
}
