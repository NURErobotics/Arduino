
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
//Servo myservo7;
//Servo myservo8;
//Servo myservo9;

//left
Servo myservo1;
Servo myservo2;
Servo myservo3;
//Servo myservo10;
//Servo myservo11;
//Servo myservo12;
int a;
float v = 1;
int ang[] = {120, 90, 60, 30, 60, 90};
int zn[] = { -1, -1, -1, +1, +1, +1};

void setup()
{
/*
  myservo7.attach(8);
  myservo9.attach(10);
  myservo11.attach(12);
  delay(300);
  myservo8.attach(9);
  myservo10.attach(11);
  myservo12.attach(13);
  delay(300);*/
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

void cancan()
{
  for (a = 0; a < 90; a += 3)
  {
    myservo1.write(120 - a);
    myservo3.write(120 - a);
    myservo5.write(120 - a);
    delay(50);
  }
  for (a = 90; a > 0; a -= 3)
  {
    myservo1.write(120 - a);
    myservo3.write(120 - a);
    myservo5.write(120 - a);
    delay(50);
  }


  for (a = 0; a < 90; a += 3)
  {
    myservo2.write(120 - a);
    myservo4.write(120 - a);
    myservo6.write(120 - a);
    delay(50);
  }
  for (a = 90; a > 0; a -= 3)
  {
    myservo2.write(120 - a);
    myservo4.write(120 - a);
    myservo6.write(120 - a);
    delay(50);
  }

}

void gopak()
{
  for (a = 0; a < 90; a += 3)
  {
    myservo1.write(120 - a);
    myservo3.write(120 - a);
    myservo5.write(120 - a);
    myservo2.write(120 - a);
    myservo4.write(120 - a);
    myservo6.write(120 - a);
    delay(50);
  }
  for (a = 90; a > 0; a -= 3)
  {
    myservo1.write(120 - a);
    myservo3.write(120 - a);
    myservo5.write(120 - a);
    myservo2.write(120 - a);
    myservo4.write(120 - a);
    myservo6.write(120 - a);
    delay(50);
  }
}
void lombada()
{

  int p1 = zn[0];
  int p2 = ang[0];

  for (int i = 0; i < 5; i++)
  {
    zn[i] = zn[i + 1];
    ang[i] = ang[i + 1];
  }
  zn[5] = p1;
  ang[5] = p2;

  for (a = 0; a < 30; a += 3)
  {
    myservo1.write(ang[0] + zn[0]*a);
    myservo2.write(ang[1] + zn[1]*a);
    myservo3.write(ang[2] + zn[2]*a);
    myservo6.write(ang[3] + zn[3]*a);
    myservo5.write(ang[4] + zn[4]*a);
    myservo4.write(ang[5] + zn[5]*a);
    
    delay(50);
  }

}

void stopp()
{
    myservo1.write(90);
    myservo2.write(90);
    myservo3.write(90);
    myservo6.write(90);
    myservo5.write(90);
    myservo4.write(90);
delay(100);
 
}
void loop()
{

  for (a = 0; a < 90; a += 3)
  {
    myservo2.write(120 - a);
    myservo3.write(120 - a);
    myservo5.write(120 - a);
    delay(50);
  }
  for (a = 90; a > 0; a -= 3)
  {
    myservo2.write(120 - a);
    myservo3.write(120 - a);
    myservo5.write(120 - a);
    delay(50);
  }

  
for(int l=0; l<13; l++)
  {
   lombada(); 
  }
  delay(500);
//stopp();
cancan();
cancan();
gopak();  
gopak();



}



