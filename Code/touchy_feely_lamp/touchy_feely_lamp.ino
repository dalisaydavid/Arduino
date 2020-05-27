#include <CapacitiveSensor.h>
CapacitiveSensor capSensor = CapacitiveSensor(4,2); // pin 4 sends to the conductive sensor through the resistor, pin 2 is the sense pin.

int threshold = 1000;
const int ledPin = 12;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);

}

void loop() {
  long sensorValue = capSensor.capacitiveSensor(30);
  Serial.println(sensorValue);

  if (sensorValue > threshold){
    digitalWrite(ledPin, HIGH);
  }
  else {
    digitalWrite(ledPin, LOW);
  }
  delay(10);

}
