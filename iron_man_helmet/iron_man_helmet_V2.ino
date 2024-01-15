/*
  Дополнил код, добавил функцию printDataOfBot, изменил работу Servo neck
  *
  Completed the code, added printDataOfBot function, changed the work of Servo neck
  by Abdusabirov Davlat <https://github.com/Davlat-Abdusabirov>
*/

#include <Servo.h>

//***Pins***//
#define PIN_LED_EYE_RIGHT 13
#define PIN_LED_EYE_LEFT 12
#define PIN_SERVO_HELMET 8
#define PIN_SERVO_NECK 9
#define PIN_BUTT1 7
//#define PIN_BUTT2 6
#define PIN_POTENTIOMETR A0

//***Turn_of_Servo***//
#define HELMET_OPEN 60
#define HELMET_CLOSE 0

//***Mode_For_Function_PrintDataOfBot***//
enum ModeForPrint
{
  OF_BUTTHON, 
  OF_SERVO_TURN, 
  OF_POTENTIOMETR,
  OF_INPUT
};

//***Objects***//
Servo helmet;
Servo neck;

//***Vars***//
bool is_left_eye_on = true;
bool is_right_eye_on = true;

bool is_helmet_open = true;
bool is_neck_open = true;

bool is_butt_press = false;
//bool is_butt_press2 = false;

//***Functions***//
void printDataOfBot(ModeForPrint mode);

void setup()
{
  Serial.begin(9600);

  pinMode(PIN_LED_EYE_RIGHT, OUTPUT);
  pinMode(PIN_LED_EYE_LEFT, OUTPUT);
  pinMode(PIN_BUTT1, INPUT);
  //pinMode(PIN_BUTT2, INPUT);

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
  //is_butt_press2 = digitalRead(PIN_BUTT2);
  //is_neck_open = is_butt_press2;

  // Читка данных с потенциометра и иницализация градуса поворота Servo neck
  uint8_t neck_turn = map(analogRead(PIN_POTENTIOMETR), 0, 1023, 0, 180); 

  // Повернуть servo на градус HELMET_OPEN || HELMET_CLOSE && neck_turn
  helmet.write(is_helmet_open ? HELMET_OPEN : HELMET_CLOSE);
  neck.write(neck_turn);
}


void printDataOfBot(ModeForPrint mode)
{
  switch (mode)
  {
    case OF_BUTTHON:
      Serial.print("Button 1:/t"); Serial.print(is_butt_press); 
      //Serial.print(" Button 2:/t"); Serial.println(is_butt_press2);
      break;
    case OF_SERVO_TURN:
      Serial.print("Servo Helmet:/t"); Serial.print(helmet.read());
      Serial.print("Servo Neck:/t"); Serial.println(neck.read());
      break;
    case OF_POTENTIOMETR:
      Serial.print("Potentiometr:/t"); Serial.println(analogRead(PIN_POTENTIOMETR));
      break;
    case OF_INPUT:
      Serial.print("Potentiometr:/t"); Serial.println(analogRead(PIN_POTENTIOMETR));
      Serial.print("Button 1:/t"); Serial.println(is_butt_press); 
      //Serial.print(" Button 2:/t"); Serial.println(is_butt_press2);
      break;
    default:
      Serial.println("ERROR: Wrong printMode;");
  }
}