const int switchPin = 2;
const int motorPin = 9;
const int potPin = A0;
int potVal;
int switchState = 0;

void setup() {
  pinMode(motorPin, OUTPUT);
  pinMode(switchPin, INPUT);

  Serial.begin(9600);

}

void loop() {
  switchState = digitalRead(switchPin);

  potVal = analogRead(potPin);
  Serial.print("potVal/4: ");
  Serial.println(potVal/4);

//  analogWrite(motorPin, potVal / 4);
  
  if (switchState == HIGH) {
    // digitalWrite(motorPin, HIGH);
    analogWrite(motorPin, potVal / 4);
  }
  else {
    // digitalWrite(motorPin, LOW);
    analogWrite(motorPin, LOW);
  }
  

}
