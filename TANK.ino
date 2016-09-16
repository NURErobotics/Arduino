//Порты управлением драйвера двигателей (2 задают направление, 1 - ШИМ)
//Канал 1
#define M1_B 23
#define M1_A 25
#define M1_PWM 7
//Канал 2
#define M2_B 27
#define M2_A 29
#define M2_PWM 6

void setup()
{
  pinMode(M1_A, OUTPUT);
  pinMode(M1_B, OUTPUT);
  pinMode(M2_A, OUTPUT);
  pinMode(M2_B, OUTPUT);
  pinMode(M1_PWM, OUTPUT);
  pinMode(M2_PWM, OUTPUT);

  void go_forward(int PWM1)  //... , int time1
{
    digitalWrite(M1_A, LOW);
    digitalWrite(M1_B, HIGH);
    digitalWrite(M2_A, HIGH);
    digitalWrite(M2_B, LOW);
    analogWrite(M1_PWM, PWM1); //сбавить, мотор - слева
    analogWrite(M2_PWM, PWM1+7);
}

//Движение назад с определенной скоростью
void go_back(int PWM2)//time2
{
    digitalWrite(M1_A, HIGH);
    digitalWrite(M1_B, LOW);
    digitalWrite(M2_A, LOW);
    digitalWrite(M2_B, HIGH);
    analogWrite(M1_PWM, PWM2);
    analogWrite(M2_PWM, PWM2+7);
}

//Остановка (Электронный тормоз)
void Stop()
{
  digitalWrite(M1_A, HIGH);
  digitalWrite(M1_B, HIGH);
  digitalWrite(M2_A, HIGH);
  digitalWrite(M2_B, HIGH);
  analogWrite(M1_PWM, 0);
  analogWrite(M2_PWM, 0);
  delay(100);
}

//Движение Влево с определенной скоростью
void go_right(int PWM3)//time3
{
    digitalWrite(M1_A, HIGH);
    digitalWrite(M1_B, LOW);
    digitalWrite(M2_A, HIGH);
    digitalWrite(M2_B, LOW);
    analogWrite(M1_PWM, PWM3);
    analogWrite(M2_PWM,PWM3+35); //подобрать скорость экспериментально!!!
}

//Движение Вправо с определенной скоростью
void go_left(int PWM4)//time4
{
    digitalWrite(M1_A, LOW);
    digitalWrite(M1_B, HIGH);
    digitalWrite(M2_A, LOW);
    digitalWrite(M2_B, HIGH);
    analogWrite(M1_PWM, PWM4);
    analogWrite(M2_PWM, PWM4 + 40); //подобрать скорость экспериментально!!!
}
}

void loop(){
}
}

