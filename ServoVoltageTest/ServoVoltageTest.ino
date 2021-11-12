#include <Servo.h>

// create a servo object
Servo servo; 

//analog input from the potentiometer
int potPos = A0;

void setup() {
  // link the servo to pin 9, and set the pulse width limits (544ms and 2400ms in this case)
  servo.attach(9, 544,2400);  

  //set the analog pin as an input
  pinMode(potPos, 9);
}

void loop() {
  //store the potentiometer position as a float
  float level = analogRead(potPos);

  //calculate analog data as a voltage
  float voltage = 5*level/1024;

  //make sure the voltage isn't outside the acceptable range
  if(voltage < 0){
    voltage = 0;
  }
  if(voltage > 5){
    voltage = 5;
  }

  //scale voltage to 180 degrees
  servo.write(36 * voltage);

  //give the servo time to move to new position
  delay(15);
}
