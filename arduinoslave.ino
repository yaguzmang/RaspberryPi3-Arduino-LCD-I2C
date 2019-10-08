#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define  led 22
#define  pot A0
 
void setup() {
  pinMode(led,OUTPUT);
  pinMode(pot,INPUT);
  
  // Join I2C bus as slave with address 7
  Wire.begin(0x8);
  
  // Call receiveEvent when data received                
  Wire.onReceive(receiveEvent);
  
  // Setup pin 22 as output and turn LED off
  digitalWrite(led, 0);

  //evento de entrada
  Wire.onRequest(prenrasp);
  
  Serial.begin(9600);
}

void prenrasp(){
    int x = analogRead(pot);
    x= map(x, 0, 1023, 0, 255);
    Serial.println(x);
    Wire.write(x);
}
 
// Function that executes whenever data is received from master
void receiveEvent(int howMany) {
  while (Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    digitalWrite(led, c);
  }
}

void loop() {
  delay(100);
}
