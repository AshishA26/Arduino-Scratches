//Set pin 7 to variable "LED"
#define LED 7
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED as an output.
  pinMode(LED , OUTPUT);
  //pinMode decides whether the specified pin behaves as an input or output
}
 
// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED , HIGH);//turn the LED On by making the voltage HIGH
  // digital write means to write Low (0V Off) or High (5V or 3.3V On)to a digital pin (pin in the digital section of board)
  delay(500);                       // wait half a second
  digitalWrite(LED , LOW);// turn the LED Off by making the voltage LOW
  delay(500);                       // wait half a second
}

//https://www.geekering.com/?p=145
