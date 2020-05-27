byte character[8]={0x0, 0x66, 0x99, 0x81, 0x42, 0x24, 0x18, 0x0};

uint8_t rowPins[8]={10,11,12,13,A0,A1,A2,A3};
uint8_t colPins[8]={ 2, 3, 4, 5, 6, 7, 8, 9};
int PulseSensorPurplePin = A4;
int Signal;                // holds the incoming raw data. Signal value can range from 0-1024
int Threshold = 550;            // Determine which Signal to "count as a beat", and which to ingore.


void setup() {
  // Turn everything to low
  for(int i=0; i<8; i++) {
    pinMode(colPins[i],OUTPUT);
    pinMode(rowPins[i],OUTPUT);
  }
}

void loop() {
   Signal = analogRead(PulseSensorPurplePin);  // Read the PulseSensor's value.
                                              // Assign this value to the "Signal" variable.

   Serial.println(Signal);                    // Send the Signal value to Serial Plotter.



   if(Signal > Threshold){                          // If the signal is above "550", then light up heart shape on 8x8 led matrix
      for(int row=0; row<8; row++) { // iterate each row
        for(int k=0; k<8; k++) digitalWrite(colPins[k],LOW); // Change all columns to low.
        digitalWrite(rowPins[row], LOW); // Change current row to low.
        for(int col=0; col<8; col++) {
          digitalWrite(colPins[7-col], character[row] & 1 << col ? HIGH : LOW); // if current column has a 1, change current column to high, otherwise keep low.
        }
        delay(1);
        digitalWrite(rowPins[row],HIGH);
      }
   } 
   else { // Don't turn on the light up heart shape.

    for(int i=0; i<8; i++) {
      digitalWrite(rowPins[i], HIGH);
      digitalWrite(colPins[i], HIGH);
    }
     
   }

 
}
