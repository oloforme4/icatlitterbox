#include <SoftwareSerial.h>
#define R 10  //กำหนดขาที่นำไปต่อกับรีเลย์
#define L 9
const int homeSwitchPin1 = 12; //limit switch const
const int homeSwitchPin2 = 13; //limit switch const
const int homeSwitchPin3 = 8; //limit switch const
//Code By ArduinoALL
SoftwareSerial ArduinoSerial(3, 2); // RX, TX
void setup() {
  Serial.begin(115200);
  ArduinoSerial.begin(4800);
  pinMode(homeSwitchPin1 , INPUT);
  pinMode(homeSwitchPin2 , INPUT);
  pinMode(homeSwitchPin3 , INPUT);
  digitalWrite(homeSwitchPin1, HIGH);
  digitalWrite(homeSwitchPin2, HIGH);
  digitalWrite(homeSwitchPin3, HIGH);
  pinMode(R, OUTPUT);
  pinMode(L, OUTPUT);
}
void loop() {
  while (ArduinoSerial.available() > 0) {
    float val = ArduinoSerial.parseFloat();
    if (ArduinoSerial.read() == '\n') {
      Serial.println(val);
      if (val == 120) {
        digitalWrite(R, HIGH);
        digitalWrite(L, LOW);
        Serial.println("Relay ON");
        Serial.println("LOOP0");
        for (int i = 0; i < 80; i++){
            Serial.print(". ");
            delay(1000);
          }        
      }
      while (val == 120) { //เมื่อรับค่า serial มาจาก NodeMCU 120
        int homeSw1 = digitalRead(homeSwitchPin1);
        int homeSw2 = digitalRead(homeSwitchPin2);
        int homeSw3 = digitalRead(homeSwitchPin3);
        if (homeSw2 == HIGH && homeSw1 == LOW) {
          digitalWrite(R, LOW);
          digitalWrite(L, HIGH);
          Serial.println("Relay ON");
          Serial.println("LOOP1"); //ccw
          Serial.println("dalay 10 sec");
          for (int i = 0; i < 104; i++){
            Serial.print(". ");
            delay(1000);
          }
          Serial.println("next loop");
        }
        if (homeSw2 == LOW && homeSw1 == HIGH) {
          digitalWrite(R, HIGH);
          digitalWrite(L, LOW);
          Serial.println("Relay ON");
          Serial.println("LOOP2");//cw
          delay(500);
        }
        if (homeSw3 == LOW && homeSw1 == HIGH && homeSw2 == HIGH) {
          digitalWrite(R, LOW);
          digitalWrite(L, LOW);
          Serial.println("Relay ON");
          Serial.println("LOOP3"); //motor off
          Serial.println("End loop");
          break;
        }
      }
    }
  }
}
