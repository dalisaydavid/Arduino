int val = 0; //value for storing moisture value 
int soilPin = A0;//Declare a variable for the soil moisture sensor 
int soilPower = 7;//Variable for Soil moisture Power

int isWetPin = 3;
int isDryPin = 2;

int buttonPin = 12;
int buttonState = 0;
int buttonPushCount = 0;
int lastButtonState = 0;

int canReadSoil = 0;

//Rather than powering the sensor through the 3.3V or 5V pins, 
//we'll use a digital pin to power the sensor. This will 
//prevent corrosion of the sensor as it sits in the soil. 

void setup() 
{
  Serial.begin(9600);   // open serial over USB

  pinMode(soilPower, OUTPUT);//Set D7 as an OUTPUT
  digitalWrite(soilPower, LOW);//Set to LOW so no power is flowing through the sensor

  pinMode(isWetPin, OUTPUT);
  digitalWrite(isWetPin, LOW);
  pinMode(isDryPin, OUTPUT);
  digitalWrite(isDryPin, LOW);

  pinMode(buttonPin, INPUT);

}

void loop() {
  buttonState = digitalRead(buttonPin);

  if (buttonState != lastButtonState and buttonState == LOW){
    canReadSoil = (buttonPushCount % 2 == 0);

    buttonPushCount++;
    Serial.print("Pressed button. buttonPushCount: ");
    Serial.println(buttonPushCount);
  }

  if (canReadSoil){
      Serial.print("Soil Moisture = ");
      int soil_value = readSoil();
      Serial.println(soil_value);
      
      if (soil_value >= 885) { // It's wet! Nice and watered.
        digitalWrite(isWetPin, HIGH);
        digitalWrite(isDryPin, LOW);
      }
      else {
        digitalWrite(isWetPin, LOW);
        digitalWrite(isDryPin, HIGH);
      }

      //This 1 second timefrme is used so you can test the sensor and see it change in real-time.
      //For in-plant applications, you will want to take readings much less frequently.
      delay(1000);//take a reading every second
  }
  else{
    digitalWrite(isWetPin, LOW);
    digitalWrite(isDryPin, LOW);
  }

  lastButtonState = buttonState;

}
//This is a function used to get the soil moisture content
int readSoil()
{

    digitalWrite(soilPower, HIGH);//turn D7 "On"
    delay(10);//wait 10 milliseconds 
    val = analogRead(soilPin);//Read the SIG value form sensor 
    digitalWrite(soilPower, LOW);//turn D7 "Off"
    return val;//send current moisture value
}
