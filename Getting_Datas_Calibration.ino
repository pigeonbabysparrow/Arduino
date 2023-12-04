#include <Wire.h> // Library for the controls of TCA9548A
#include <Adafruit_TCS34725.h> // TCS34725 Library

// TCA9548A I2C address 
#define TCAADDR 0x70

// TCS34725 Class [INTTIME=154ms, GAIN(Sensitivity)=16X]
Adafruit_TCS34725 tcs[4] = {
  Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_154MS , TCS34725_GAIN_16X),
  Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_154MS , TCS34725_GAIN_16X),
  Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_154MS , TCS34725_GAIN_16X),
  Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_154MS , TCS34725_GAIN_16X)
};

// tcaselect
void tcaselect(uint8_t i) {
  if (i > 7) {
    Serial.println("That pin dosen't exist");
    return;

  Wire.beginTransmission(0x70);
  Wire.write((1 << i)); // Control MUX Module
  Wire.endTransmission();

  Serial.println("Selecting TCA is complete");
}

void setup(void) {
  Serial.begin(115200); // BaudRate, which is 9600, is slow for I2C communication
  Wire.begin();
  Wire.setClock(100000);
  // Set 4 TCS34725 which are sequential to use MUX to I2C module 
  for (uint8_t i = 0; i < 4; i++) {
    tcaselect(i);
    delay(10);
    if (tcs[i].begin()) {
      Serial.print("TCS ");
      Serial.print(i);
      Serial.println(" begins.")
    } 
    else {
      Serial.println("Any sensor is not found");
      // while loop is needed to notify errors to users
      while (1);
    }
  }
  Serial.println("The Setup process is complete.");
}

void loop(void) {
  // Get Raw RGB data from each TCS34725
  for (uint8_t i = 0; i < 4; i++) {
    tcaselect(i);
    uint16_t red, green, blue, clear;
    tcs[i].setInterrupt(false); // Interrupt must be off while getting datas
    tcs[i].getRawData(&red, &green, &blue, &clear);
    tcs[i].setInterrupt(true);

    //////////////////////////////////////////////////////////////////////////
    //                        The Calibration Part                          //
    //    Considering that TCS34725 is always existing dark conditions,     //
    //      Our experimental data determines calibration coefficients.      //
    //////////////////////////////////////////////////////////////////////////
    float red_calb = r / float(c) * 255 * 1.2;
    float blue_calb = b / float(c) * 255 * 1.2;
    float green_calb = g / float(c) * 255 * 1.2;

    Serial.print("Sensor ");
    Serial.print(i);
    Serial.print(" - R: ");
    Serial.print(red_calb);
    Serial.print(" G: ");
    Serial.print(green_calb);
    Serial.print(" B: ");
    Serial.println(blue_calb);
  }

  delay(500);
}
