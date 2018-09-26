#include <Arduino.h>
#line 1 "F:\\Logiciels\\Arduino_graphique\\BlocklyArduino_electrified\\resources\\compilation\\ino\\sketch.ino"
#line 1 "F:\\Logiciels\\Arduino_graphique\\BlocklyArduino_electrified\\resources\\compilation\\ino\\sketch.ino"
#line 1 "F:\\Logiciels\\Arduino_graphique\\BlocklyArduino_electrified\\resources\\compilation\\ino\\sketch.ino"
void setup();
#line 5 "F:\\Logiciels\\Arduino_graphique\\BlocklyArduino_electrified\\resources\\compilation\\ino\\sketch.ino"
void loop();
#line 1 "F:\\Logiciels\\Arduino_graphique\\BlocklyArduino_electrified\\resources\\compilation\\ino\\sketch.ino"
void setup() {
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(1000);

}
