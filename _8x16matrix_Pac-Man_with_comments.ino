#include <Wire.h> //Include the libraries.
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>

Adafruit_8x16matrix matrix = Adafruit_8x16matrix();

int APin = 2; //Mark the pins.
int UPin = 13;
int DPin = 11;
int LPin = 12;
int RPin = 10;
int AState = 1; //Create a variable for the button's states.
int UState = 1;
int DState = 1;
int LState = 1;
int RState = 1;
int pixPosX = 0; //Create the variables for the Pac-Man's position.
int pixPosY = 0;
bool isTarCaught = false; //Make a variable for detecting if the target is caught.
int tarPosX = random(0, 15); //Set the target to a random position.
int tarPosY = random(0, 7);
int score = 0; //Make a variable for tracking the score.

void setup() {
  matrix.begin(0x70); //Initialize the screen.
  matrix.setRotation(1); //Turn the screen right.
  matrix.setTextWrap(false); //Make the screen not to wrap.
  pinMode(APin, INPUT_PULLUP); //Initialize the pins.
  pinMode(UPin, INPUT_PULLUP);
  pinMode(DPin, INPUT_PULLUP);
  pinMode(LPin, INPUT_PULLUP);
  pinMode(RPin, INPUT_PULLUP);
  for (int C1 = 15; C1 >= -155; C1--) { //Scroll some text through the screen.
    matrix.print("Pac-Man by Nanohenry 10-9"); //Print the text.
    matrix.writeDisplay(); //Make the text to stay on the screen.
    delay(75); //Wait 75 milliseconds.
    matrix.clear(); //Clear the screen.
    matrix.setCursor(C1, 0); //Set the cursor to the next pixel.
  }

  for (int C2 = 15; C2 >= -55; C2--) { //Scroll some text through the screen.
    matrix.print("Press A"); //Print the text.
    matrix.writeDisplay(); //Make the text to stay on the screen.
    delay(75); //Wait 75 milliseconds.
    matrix.clear(); //Clear the screen.
    matrix.setCursor(C2, 0); //Set the cursor to the next pixel.
  }
menu:
  AState = digitalRead(APin); //Make the program wait until button 'A' is pressed.
  if (AState == 1) {
    goto menu;
  }
}

void loop() {
  AState = digitalRead(APin); //Checks if the buttons are pressed.
  UState = digitalRead(UPin);
  DState = digitalRead(DPin);
  LState = digitalRead(LPin);
  RState = digitalRead(RPin);

  if (isTarCaught == true) { //Checks if the target is caught.
    score = score + 1; //Add one point to score.
    matrix.clear(); //Clear the display.
    matrix.drawLine(1, 4, 3, 6, LED_ON); //Draw a checkmark.
    matrix.drawLine(3, 6, 6, 0, LED_ON);
    matrix.writeDisplay(); //Make the checkmark to stay on the screen.
    delay(1000); //Wait one second (1000 milliseconds = one second).
    tarPosX = random(0, 15); //Set a random position for the target.
    tarPosY = random(0, 7);
    isTarCaught = false; //Mark that the target is not caught.
    pixPosX = 0; //Set the Pac-Man to position zero.
    pixPosY = 0;
    matrix.clear(); //Clear the screen.
  }

  matrix.drawPixel(tarPosX, tarPosY, LED_ON); //"Draw" the target.
  matrix.writeDisplay(); //Make the target to stay on the screen.

  if (UState == 0) { //Move the Pac-Man if buttons are pressed.
    pixPosY = pixPosY - 1;
    matrix.clear();
  }
  if (DState == 0) {
    pixPosY = pixPosY + 1;
    matrix.clear();
  }
  if (LState == 0) {
    pixPosX = pixPosX - 1;
    matrix.clear();
  }
  if (RState == 0) {
    pixPosX = pixPosX + 1;
    matrix.clear();
  }

  matrix.drawPixel(pixPosX, pixPosY, LED_ON); //Draw the Pac-Man.
  matrix.drawPixel((pixPosX + 1), pixPosY, LED_ON);
  matrix.drawPixel(pixPosX, (pixPosY + 1), LED_ON);
  matrix.drawPixel((pixPosX + 1), (pixPosY + 1), LED_ON);
  matrix.writeDisplay(); //Make the Pac-Man stay.

  if (pixPosX == tarPosX && pixPosY == tarPosY) { //Checks if the Pac-Man's cordinates match the target's cordinates.
    isTarCaught = true;
  }
  if ((pixPosX + 1) == tarPosX && pixPosY == tarPosY) {
    isTarCaught = true;
  }
  if (pixPosX == tarPosX && (pixPosY + 1) == tarPosY) {
    isTarCaught = true;
  }
  if ((pixPosX + 1) == tarPosX && (pixPosY + 1) == tarPosY) {
    isTarCaught = true;
  }

  
  if (score == 10) { //Checks if the score is ten.
    for (int C6 = 0; C6 <= 2; C6++) { //Make a firework animation three times.
      matrix.clear(); //Clear the screen.
      matrix.drawPixel(7, 3, LED_ON); //Draw the first pixels.
      matrix.drawPixel(7, 4, LED_ON);
      matrix.drawPixel(8, 3, LED_ON);
      matrix.drawPixel(8, 4, LED_ON);
      matrix.writeDisplay(); //Make the first pixels to stay on the screen.
      delay(500); //Wait 500 milliseconds.
      matrix.clear(); //Clear the screen.
      matrix.drawPixel(6, 2, LED_ON); //Draw the second pixels.
      matrix.drawPixel(9, 2, LED_ON);
      matrix.drawPixel(6, 5, LED_ON);
      matrix.drawPixel(9, 5, LED_ON);
      matrix.writeDisplay(); //Make the second pixels to stay on the screen.
      delay(500); //Wait 500 milliseconds.
      matrix.clear(); //Clear the screen,
      matrix.drawPixel(5, 1, LED_ON); //Draw the third pixels, and so on...
      matrix.drawPixel(10, 1, LED_ON);
      matrix.drawPixel(5, 6, LED_ON);
      matrix.drawPixel(10, 6, LED_ON);
      matrix.writeDisplay();
      delay(500);
      matrix.clear();
      matrix.drawPixel(4, 0, LED_ON);
      matrix.drawPixel(11, 0, LED_ON);
      matrix.drawPixel(4, 7, LED_ON);
      matrix.drawPixel(11, 7, LED_ON);
      matrix.writeDisplay();
      delay(500);
    }
    delay(500); //Wait 500 milliseconds (0,5 seconds).
    matrix.clear(); //Clear the screen.
    for (int C4 = 0; C4 <= 9999999; C4++) { //Repeat 9999999 times, so it's almost indefinite times.
      for (int C5 = 16; C5 >= -210; C5--) { //Scroll some text through the screen.
        matrix.print("To start a new game press Reset."); //Print the text.
        matrix.writeDisplay(); //Make the text to stay on the screen.
        delay(75); //Wait 75 milliseconds.
        matrix.clear(); //Clear the screen.
        matrix.setCursor(C5, 0); //Set the cursor to the next pixel.
      }
    }
  }
  delay(100); //Wait for 100 milliseconds.
}










