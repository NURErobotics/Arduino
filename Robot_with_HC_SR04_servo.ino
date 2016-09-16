
#include "Arduino.h"
#include <SPI.h>
//#include <MFRC522.h>
#include <NewPing.h>
#include <Servo.h>
#include <TimerFreeTone.h>
#include <LiquidCrystalRus.h>

/*
   Программа для управления роботом на HC-SR04 (установлен на сервопривод)
*/

//карта для идентификации
//byte White_Card[] = {0xBC, 0xC2, 0xAE, 0x07};
//идентификация RFID-ридера
#define SS_PIN 53
#define RST_PIN 5
//MFRC522 mfrc522(SS_PIN, RST_PIN);	// Create MFRC522 init.

/*
//для дисплея
byte cube[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
};
*/
//пин пьезо
#define Music_Pin 47
//пин мигалки
#define Yellow_led_pin 46
//инициализация ножек для дисплея
//LiquidCrystalRus lcd(30, 31, 22, 24, 26, 28); //RS, E, D4, D5, D6, D7
//Пин управления сервоприводом
#define servo_pin 8
//Порты, к которым подключен сонар
#define Echo 49
#define Trig 48
//Порты управлением драйвера двигателей (2 задают направление, 1 - ШИМ)
//Канал 1
#define M1_B 23
#define M1_A 25
#define M1_PWM 7
//Канал 2
#define M2_B 27
#define M2_A 29
#define M2_PWM 6

int distance[9]; 
//Ultrasonic ultrasonic(Trig, Echo); //Дальномер
NewPing sonar(Trig, Echo);
/*unsigned long now_time;
long pre_time1 = 0;
long pre_time2 = 0;
long pre_time3 = 0;
long pre_time4 = 0;
char mass[3];*/

//int k = 0;
unsigned long lastUpdate; //последнее обновление положения
///////////////////////////////////////////////КЛАССЫ///////////////////////////////////////////////////////////////////////////////////////////////

class Flasher
{
  //Переменные - члены класса
  int ledPin; //номер пина светодиода
  long OnTime; //время включения
  long OffTime; //время выключения
  
  // текущее состояние
  int ledState;
  unsigned long previousMillis;
  
  public:
  Flasher(int pin, long on, long off)
  {
    ledPin = pin;
    pinMode(ledPin, OUTPUT);
    
    OnTime = on;
    OffTime = off;
    
    ledState = LOW;
    previousMillis = 0;
  }
  
  void Update()
  {
    unsigned long currentMillis = millis();
    
    if((ledState == HIGH) && (currentMillis - previousMillis >= OnTime))
    {
      ledState = LOW;
      previousMillis = currentMillis;
      digitalWrite(ledPin, ledState);
    }
    else if((ledState == LOW) && (currentMillis - previousMillis >= OffTime))
    {
      ledState = HIGH;
      previousMillis = currentMillis;
      digitalWrite(ledPin, ledState);
    }
  }
  
};

class Sweeper
{
  Servo myservo; //Создание объекта myservo
  int pos; //позиция сервопривода
  int i; //счетчик массива
  //unsigned long activateTime; //для записи настоящего времени
  int increment; //на сколько переместится серво с каждой итерацией цикла
  int updateInterval; //время между обновлениями
  //unsigned long lastUpdate; //последнее обновление положения
  unsigned long time_for_go;
  
  public:
  Sweeper(int interval, int S)
  {
    updateInterval = interval;
    increment = S;
  }
  
  void Attach(int pin)
  {
    myservo.attach(pin);
    myservo.write(0);
  }
  
  void Detach()
  {
    myservo.detach();
  }
  
  void Update()
  {
    if((millis() - lastUpdate) > updateInterval)  //it is time to update!
    {
      lastUpdate = millis();
      if(i < 9)
      {
        distance[i] = sonar.ping_cm();
        /*lcd.clear();
        lcd.setCursor(0, 0); //столбец, строка
        lcd.print("Расстояние:");
        lcd.setCursor(11, 0); //столбец, строка
        lcd.print(distance[i]);*/
        //lcd.clear();
      }
      
      if (distance[i] <= 20)
      {
        time_for_go = millis();
        
        switch(myservo.read()) {
         case 0: {Stop();
                  TimerFreeTone(Music_Pin, 1300, 300); 
                  while (sonar.ping_cm() < 20 && (millis() - time_for_go) < 3000){ //цикл выполняется пока не достигнет цели либо не истечет время
                       /*lcd.setCursor(1, 1); 
                       lcd.print("Едем влево..."); */
                       go_left(80); 
                  } 
                  //lcd.clear(); 
                  break;};//500 --- Stop(); go_left(60, updateInterval);
         case 45: {Stop(); 
                   TimerFreeTone(Music_Pin, 1300, 300); 
                   while (sonar.ping_cm() < 20 && (millis() - time_for_go) < 3000){
                        /*lcd.setCursor(1, 1); 
                        lcd.print("Едем влево...");*/
                        go_left(70); 
                   } 
                   //lcd.clear(); 
                   break;};//1000
         case 90: {Stop();
                   TimerFreeTone(Music_Pin, 1300, 300); 
                   while (sonar.ping_cm() < 35 && (millis() - time_for_go) < 3000){
                        /*lcd.setCursor(1, 1);
                        lcd.print("Едем назад..."); */
                        go_back(70); 
                   } 
                   //lcd.clear();
                   break;};//1000
         case 135: {Stop(); 
                    TimerFreeTone(Music_Pin, 1300, 300); 
                    while (sonar.ping_cm() < 20 && (millis() - time_for_go) < 3000){
                         /*lcd.setCursor(1, 1); 
                         lcd.print("Едем вправо..."); */
                         go_right(70); 
                    } 
                    //lcd.clear(); 
                    break;};//500
         case 180: {Stop(); 
                    TimerFreeTone(Music_Pin, 1300, 300); 
                    while (sonar.ping_cm() < 20 && (millis() - time_for_go) < 3000){
                        /* lcd.setCursor(1, 1); 
                         lcd.print("Едем вправо..."); */
                         go_right(80); 
                    } 
                    //lcd.clear(); 
                    break;};//1000
         //case 5: {Stop(); while (sonar.ping_cm() < 30){lcd.setCursor(1, 1); lcd.print("Едем вправо..."); go_right(60); } lcd.clear(); break;};//500
         //case 6: {Stop(); while (sonar.ping_cm() < 30){lcd.setCursor(1, 1); lcd.print("Едем назад..."); go_back(70); } lcd.clear(); break;};//1000
         //case 7: {Stop(); while (sonar.ping_cm() < 30){lcd.setCursor(1, 1); lcd.print("Едем влево..."); go_left(60); } lcd.clear(); break;};//1000
         //case 8: {Stop(); while (sonar.ping_cm() < 30){lcd.setCursor(1, 1); lcd.print("Едем влево..."); go_left(70); } lcd.clear(); break;};//500 
         }
        
      }
      
      i += 1;
      pos += increment;
      myservo.write(pos);
      if((pos >= 180) || (pos <= 0)) //вращать некуда - меняем направление
      {
        increment = -increment; // change rotation
      }
      if(i == 11)
      {
       i = 0; 
      }
    }
  }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Объявление переменных
int distance_sm = 0; //расстояние в см

//int dist_0, dist_180;

//Инициализация

//Servo myservo; //Создание объекта myservo

//настройка мигающих светодиодов
Flasher led1(Yellow_led_pin, 100, 100); // <name>(<pin>, <on time>, <off time>)
Flasher led2(13, 1000, 1000);

//настройка сервопривода
Sweeper sweeper1(300, 45); // <name>(<interval>, <rotation degrees>)

/*int RC522_control()
{   
   byte buffer[15];
   int flag = 0; //0 - нет карт, 1 - не наша карта, 2 - наша карта
   if (mfrc522.PICC_IsNewCardPresent())
   {
    if (mfrc522.PICC_ReadCardSerial())
    {
      flag = 1;
       
      
      for (byte i = 0; i < mfrc522.uid.size; i++) {
          buffer[i] = mfrc522.uid.uidByte[i];
      }
      
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Карта распознана");
      
      for(int j = 0; j < mfrc522.uid.size; j++) 
      {
      if (White_Card[j] == buffer[j])
          {
            flag = 2;
          }
      else 
          {
            flag = 1;
          }    
      }

      if (flag == 2)
      {
        TimerFreeTone(Music_Pin, 1000, 100);
        TimerFreeTone(Music_Pin, 1400, 100);
        lcd.setCursor(1, 2);
        lcd.print("Доступ");
        lcd.setCursor(0, 3);
        lcd.print("разрешен");
        delay(1000);
      }
      else if (flag == 1)
      {
        TimerFreeTone(Music_Pin, 600, 100);
        delay(50);
        TimerFreeTone(Music_Pin, 600, 100);
        lcd.setCursor(1, 2);
        lcd.print("Доступ");
        lcd.setCursor(0, 3);
        lcd.print("запрещен");
      }
      
 return flag;
    }
   }
}*/
/*
void hello() //функция приветствия
{
  int hello_counter;
  lcd.createChar(0, cube);
  
  for (hello_counter = -4; hello_counter < 12; hello_counter++)
  {
    //lcd.clear(); 
    lcd.setCursor(2, 0); //столбец, строка
    lcd.print("Здравствуйте!");
    lcd.setCursor(5, 1); 
    lcd.print("Hello!");
    
    lcd.setCursor(hello_counter, 3); //для двух последних строк указывать -4 вместо 0 (для столбца)!
    lcd.write(byte(0));
    delay(100);
  }
  
  TimerFreeTone(Music_Pin, 1175, 300);
        lcd.clear();
        lcd.setCursor(3, 1);
        lcd.print("Пожалуйста,"); 
        lcd.setCursor(-2, 2);
        lcd.print("авторизуйтесь");
}*/

void setup()
{
  /* Инициализация */
  
  //дисплей
  //lcd.begin(16, 4);
  //SPI and rc-522 initialization
 // SPI.begin();			// Init SPI bus
  //mfrc522.PCD_Init();	// Init MFRC522 card
  sweeper1.Attach(servo_pin); //Указание выхода управления сервопривода
  
  /* Конфигурация портов ввода-вывода */
  
  //Для сонара
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  //Наплатный светодиод
 // pinMode(LED, OUTPUT);
  //Драйвер двигателей
  pinMode(M1_A, OUTPUT);
  pinMode(M1_B, OUTPUT);
  pinMode(M2_A, OUTPUT);
  pinMode(M2_B, OUTPUT);
  pinMode(M1_PWM, OUTPUT);
  pinMode(M2_PWM, OUTPUT);
  
  //hello();
  
  /*do {
    RC522_control();
  }
  while (RC522_control() != 2);*/
  /* Операции, выполняемые вне цикла */
  
}//setup



/* Функции управления */

//Движение вперед с определенной скоростью
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

void loop()
{
  /*if (RC522_control() == 2)
  {
    //остановка
    Stop();
    //звук
    delay(150);
    TimerFreeTone(Music_Pin, 1180, 300);
    TimerFreeTone(Music_Pin, 1210, 300);
    TimerFreeTone(Music_Pin, 2000, 300);
    //отключение светодиодов
    digitalWrite(Yellow_led_pin, LOW);
    digitalWrite(13, LOW);
    //выведение оповещения
    lcd.clear();
    lcd.setCursor(3, 1);
    lcd.print("Завершение");
    lcd.setCursor(1, 2);
    lcd.print("работы");
    
    delay(3000);
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Для продолжения");
    lcd.setCursor(0, 1);
    lcd.print("приложите карту");
    lcd.setCursor(-4, 2);
    lcd.print("к считывателю");
    
    do {
      RC522_control();
    }
    while (RC522_control() != 2);
  }*/
  
  led1.Update(); //запуск функции Update класса Flasher
  led2.Update();
  go_forward(60);
  sweeper1.Update(); 
}//loop



