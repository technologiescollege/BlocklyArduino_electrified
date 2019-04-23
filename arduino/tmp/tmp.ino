#include <SoftwareSerial.h>

SoftwareSerial liaison_BT(4,5);

String donnee;

void setup() {
  liaison_BT.begin(9600);
  Serial.begin(9600);

}

void loop() {
    if (liaison_BT.available()) {
      donnee = liaison_BT.readStringUntil('F');
      Serial.println(donnee);

    }

}