
#include <Servo.h>

/*
 ** heksapod **

 3_12_______7_6
 2_11_______8_5
 1_10_______9_4



4_13___ 8_7
3_12___ 9_6
2_11___10_5
 */
//right
Servo myservo4 ;
Servo myservo5;
Servo myservo6;
Servo myservo7;
Servo myservo8;
Servo myservo9;

//left
Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo10;
Servo myservo11;
Servo myservo12;
int a;
float v = 1;
int ang[] = {120, 90, 60, 30, 60, 90};
int zn[] = { -1, -1, -1, +1, +1, +1};

void setup()
{

  myservo7.attach(8);
  myservo9.attach(10);
  myservo11.attach(12);
  delay(300);
  myservo8.attach(9);
  myservo10.attach(11);
  myservo12.attach(13);
  delay(300);
  myservo2.attach(3);
  myservo4.attach(5);
  myservo6.attach(7);
  delay(300);
  myservo1.attach(2);
  myservo3.attach(4);
  myservo5.attach(6);
  delay(300);
  myservo2.write(120);
  myservo4.write(120);
  myservo6.write(120);
  myservo1.write(120);
  myservo3.write(120);
  myservo5.write(120);
 /* myservo7.write(90);
  myservo8.write(90);
  myservo9.write(90);
  myservo10.write(90);
  myservo11.write(90);
  myservo12.write(90);
  delay(1000);*/

}

 
void loop()
{
    myservo1.write(120);
    
    myservo3.write(120);
    
    myservo5.write(120);
    
    delay(500);
    myservo7.write(100);
    myservo9.write(100);
    myservo11.write(100);
    delay(500);
    myservo1.write(30);
    myservo3.write(30);
    myservo5.write(30);
    
    delay(500);
    myservo7.write(60);
    
    myservo9.write(60);
   
    myservo11.write(60);
    
    delay(500);

    
    myservo2.write(120);
    myservo4.write(120);
    myservo6.write(120);
    delay(500);
    
    myservo8.write(100);
    myservo10.write(100);
    myservo12.write(100);
    delay(500);
    myservo2.write(30);
    myservo4.write(30);
    myservo6.write(30);
    
    delay(500);
    myservo8.write(60);
    myservo10.write(60);
    myservo12.write(60);

}



