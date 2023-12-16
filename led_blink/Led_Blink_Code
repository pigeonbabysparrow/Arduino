int leftLedPins[] = {5, 6, 7}; // 왼쪽 LED가 연결된 핀 번호
int rightLedPins[] = {8, 9, 10}; // 오른쪽 LED가 연결된 핀 번호
int ledCount = sizeof(leftLedPins) / sizeof(int); // LED 개수

void setup() {
  Serial.begin(9600); // 시리얼 통신 시작
  for (int i = 0; i < ledCount; i++) {
    pinMode(leftLedPins[i], OUTPUT); // 왼쪽 LED 핀을 출력 모드로 설정
    pinMode(rightLedPins[i], OUTPUT); // 오른쪽 LED 핀을 출력 모드로 설정
  }
}

void loop() {
  if (Serial.available()) { // 시리얼 포트에 데이터가 있을 경우
    char ch = Serial.read(); // 문자 읽기

    if (ch == 'C') {
      return; // 'C'를 입력받으면 동작 중지
    } else if (ch == 'L') {
      while (!Serial.available()) { // 'C'를 입력받을 때까지 반복
        lightLed(leftLedPins, ledCount);
      }
    } else if (ch == 'R') {
      while (!Serial.available()) { // 'C'를 입력받을 때까지 반복
        lightLed(rightLedPins, ledCount);
      }
    }
  }
}

void lightLed(int ledPins[], int count) {
  for (int i = 0; i < count; i++) {
    digitalWrite(ledPins[i], HIGH); // LED 켜기
    delay(200); // 0.5초 대기
    digitalWrite(ledPins[i], LOW); // LED 끄기
  }
}
