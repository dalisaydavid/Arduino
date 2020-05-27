#include <LiquidCrystal.h>
#include "Volume.h"
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int switchPin = 6;
int switchState = 0;
int prevSwitchState = 0;

int cursorColumn = 0;
const int maxColumns = 16;

int randomColumn = 0;
bool winner = false;

int endColumn = maxColumns;
int columnMovement = 1;
int level = 0;
int rounds = 0;
const int roundsPerLevel = 3;
int levelSpeed = 10;

const int potPin = A0;
int potVal = 0;

void setup() {
  lcd.begin(16, 2);
  pinMode(switchPin, INPUT);

  lcd.print("Begin!");

  Serial.begin(9600);
  
  randomSeed(analogRead(0));
  randomColumn = random(16);
}

void loop() {
  potVal = analogRead(potPin);
  switchState = digitalRead(switchPin);

  
  int levelDelay = 100-(levelSpeed*level);
  if (levelDelay <= 0){
    levelDelay = 0;
  }


  lcd.clear();
  lcd.setCursor(cursorColumn, 0);
  lcd.print("X");

  lcd.setCursor(randomColumn, 1);
  lcd.print("X");

  Serial.print("prevSwitchState: ");
  Serial.print(prevSwitchState);
  Serial.print(", switchState: ");
  Serial.print(switchState);
  Serial.print(", cursorColumn: ");
  Serial.print(cursorColumn);
  Serial.print(", randomColumn: ");
  Serial.println(randomColumn);
  if (prevSwitchState == LOW && switchState == HIGH && cursorColumn >= (randomColumn-1) && cursorColumn <= (randomColumn+1)){
    cursorColumn = 0;
    randomColumn = random(16);

    if (randomColumn < 5){
      cursorColumn = maxColumns;
      endColumn = 0;
      columnMovement = -1;
    }
    else {
      cursorColumn = 0;
      endColumn = maxColumns;
      columnMovement = 1;
    }
    
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.println("Nice!");

    if (rounds >= roundsPerLevel){
      rounds = 0;
      level += 1;
    }

    rounds += 1;
    delay(750);
    return;
  }

  if (cursorColumn == endColumn){
    cursorColumn = 0;
    randomColumn = random(16);
   
    if (randomColumn < 5){
      cursorColumn = maxColumns;
      endColumn = 0;
      columnMovement = -1;
    }
    else {
      cursorColumn = 0;
      endColumn = maxColumns;
      columnMovement = 1;
    }
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("Missed.");
    delay(250);
  }
  prevSwitchState = switchState;
  cursorColumn += columnMovement;

  int tones [] = {262, 294, 330};
  
  tone(8, tones[random(0,3)], levelDelay);

//  noTone(8);

  delay(levelDelay);

  
}
