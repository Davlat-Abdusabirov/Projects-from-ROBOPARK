/*
  Дополнил код, добавил Servo helmet, neck
  *
  Completed the code, added Servo helmet, neck.
  by Abdusabirov Davlat <https://github.com/Davlat-Abdusabirov>
*/

#include <Servo.h>

//***Pins***//
#define PIN_SERVO_HELMET 8
#define PIN_SERVO_NECK 9
#define PIN_LED_EYE_RIGHT 13
#define PIN_LED_EYE_LEFT 12
#define PIN_BUTT1 7
#define PIN_BUTT2 6

//***Turn_of_Servo***//
#define HELMET_OPEN 60
#define HELMET_CLOSE 0

//***Object***//
Servo helmet;
Servo neck; 

//***Vars***//
bool is_left_eye_on = true;
bool is_right_eye_on = true;

bool is_helmet_open = true;
bool is_neck_open = true;

bool is_butt_press = false;
bool is_butt_press2 = false;

void setup()
{
  Serial.begin(9600);

  pinMode(PIN_LED_EYE_RIGHT, OUTPUT);
  pinMode(PIN_LED_EYE_LEFT, OUTPUT);
  pinMode(PIN_BUTT1, INPUT);

  neck.attach(PIN_SERVO_NECK);
  helmet.attach(PIN_SERVO_HELMET);
}

void loop() 
{
  // Включить led в статус is_on
  digitalWrite(PIN_LED_EYE_LEFT, is_left_eye_on);
  digitalWrite(PIN_LED_EYE_RIGHT, is_right_eye_on);

  // Проверка кнопки на нажатие 
  is_butt_press = digitalRead(PIN_BUTT1);
  is_helmet_open = is_butt_press;
  is_butt_press2 = digitalRead(PIN_BUTT2);
  is_neck_open = is_butt_press2;

  // Повернуть servo на градус HELMET_OPEN || HELMET_CLOSE 
  helmet.write(is_helmet_open ? HELMET_OPEN : HELMET_CLOSE);
  neck.write(is_neck_open ? HELMET_OPEN : HELMET_CLOSE);

  Serial.print("Button 1: "); Serial.print(is_butt_press); 
  Serial.print(" Button 2: "); Serial.println(is_butt_press2);
}
