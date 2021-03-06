#include <uStepper.h>

#define MAXACCELERATION 20000         //Max acceleration = 20000 Steps/s^2
#define MAXVELOCITY 4000          //Max velocity = 4000 steps/s


uStepper stepper(MAXACCELERATION, MAXVELOCITY);
int a;
int D;
int cmd = 0;
int d;
int n;
int moving;
int pinState = LOW;
int trigger_period = 500; // hold camera trigger in ms
int anti_shake_period =1000; // delay to allow things to stop vibrating

const int camera_trigger = PD2;

void setup() {
  // put your setup code here, to run once:
  stepper.setup();
  Serial.begin(115200);
  pinMode(camera_trigger, OUTPUT);
  digitalWrite(camera_trigger,HIGH); // not triggered
  
}

void loop() {
  char cmd;


  // read command
  while (Serial.available() > 0) {
    cmd=Serial.parseInt(); // 1 is just a move 2 is take a photo too
    D=Serial.parseInt(); // 1 for CW and -1 for CCW
    d=Serial.parseInt(); // distance in uM
    n=Serial.parseInt(); // number of repetitons
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
      stepper.hardStop(SOFT); // disables motor too
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
        stepper.hardStop(SOFT); // disables motor too
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
        stepper.hardStop(SOFT); // disables motor too

        // take photo
        delay(anti_shake_period); // wait for vobration to settle
        digitalWrite(camera_trigger,LOW); // Camera triggered
        delay(trigger_period);
        digitalWrite(camera_trigger,HIGH); // Camera NOT triggered
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
        stepper.hardStop(SOFT); // disables motor too

        // take photo
        delay(anti_shake_period); // wait for vobration to settle
        digitalWrite(camera_trigger,LOW); // Camera triggered
        delay(trigger_period);
        digitalWrite(camera_trigger,HIGH); // Camera NOT triggered
      }
    }
   }
}



 

