#include <ArduinoRobot.h>
#include <Wire.h>
#include <SPI.h>

  int trigPin = TKD3;
  int echoPin = TKD4;
    // pin is used by the sensor
  
void setup() {
  // initialize the Robot, SD card, and display
  Serial.begin(9600);
  Robot.begin();
  Robot.beginTFT();
  Robot.beginSD();
  // draw a face on the LCD screen
  setFace(true);
  //set the motor board into line-follow mode
}

void loop() {
  while (getDistance() > 80) { 
    setFace(false); //shows an unhappy face
    Robot.motorsStop(); // stop the motors
    delay(100); // wait for a moment
    Robot.turn(30); // turn to the right and try again
    setFace(true); // happy face
  }
  
  Robot.motorsWrite(200, 200);
}

// return the distance in cm
float getDistance() {
 // Initialize trigPin
 pinMode(trigPin, OUTPUT);
 Robot.digitalWrite(trigPin, LOW);
 delayMicroseconds(2);

 // Trigger trigPin
 Robot.digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 Robot.digitalWrite(trigPin, LOW);
 pinMode(echoPin, INPUT);

 // Obtain and process data from echoPin
 long duration = pulseIn(echoPin, HIGH);
 long cm = duration / 58;

 // return distance to object in centimeters
 return cm;
}

// make a happy or sad face
void setFace(boolean onOff) {
  if (onOff) {
    // if true show a happy face
    Robot.background(0, 0, 255);
    Robot.setCursor(44, 60);
    Robot.stroke(0, 255, 0);
    Robot.setTextSize(4);
    Robot.print(":)");
  } else {
    // if false show an upset face
    Robot.background(255, 0, 0);
    Robot.setCursor(44, 60);
    Robot.stroke(0, 255, 0);
    Robot.setTextSize(4);
    Robot.print("X(");
  }
}
