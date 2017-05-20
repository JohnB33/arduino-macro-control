#include <uStepper.h>

#define MAXACCELERATION 1500         //Max acceleration = 1500 Steps/s^2
#define MAXVELOCITY 1100           //Max velocity = 1100 steps/s

uStepper stepper(MAXACCELERATION, MAXVELOCITY);
int a;
int D;
int cmd = 0;
int d;
int n;
int moving;


void setup() {
  // put your setup code here, to run once:
  stepper.setup();
  Serial.begin(115200);
}

void loop() {
  char cmd;
    
  // read command
  while (Serial.available() > 0) {
    cmd=Serial.parseInt(); // 1 is just a move 2 is take a photo too
    D=Serial.parseInt(); // 1 for CW and -1 for CCW
    d=Serial.parseInt(); // distance in uM
    n=Serial.parseInt(); // number of steps
  }

  d=d*0.4; // convert um to steps
  

  if(cmd==1)                      // move
  {
    cmd=0; // avoid re-entering loop
    if( D == 1){                  // clockwise
      String stuff = "Moving " + String(d) + " steps forward";

      for(a=0;a<n;a++){
        Serial.println (stuff);
        stepper.moveSteps(d,CW,HARD);
        while(stepper.getMotorState()){
          delay(1);
          }
      }
    } 
     else if( D ==-1)
    {
      String stuff = "Moving " + String(d) + " steps backward";

      for(a=0;a<n;a++){
        Serial.println (stuff);
        stepper.moveSteps(d,CCW,HARD);
        while(stepper.getMotorState()){
          delay(1);
        }
      }
    }
  }

  if(cmd==2)                      // move + take phooto
  {
    cmd=0; // avoid re-entering loop
    if( D == 1){                  // clockwise
      String stuff = "Moving " + String(d) + " steps forward and taking photos";

      for(a=0;a<n;a++){
        Serial.println (stuff);
        stepper.moveSteps(d,CW,HARD);
        while(stepper.getMotorState()){
          delay(1);
        }
      }

    } 
     else if( D ==-1)
    {
      String stuff = "Moving " + String(d) + " steps backward and taking photos";

      for(a=0;a<n;a++){
        Serial.println (stuff);
        stepper.moveSteps(d,CCW,HARD);
        while(stepper.getMotorState()){
          delay(1);
        }
      }
    }
  }
 delay(100);
 
 }

