#include <math.h>
#include <Stepper.h>

int buttonPin = 12;

int in1Pin1 = 11, in2Pin1 = 10, in3Pin1 = 9, in4Pin1 = 8;
int in1Pin2 = 7, in2Pin2 = 6, in3Pin2 = 5, in4Pin2 = 4;
Stepper motor1(64, in1Pin1, in3Pin1, in4Pin1, in2Pin1);
Stepper motor2(64, in1Pin2, in3Pin2, in4Pin2, in2Pin2);


boolean debug = false;
boolean print_lines = false;
boolean testConversions = false;


int buttonState;

float tStep = 0.1;

float stepsToAngleConv = 1000/2/3.14159 * 10; //by measurmants + make the drawing 10 times larger
float stepsToDistanceConv = 1000/218;


float curX = 0; //current X coord
float curY = 0; //current Y coord
float curA = 0; //current angle

void setup()
{
  while (!Serial);
  Serial.begin(9600);
  motor1.setSpeed(100);
  motor2.setSpeed(100);
  pinMode(buttonPin, INPUT_PULLUP);

  Serial.println("READY");  
}



void loop() {
  buttonState = digitalRead(buttonPin);

  if (buttonState == LOW) {     
    if (testConversions){
      //set stepsToDistanceConv = 1000 (units: steps/mm)
      //measure the distance (in mm) the robot passes 
      //set stepsToDistanceConv = 1000/mm
      forward(1); 
      //set stepsToAngleConv = 1000 (units: steps/radians)
      //measure the angle (in radians) the robot turns 
      //set stepsToAngleConv = 1000/radians
      turn(1);
    }else{
      drawSVG();  
      delay(3000);
    }
  }

  delay(500);
}
