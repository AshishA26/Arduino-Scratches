///* Sweep
//  by BARRAGAN <http://barraganstudio.com>
//  This example code is in the public domain.
//
//  modified 8 Nov 2013
//  by Scott Fitzgerald
//  http://www.arduino.cc/en/Tutorial/Sweep
//*/
//
//#include <Servo.h>
//
//Servo myservo;  // create servo object to control a servo
//Servo myservo2;  // create servo object to control a servo
//// twelve servo objects can be created on most boards
//
//int pos = 0;    // variable to store the servo position
//
//void setup() {
//  myservo.attach(5);  // attaches the servo on pin 9 to the servo object
//    myservo2.attach(6);  // attaches the servo on pin 9 to the servo object
//}
//
//void loop() {
//  myservo.writeMicroseconds(500);              // tell servo to go to position in variable 'pos'
//  myservo2.writeMicroseconds(500); 
//  delay(2000);
//  myservo.writeMicroseconds(1500);              // tell servo to go to position in variable 'pos'
// myservo2.writeMicroseconds(1500); 
//  delay(2000);
//  myservo.writeMicroseconds(2500);              // tell servo to go to position in variable 'pos'
//  myservo2.writeMicroseconds(2500); 
//  delay(2000);
//}


//*************************************************3D RADAR CODE*************************************************//

// Include libraries:
#include <Servo.h>

Servo servo1;
Servo servo2;

// defines variables
int angle = 600;
long duration;
int distance;

void setup() {
  servo1.attach(9);
  servo2.attach(10);

  //Tell servo to go to this angle
  servo1.writeMicroseconds(angle);
  servo2.writeMicroseconds(angle);
  delay(1000);
}

void loop() {
  for (angle = 600; angle <= 2400; angle += 5)
  {
    servo1.writeMicroseconds(angle);
    servo2.writeMicroseconds(angle);
    delay(15);
  }
  for (angle = 2400; angle >= 600; angle -= 5)
  {
    servo1.writeMicroseconds(angle);
    servo2.writeMicroseconds(angle);
    delay(15);
  }
}
//Move vertical servo up by one degree
