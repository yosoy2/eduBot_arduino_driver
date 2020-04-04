#include <Arduino.h>

// rele
const int rele = 13;

void setup(/* arguments */) {
  /* code */
  Serial.begin(9600);
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(rele, OUTPUT);
  digitalWrite(rele, LOW);
}

void loop(/* arguments */) {
  /* code */
  //pinMode(LED_BUILTIN, HIGH);
  //delay(1000);
  //pinMode(LED_BUILTIN, LOW);
  //delay(100);
  digitalWrite(rele, HIGH);
  Serial.println("OFF");
  delay(1000);
  digitalWrite(rele, LOW);
  Serial.println("ON");
  delay(1000);
}
