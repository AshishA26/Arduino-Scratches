// function to Increase one of the colors
void LEDIncrease(int a) {
  for (int i = 0; i <= 255; i++) {
    analogWrite (a, i);
    delay(10);
  }
}
//function to Decrease one of the colors
void LEDDecrease(int b) {
  for (int i = 255; i >= 0; i--) {
    analogWrite (b, i);
    delay(10);
  }
}
void setup() {
  // put your setup code here, to run once:
#define Red 6
#define Green 5
#define Blue 3
  //Set pin types:
  pinMode (Red, OUTPUT);
  pinMode (Green, OUTPUT);
  pinMode (Blue, OUTPUT);
  //Set starting color (Red is on, Green and Blue are off)
  digitalWrite (Red, HIGH);
  digitalWrite (Green, LOW);
  digitalWrite (Blue, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Call on both functions to one at a time decrease and increase colors
  LEDIncrease(Blue);
  LEDDecrease(Red);
  LEDIncrease(Green);
  LEDDecrease(Blue);
  LEDIncrease(Red);
  LEDDecrease(Green);
}
