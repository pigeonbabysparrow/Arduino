int left_LED_Pins[] = {5, 6, 7};
int right_LED_Pins[] = {8, 9, 10};
int LED_Count = sizeof(left_LED_Pins) / sizeof(int);

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < LED_Count; i++) {
    pinMode(left_LED_Pins[i], OUTPUT);
    pinMode(right_LED_Pins[i], OUTPUT);
  }
}

void loop() {
  if (Serial.available()) {
    char ch = Serial.read(); // For testing, Serial monitor has to be gotten something character.  

    if (ch == 'C') {
      return; // input "C" means getting to stop
    } 
    else if (ch == 'L') {
      while (!Serial.available()) { // Repeat until the value of the input is C
        LightLed(left_LED_Pins, LED_Count);
      }
    } else if (ch == 'R') {
      while (!Serial.available()) { // Repeat until the value of the input is C
        lightLed(right_LED_Pins, LED_Count);
      }
    }
  }
}

void Light_LED(int LED_Pins[], int count) {
  for (int i = 0; i < count; i++) {
    digitalWrite(ledPins[i], HIGH); // LED Light on
    delay(200);
    digitalWrite(ledPins[i], LOW); // LED Light off
  }
}