#include <Adafruit_TCS34725.h>

// For the convenient debugging and processing datas, Use Class in C++
class RGB {
  private:
    float R,G,B;

  public:
    // Constructor
    RGB(float r, float g, float b) : R(r), G(g), B(b) {}

    // For the Classification, we needs maximum value
    float max_RGB() {
      float max_RGB = R;
      if (G > max_RGB) max_RGB = G;
      if (B > max_RGB) max_RGB = B;
      
      return max_RGB;
    }
    
    char Classification() {
      float color = max_RGB();
      
      if (color == R) return 'R';
      if (color == G) return 'G';
      if (color == B) return 'B';
    }
};

#define LED_RED 5
#define LED_GREEN 6
#define LED_BLUE 7
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
uint16_t r, g, b, c; // red, green, blue, clear

void setup() {
  DDRD = 0xFF;  
  Serial.begin(9600);
  if (tcs.begin()) {
    Serial.println("TCS34725 ready");
  } 
  else {
    Serial.println("TCS34725 initialization failed");
  }
}

void loop() {
  
  tcs.setInterrupt(false); // in situation getting datas, Disable interrupts
  delay(50);
  tcs.getRawData(&r, &g, &b, &c); // Get RGB datas
  tcs.setInterrupt(true); 

  r = r / float(c) * 255*1.5;
  g = g / float(c) * 255*1.07;
  b = b / float(c) * 255*1.28;
  
  RGB RGB_Test(r,g,b);
  char Color = RGB_Test.Classification();
  Serial.println(Color);
  
  if (Color == 'R') PORTD = (1 << LED_RED);
  if (Color == 'G') PORTD = (1 << LED_GREEN);
  if (Color == 'B') PORTD = (1 << LED_BLUE);
  delay(50);
}
