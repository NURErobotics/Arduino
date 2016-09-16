/*
10 - Enable A - ШИМ управление двигателем А
 11 - Enable B - ШИМ управление двигателем В
 12 - Input 1 - Направление двигателя А
 13 - Input 3 - Направление двигателя В
 
 A8 - RIGHT SHARP SENSOR
 A9 - LEFT SHARP SENSOR
 
 Источник https://arduino-ua.com/prod1183-motoshild-ysilennii-ASC204
 IMPORTANT! 29ms should be the shortest delay between pings.
 */
 //#include <NewPing.h>
///////////////////////////PIN DEFINITION//////////////////////////////////////////
#define SPEED 130

#define left_sharp 9
#define right_sharp 8

#define FRONT_SENSOR_TRIG 22
#define FRONT_SENSOR_ECHO 23

#define LEFT_SENSOR_TRIG 24
#define LEFT_SENSOR_ECHO 25

#define RIGHT_SENSOR_TRIG 26
#define RIGHT_SENSOR_ECHO 27

#define PWM_CONTROL_MOTOR_A 10
#define ROTATION_MOTOR_A 12

#define PWM_CONTROL_MOTOR_B 11
#define ROTATION_MOTOR_B 13
///////////////////////////END OF PIN DEFINITION///////////////////////////////////

///////////////////////////SOME CONSTANT VALUES////////////////////////////////////
#define TIME_BETWEEN_MEASUREMENTS 30 //IN uS
#define MAX_PING_DISTANCE 400 //IN CM, NO MORE THAN 500 BY DEFAULT
#define ITERACTION_FOR_ACCURATE_DIST_RESULT 2
///////////////////////////END OF SOME CONSTANT VALUES/////////////////////////////

///////////////////////////SOME OBJECTS AND FUNTIONS DECLARATION///////////////////
//NewPing sonar_front(FRONT_SENSOR_TRIG, FRONT_SENSOR_ECHO, MAX_PING_DISTANCE); // NewPing setup of pins and maximum distance.
//NewPing sonar_left(LEFT_SENSOR_TRIG, LEFT_SENSOR_ECHO, MAX_PING_DISTANCE);
//NewPing sonar_right(RIGHT_SENSOR_TRIG, RIGHT_SENSOR_ECHO, MAX_PING_DISTANCE);
///////////////////////////END OF SOME OBJECTS AND FUNTIONS DECLARATION///////////

//////////////////////////GLOBAL VARIABLES////////////////////////////////////////
int i;
unsigned long int now_time = 0, now_time_for_driving = 0;
unsigned int uS = 0;
unsigned int dist_front_sensor = 0;
unsigned int dist_left_sensor = 0;
unsigned int dist_right_sensor = 0;
int smaller_dist = 0;
int right = 0;
int left = 0;
int right_now = 0, left_now = 0;
float volts = 0, dist = 0;
//////////////////////////END OF GLOBAL VARIABLES/////////////////////////////////

float get_sharp_dist(int pin)
{
  volts = analogRead(pin)*0.0048828125; // считываем значение сенсора и переводим в напряжение
  dist = 27.579*pow(volts, -1.212);

  return dist;
}

/*unsigned int get_front_sensor_data()
{
  uS = sonar_front.ping_median(ITERACTION_FOR_ACCURATE_DIST_RESULT);
  dist_front_sensor = sonar_front.convert_cm(uS);

  uS = 0;
  return dist_front_sensor;
}

unsigned int get_left_sensor_data()
{
  uS = sonar_left.ping_median(ITERACTION_FOR_ACCURATE_DIST_RESULT);
  dist_left_sensor = sonar_left.convert_cm(uS);

  uS = 0;
  return dist_left_sensor;
}

unsigned int get_right_sensor_data()
{
  uS = sonar_right.ping_median(ITERACTION_FOR_ACCURATE_DIST_RESULT);
  dist_right_sensor = sonar_right.convert_cm(uS);

  uS = 0;
  return dist_right_sensor;
}
*/
void motion(char major_motor_rotation[8], int major_motor_speed, char m_direction[5]) //FORWARD/BACKWARD/STOP, 0-255, LEFT/RIGHT/NO
{
  //TURN MOTOR CONTROL
  if (m_direction == "LEFT")
  {
    digitalWrite(ROTATION_MOTOR_B, HIGH);
    analogWrite(PWM_CONTROL_MOTOR_B, 180);
  }
  else if (m_direction == "RIGHT")
  {
    digitalWrite(ROTATION_MOTOR_B, LOW);
    analogWrite(PWM_CONTROL_MOTOR_B, 180);
  }
  else if (m_direction == "NO")
  {
    digitalWrite(ROTATION_MOTOR_B, LOW);
    analogWrite(PWM_CONTROL_MOTOR_B, 0);
  }

  //MAJOR MOTOR CONTROL
  if (major_motor_rotation == "FORWARD")
  {
    digitalWrite(ROTATION_MOTOR_A, HIGH);
    analogWrite(PWM_CONTROL_MOTOR_A, major_motor_speed);
    //analogWrite(PWM_CONTROL_MOTOR_A, major_motor_speed);
    /*now_time_for_driving = millis();
     for (i = 40; i < major_motor_speed; i += 10)
     {
     if (millis() - now_time_for_driving < 10)
     {
     analogWrite(PWM_CONTROL_MOTOR_A, i);
     now_time_for_driving = millis();
     }
     }*/
  }
  else if (major_motor_rotation == "BACKWARD")
  {
    digitalWrite(ROTATION_MOTOR_A, LOW);
    analogWrite(PWM_CONTROL_MOTOR_A, major_motor_speed);
    //now_time_for_driving = millis();
    /*for (i = 40; i < major_motor_speed; i += 10)
     {
     if (millis() - now_time_for_driving < 10)
     {
     analogWrite(PWM_CONTROL_MOTOR_A, i);
     now_time_for_driving = millis();
     }
     }*/
  }
  else if (major_motor_rotation == "STOP")
  {
    digitalWrite(ROTATION_MOTOR_A, LOW);
    analogWrite(PWM_CONTROL_MOTOR_A, 0);
  }
}

void setup()
{
  //pinMode(52, OUTPUT);
  pinMode(53, INPUT);

  pinMode(36, INPUT);
  pinMode(40, INPUT);
  //++
  //pinMode(42, OUTPUT);
  //pinMode(39, OUTPUT);
  //--
  //pinMode(41, OUTPUT);
  //pinMode(38, OUTPUT);


  /* pinMode(FRONT_SENSOR_TRIG, OUTPUT);
   pinMode(RIGHT_SENSOR_TRIG, OUTPUT);
   pinMode(LEFT_SENSOR_TRIG, OUTPUT);
   
   pinMode(FRONT_SENSOR_ECHO, INPUT);
   pinMode(RIGHT_SENSOR_ECHO, INPUT);
   pinMode(LEFT_SENSOR_ECHO, INPUT);*/

  pinMode(ROTATION_MOTOR_A, OUTPUT);
  pinMode(ROTATION_MOTOR_B, OUTPUT);
  pinMode(PWM_CONTROL_MOTOR_A, OUTPUT);
  pinMode(PWM_CONTROL_MOTOR_B, OUTPUT);

  /////////////////////////UNDER LOOP OPERATIONS////////////////////
  //right = get_right_sensor_data();
  //left = get_left_sensor_data();

  right = get_sharp_dist(right_sharp);
  left = get_sharp_dist(left_sharp);
}



void loop()
{

  //right_now = get_right_sensor_data();
  //left_now = get_left_sensor_data();
  /*
  if (get_left_sensor_data() < get_right_sensor_data() && digitalRead(53) == LOW) //get_front_sensor_data() <= 10()() || digitalRead(53) == HIGH && get_left_sensor_data() < get_right_sensor_data()
   {
   motion("BACKWARD", SPEED, "RIGHT"); //right
   }
   
   if (get_left_sensor_data() > get_right_sensor_data() && digitalRead(53) == LOW) //|| (digitalRead(53) == LOW && digitalRead(36) == LOW)
   {
   motion("BACKWARD", SPEED, "LEFT"); //LEFT
   }
   
   if(digitalRead(53) == LOW && digitalRead(40) == LOW) //forward and right
   {
   motion("BACKWARD", SPEED, "RIGHT");
   }
   
   if(digitalRead(53) == LOW && digitalRead(36) == LOW) //forward and left
   {
   motion("BACKWARD", SPEED, "LEFT");
   } 
   
   if (get_front_sensor_data() > 20)
   {
   if (millis() - now_time > 250)
   {
   now_time = millis();
   right = get_right_sensor_data();
   left = get_left_sensor_data();
   }
   
   motion("FORWARD", SPEED, "NO");
   
   if (get_front_sensor_data() < 40)
   {
   motion("FORWARD", 80, "NO");
   }
   
   if (get_front_sensor_data() >= 40 && get_front_sensor_data() <= 42)
   {
   motion("FORWARD", 0, "NO");
   }
   
   if (right - get_right_sensor_data() > 2 && right - get_right_sensor_data() < 20 || digitalRead(40) == LOW)
   {
   motion("FORWARD", SPEED, "LEFT");
   }
   
   if (left - get_left_sensor_data() > 2 && left - get_left_sensor_data() < 20 || digitalRead(36) == LOW)
   {
   motion("FORWARD", SPEED, "RIGHT");
   }
   */
  /* if (left - get_left_sensor_data() > 3 && left - get_left_sensor_data() < 10 && digitalRead(36) == LOW && digitalRead(40) == LOW)
   {
   motion("BACKWARD", 70, "RIGHT");
   }
   
   if (right - get_right_sensor_data() > 3 && right - get_right_sensor_data() < 10 && digitalRead(36) == LOW && digitalRead(40) == LOW)
   {
   motion("BACKWARD", 70, "LEFT");
   }
   }*/
  /*
  if (millis() - now_time > 250)
   {
   now_time = millis();
   right = get_sharp_dist(right_sharp);
   left = get_sharp_dist(left_sharp);
   }
   */
   
  if(abs(get_sharp_dist(left_sharp) - get_sharp_dist(right_sharp)) < 5)
  {
    
    motion("FORWARD", SPEED, "NO");
  }

  if (abs(get_sharp_dist(left_sharp) - get_sharp_dist(right_sharp)) >= 7 && get_sharp_dist(right_sharp) > get_sharp_dist(left_sharp))
  {
    motion("FORWARD", SPEED - 30, "LEFT");
  }

  if (abs(get_sharp_dist(left_sharp) - get_sharp_dist(right_sharp)) >= 7 && get_sharp_dist(right_sharp) < get_sharp_dist(left_sharp))
  {
    motion("FORWARD", SPEED - 30, "RIGHT");
  }

  if(digitalRead(53) == HIGH)
  {
    //motion("STOP", 0, "NO");
    //motion("BACKWARD", SPEED, "NO");
    now_time = millis();
   while (millis() - now_time < 700)
   {
   
   motion("BACKWARD", SPEED, "LEFT");
   }
   now_time = millis();
   while (millis() - now_time < 300)
   {
   
   motion("BACKWARD", SPEED, "RIGHT");
   }
   now_time = millis();
  }

    if (digitalRead(53) == LOW && get_sharp_dist(right_sharp) > 35 &&  get_sharp_dist(left_sharp) < 30)
  {
    motion("FORWARD", SPEED , "RIGHT");
  }

   if (digitalRead(53) == LOW && get_sharp_dist(right_sharp) < 30 &&  get_sharp_dist(left_sharp) > 35)
  {
    motion("FORWARD", SPEED , "LEFT");
  }


 if(get_sharp_dist(left_sharp) < 10 || get_sharp_dist(right_sharp) < 10) 
    {
      now_time = millis();
      while (millis() - now_time < 500)
   {
   
   motion("BACKWARD", SPEED - 20, "LEFT");
   }
      now_time = millis();
   while (millis() - now_time < 500)
   {
   
   motion("BACKWARD", SPEED - 20, "NO");
   }
   now_time = millis();
  }
    
  

/*
  if(digitalRead(53) == LOW)
  {
    motion("BACKWARD", SPEED, "NO");
  }
  */
}

