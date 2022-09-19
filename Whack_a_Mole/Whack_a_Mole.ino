#include <Servo.h>
Servo myServo;
// assign LEDs and button to pins
int playerOneWins = 0;
int playerTwoWins = 0;
boolean resetButton = false;
int const potPin = A0;
int ledPin[] = {4,5,6};
int ledPin2[] = {7,8,10};
int ledPinWin[] = {4,5,6,9};
int ledPinWin2[] = {7,8,10,11};
int playerOneButton = 2;
int playerTwoButton = 3;
int whiteLED = 9;
int whiteLED2 = 11;
int playerOneScore = 0;
int playerTwoScore = 0;
// declare variables
int delayTime = 400; // time delay between lights on/off
int randNumber;
int randNumber2;
int whiteLEDOn; 
int whiteLEDOn2;
bool playerOneButtonOn = false;
bool playerTwoButtonOn = false;
//setup interrupt, button input and LED outputs
void setup() {
  myServo.attach(13); 
  attachInterrupt(0, playerOneInput, FALLING); // specify interrupt routine for button 1
  attachInterrupt(1, playerTwoInput, FALLING); // specify interrupt routine for button 2
  for (int i=0; i<3; i++){
    pinMode(ledPin[i], OUTPUT); //assign led pins as output
    pinMode(ledPin2[i], OUTPUT);//assign led pins as output
  }
  pinMode(playerOneButton, INPUT); //assign button 1 as input
  pinMode(playerTwoButton, INPUT); //assign button 2 as input
  pinMode(whiteLED, OUTPUT); //assign whiteLED as output
  pinMode(whiteLED, OUTPUT); //assign blueLED as output
}

//run main program loop
void loop() {

  delayTime = map(analogRead(potPin), 0, 1023, 500, 2000); //changes the delay time between LED's turning on and off based on the potometer
  if (playerOneScore < playerTwoScore){
    myServo.write(30); //servo points towards player two 
  }
  else{
    if(playerOneScore > playerTwoScore){
      myServo.write(149); //servo points towards player one
    }
    else{
      myServo.write(90); //servo points inbetween both players
    }
  }
  if ((playerOneScore <= 10 && playerTwoScore <= 10) || (resetButton == true)){
    resetButton = false;
    randNumber = random(3); // select a random number
    randNumber2 = random(3); // select a random number
    digitalWrite(ledPin[randNumber], HIGH); // light the LED with this number
    digitalWrite(ledPin2[randNumber2], HIGH); // light the LED with this number
    delay(delayTime); 
    digitalWrite(ledPin[randNumber], LOW); //turn's all LED's off
    digitalWrite(ledPin2[randNumber2], LOW); //turn's all LED's off
    delay(1500);
    whiteLEDOn = digitalRead(whiteLED); 
    whiteLEDOn2 = digitalRead(whiteLED2);
    //turns off score indicating LED's and allows buttons to be used again
      if(whiteLEDOn=HIGH){
        digitalWrite(whiteLED, LOW);
        playerOneButtonOn = false;
        }
      if(whiteLEDOn2=HIGH){
         digitalWrite(whiteLED2, LOW);
         playerTwoButtonOn = false;
        }
  }
  else{
    //if the reset button is pressed, it resets the scores to 0 and puts the servo back to the middle
    if(digitalRead(12) == LOW){ 
      resetButton = true;
      playerOneScore = 0;
      playerTwoScore = 0;
      myServo.write(90);
    }
   
    if (playerOneScore > playerTwoScore){
      for (int i = 0; i < 4; i++){
      digitalWrite(ledPinWin[i], HIGH); //turn all of player one's LEDs on
      }
    delay(500);//wait half a second
    for (int i = 0; i < 4; i++){
      digitalWrite(ledPinWin[i], LOW); //turn all of player one's LEDss off
    }
    delay(500);
    myServo.write(0);
      }
    else{
      for (int i = 0; i < 4; i++){
      digitalWrite(ledPinWin2[i], HIGH); //turn all of player two's LEDs on
      }
    delay(500);
    for (int i = 0; i < 4; i++){
      digitalWrite(ledPinWin2[i], LOW); //turn all of player two's LEDs off
    }
    delay(500);
    myServo.write(179);
    }
    
    }
  }


//function that checks if player has scored a point

void playerOneInput() {
  if (playerOneButtonOn == false){
    playerOneButtonOn = true; //boolean prevents player from pressing the button multiple times to score more points

    // if the LED is on when the button was pressed, add one to the players score and turn on the point indicating LED
    if (digitalRead(ledPin[randNumber]) == HIGH){
      digitalWrite(whiteLED, HIGH); 
      playerOneScore = playerOneScore + 1;
    }
    else{
      if (digitalRead(ledPin[randNumber]) == LOW){
        digitalWrite(whiteLED, LOW);
      }    
    }
  }

}


void playerTwoInput() {
  if (playerTwoButtonOn == false){
    playerTwoButtonOn = true; //boolean prevents player from pressing the button multiple times to score more points

    // if the LED is on when the button was pressed, add one to the players score and turn on the point indicating LED
    if (digitalRead(ledPin2[randNumber2]) == HIGH){
      digitalWrite(whiteLED2, HIGH); 
      playerTwoScore = playerTwoScore + 1;
    }
  else{
    if (digitalRead(ledPin2[randNumber2]) == LOW){
      digitalWrite(whiteLED2, LOW);  
    }    
  }

}
}
