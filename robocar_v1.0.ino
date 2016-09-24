/*
 5 - Enable A - PWM control motor А
 3 - Enable B - PWM control motor В
 4 and 6 - Input 1 - Rotation motor А
 2 and 7 - Input 3 - Rotation motor В
 
 A2 - RIGHT SHARP SENSOR
 A1 - LEFT SHARP SENSOR
 */

///////////////////////////PIN DEFINITION//////////////////////////////////////////
#define SPEED 110

#define left_sharp A1
#define right_sharp A2

#define PWM_CONTROL_MOTOR_A 5
#define ROTATION_MOTOR_A_1 4
#define ROTATION_MOTOR_A_2 6

#define PWM_CONTROL_MOTOR_B 3
#define ROTATION_MOTOR_B_1 2
#define ROTATION_MOTOR_B_2 7
///////////////////////////END OF PIN DEFINITION///////////////////////////////////

///////////////////////////SOME CONSTANT VALUES////////////////////////////////////
#define COEFFICIENT 27.579
#define DEGREE -1.212
#define ANALOG_TO_VOLTS 0.0048828125
///////////////////////////END OF SOME CONSTANT VALUES/////////////////////////////

//////////////////////////GLOBAL VARIABLES////////////////////////////////////////
int right = 0;
int left = 0;
float volts = 0, dist = 0;
//////////////////////////END OF GLOBAL VARIABLES/////////////////////////////////

float get_sharp_dist(int pin)
{
  //CONVERTING THE INPUT VALUE INTO A VOLTAGE VALUE
  volts = analogRead(pin) * ANALOG_TO_VOLTS; 
  //CONVERTING THE VOLTS INTO A DISTANCE IN CM
  dist = COEFFICIENT * pow(volts, DEGREE);

  return dist;
}


void motion(char major_motor_rotation[8], int major_motor_speed, char m_direction[5]) //FORWARD/BACKWARD/STOP, 0-255, LEFT/RIGHT/NO
{
  //TURN MOTOR CONTROL
  if (m_direction == "LEFT")
  {
    digitalWrite(ROTATION_MOTOR_A_1, HIGH);
    digitalWrite(ROTATION_MOTOR_A_2, LOW);
    analogWrite(PWM_CONTROL_MOTOR_A, 140);
  }
  else if (m_direction == "RIGHT")
  {
    digitalWrite(ROTATION_MOTOR_A_1, LOW);
    digitalWrite(ROTATION_MOTOR_A_2, HIGH);
    analogWrite(PWM_CONTROL_MOTOR_A, 140);
  }
  else if (m_direction == "NO")
  {
    digitalWrite(ROTATION_MOTOR_A_1, LOW);
    digitalWrite(ROTATION_MOTOR_B_2, LOW);
    analogWrite(PWM_CONTROL_MOTOR_A, 0);
  }

  //MAJOR MOTOR CONTROL
  if (major_motor_rotation == "FORWARD")
  {
    digitalWrite(ROTATION_MOTOR_B_1, HIGH);
    digitalWrite(ROTATION_MOTOR_B_2, LOW);
    analogWrite(PWM_CONTROL_MOTOR_B, major_motor_speed);
  }
  else if (major_motor_rotation == "BACKWARD")
  {
    digitalWrite(ROTATION_MOTOR_B_1, LOW);
    digitalWrite(ROTATION_MOTOR_B_2, HIGH);
    analogWrite(PWM_CONTROL_MOTOR_B, major_motor_speed);
  }
  else if (major_motor_rotation == "STOP")
  {
    digitalWrite(ROTATION_MOTOR_B_1, LOW);
    digitalWrite(ROTATION_MOTOR_B_2, LOW);
    analogWrite(PWM_CONTROL_MOTOR_B, 0);
  }
}

void setup()
{
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);

  pinMode(ROTATION_MOTOR_A_1, OUTPUT);
  pinMode(ROTATION_MOTOR_A_2, OUTPUT);
  pinMode(ROTATION_MOTOR_B_1, OUTPUT);
  pinMode(ROTATION_MOTOR_B_2, OUTPUT);
  pinMode(PWM_CONTROL_MOTOR_A, OUTPUT);
  pinMode(PWM_CONTROL_MOTOR_B, OUTPUT);

  /////////////////////////BEFORE LOOP OPERATIONS////////////////////
  
  right = get_sharp_dist(right_sharp);
  left = get_sharp_dist(left_sharp);
}



void loop()
{

  if(abs(get_sharp_dist(left_sharp) - get_sharp_dist(right_sharp)) < 5)
  {
    motion("FORWARD", SPEED, "NO");
  }

  if (abs(get_sharp_dist(left_sharp) - get_sharp_dist(right_sharp)) >= 5 && get_sharp_dist(right_sharp) > get_sharp_dist(left_sharp))
  {
    motion("FORWARD", SPEED, "LEFT");
  }

  if (abs(get_sharp_dist(left_sharp) - get_sharp_dist(right_sharp)) >= 5 && get_sharp_dist(right_sharp) < get_sharp_dist(left_sharp))
  {
    motion("FORWARD", SPEED, "RIGHT");
  }
}
