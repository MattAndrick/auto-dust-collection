/*
  Dust Collection Automation

  Created By: Matt Jackels
  Created On: 4/6/18

  Senses state change for 20 input sensors, which shall trigger HIGH when a power tool is powered on,
  and opens the corresponding Blast Gate and Air Blower. This is achieved by flipping the Blower
  and Blast Gate output pins to HIGH.
 
 */

//const int blowerPin = 10;
//const int chopSawPin = 12;
const int DEF_DELAY_TIME = 1000;
const int CUST_DELAY_TIME = 5000;
//int sensorInputPins = [20];
//int gateOutputPins = [20];

//****test code***********
int sensorInputPins = [1];
int gateOutputPins = [1];
const int blowerPin = 53;
//************************

void setup() {
  //assign input pins as every even slot from 12 to 52, 
  //and output pins as every odd slot from 13 to 53
  int loopCount = 0;
//  for(int pin = 12; pin <= 52; pin+=2){
//    sensorInputPins[loopCount] = pin;
//    gateOutputPins[loopCount] = pin + 1;
//    pinMode(pin, INPUT);
//    pinMode(pin + 1, OUTPUT);
//  }

//****Test Code***********
  sensorInputPins[0] = 30;
  gateOutputPins[0] = 31;
//************************
}

void loop() {
  bool blowerOn = false;

  for(int i = 0; i < sizeof(sensorInputPins)/sizeof(int); i++){
    int inputState = digitalRead(sensorInputPins[i]);
    int outputState = digitalRead(gateOutputPins[i]);

    if(inputState == HIGH){
      if(outputState == LOW){
        digitalWrite(gateOutputPins[i], HIGH);
      }

      blowerOn = true;
    } else if(inputState == LOW && outputState == HIGH){
      if(sensorInputPins[i] == chopSawPin){
        delay(CUST_DELAY_TIME);
        if(digitalRead(chopSawPin) == LOW){ //tool is still off after delay
          digitalWrite(chopSawPin, LOW);
        }
      } else {
        delay(DEF_DELAY_TIME);
        digitalWrite(gateOutputPins[i], LOW);
      }
    }
  }

  if(blowerOn && digitalRead(blowerPin) == LOW){
    digitalWrite(blowerPin, HIGH);
  } else if(!blowerOn && digitalRead(blowerPin) == HIGH){
    digitalWrite(blowerPin, LOW);
  }

}
