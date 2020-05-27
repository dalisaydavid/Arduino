int switchState = 0;

void setup() {
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  pinMode(2, INPUT);

}

void loop() {
  switchState = digitalRead(2);

  // the button isn't pressed
  if (switchState == LOW){
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);  
  }
  else { // the button is pressed
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);

    delay(250); // wait for 1/4 second

    // toggle LEDs
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    delay(250);
  }

  

}
