// Setting up 6 TCS34725 sensors together and reading their output values
// TCA9548A

#include <Wire.h>
#include "Adafruit_TCS34725.h"

#define  inPin  7
#define  rPin   8
#define  gPin   9
#define  bPin   10

byte multiAddress = 0x70;
byte count = 0;
int currentTime = 0;

char data[6][3] = {{'r', 'g', 'b'},
                 {'r', 'g', 'b'},
                 {'r', 'g', 'b'},
                 {'r', 'g', 'b'},
                 {'r', 'g', 'b'},
                 {'r', 'g', 'b'}};
Adafruit_TCS34725 tcs[] = {Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X),
                           Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X),
                           Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X),
                           Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X),
                           Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X),
                           Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X)};
byte gammatable[256];

void setup(){
    Serial.begin(9600);
    Wire.begin();
    pinMode(inPin, INPUT_PULLUP);
    pinMode(rPin, OUTPUT);
    pinMode(gPin, OUTPUT);
    pinMode(bPin, OUTPUT);
    // gammatable for more color accuracy when outputting on LED
    for(int i =0; i < 256; i++){
        float x = i;
        x /= 255;
        x = pow(x, 2.5);
        x *= 255;
        gammatable[i] = x;
    }
    initColorSensors();
    attachInterrupt(digitalPinToInterrupt(inPin), changeLED, CHANGE);
}
void loop(){
    //for(int i = 0; i < sizeof(data); i++){ // get all colors... not necessary right now 
    //    readColors(i);
    //}
    for(int i = 0; i < 5; i++){
        readColors(count);
    }
    
}
void changeLED(){
    if(millis() - currentTime > 200){
        count++;
        currentTime = millis();
    }
    if(count > 5){
        count = 0;
    }
   
}
void initColorSensors(){
    for(int i = 0; i < 6; i++){
        Serial.println(i);
        chooseBus(i);
        if (tcs[i].begin()){
            Serial.print("Found sensor "); Serial.println(i+1);
        } else{
            Serial.println("No Sensor Found");
            while (true);
        }
    }
}
void readColors(byte sensorNum){
    chooseBus(sensorNum);
    uint16_t r, g, b, c;
    tcs[sensorNum].getRawData(&r, &g, &b, &c); // reading the rgb values 16bits at a time from the i2c channel
    processColors(r, g, b, c); // processing by dividng by clear value and then multiplying by 256
    //data[sensorNum][0] = r;
    //data[sensorNum][1] = g;
    //data[sensorNum][2] = b;
    Serial.print("R: "); Serial.print(r, DEC); Serial.print(" "); 
    Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
    Serial.print("B: "); Serial.print(b, DEC); Serial.print(" "); Serial.print(c); Serial.print(" ");
    displayLED(r, g, b);
    Serial.println(sensorNum);
}
void processColors(uint16_t r, uint16_t g, uint16_t b, uint32_t c){
        // getting rid of IR component of light
       r /= c;
       g /= c;
       b /= c; 
       // adding it back in 
       r *= 256;
       g *= 256;
       b *= 256;
}
    
void chooseBus(uint8_t bus){
    Wire.beginTransmission(0x70);
    Wire.write(1 << (bus+2)); // will be using 2-7 instead of 0-5 because of convience (placed better on the breadboard)
    Wire.endTransmission();
}
void displayLED(uint16_t r, uint16_t g, uint16_t b){
    if (r > 255 || g > 255 || b > 255){
        analogWrite(rPin, 0);
        analogWrite(gPin, 0);
        analogWrite(bPin, 0);
    } else{
        analogWrite(rPin, gammatable[(int)r]);
        analogWrite(gPin, gammatable[(int)g]);
        analogWrite(bPin, gammatable[(int)b]); 
    }
    
}
