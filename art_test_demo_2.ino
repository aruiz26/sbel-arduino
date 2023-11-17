// Gives two outputs, servo and esc command pin 5 and 6
// Values are for servo vary by 25 degrees
// Values on esc not clear as it controls motor voltage

// One input to read rc receiver values on pin 2
// Triggered by the throttle trigger
// MUST reset arduino after 10 seconds

// Automatically stops after 10 seconds
float totalT = 10*1e6; //in microseconds

#include <Servo.h>

// 
#define RCPin 2
int RCValue;
bool rclock = false; // lock when rc value is reached (1700) or after 10 seconds have occured

Servo servo1;  // create servo object to control a servo
Servo esc1;
int a1 = 25; //amplitude for steering
int a2 = 1; // amplitude for esc

int servo1val;    // servo input
int esc1val;  // esc input

double wperiod = 2*1e-7; // for 5s  oscillation period

void setup() {
  Serial.begin(9600);
  servo1.attach(5);  //green - servo
  esc1.attach(6);  // blue - esc


  pinMode(RCPin, INPUT);
}

void loop() {
  servo1val = 90 + a1*sin(wperiod*micros());
  esc1val = 97 + a2*sin(wperiod*micros());
  // Serial.println(servo1val);
  // Serial.println(esc1val);


  if(rclock==false){
  servo1.write(servo1val);
  esc1.write(esc1val);
  }
  else{
    servo1.write(90); // neutral
    esc1.write(90); // neutral
  }

  RCValue = pulseIn(RCPin, HIGH); //read rc value
  // lock output if RCValue>1700 or 10 seconds have passed
  if( (RCValue>1700) || (micros()>=totalT)){
    rclock = true;
  }

  // For using with serial plotter in arduino IDE
  Serial.print(1000);  // Freeze lower limit on serial plotter
  Serial.print(" ");
  Serial.print(1500);  // Line showing midpoint
  Serial.print(" ");
  Serial.print(2000);  // Freeze upper limit on serial plotter
  Serial.print(" ");
  Serial.println(RCValue);
}
