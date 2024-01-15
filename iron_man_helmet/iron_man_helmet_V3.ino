/*
  Дополнил код, добавил struct RGB_Led, дополнил printDataOfBot
  *
  Completed the code, added struct RGB_Led, added printDataOfBot
  by Abdusabirov Davlat <https://github.com/Davlat-Abdusabirov>
*/

#include <Servo.h>

//***Pins***//
#define PIN_RLED_RIGHT 13
#define PIN_GLED_RIGHT 12
#define PIN_BLED_RIGHT 11

#define PIN_RLED_LEFT 10
#define PIN_GLED_LEFT 9
#define PIN_BLED_LEFT 8

#define PIN_SERVO_HELMET 7
#define PIN_SERVO_NECK 6

#define PIN_BUTT1 5
//#define PIN_BUTT2 4
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
  OF_INPUT,
  OF_ALL_INFO
};

//***Struct_Class***//
class RGB_Led 
{
  uint8_t R_pin;
  uint8_t G_pin;
  uint8_t B_pin;

public:
  void connect(uint8_t R_pin, uint8_t G_pin, uint8_t B_pin)
  {
    this->R_pin = R_pin;
    this->G_pin = G_pin;
    this->B_pin = B_pin;

    pinMode(R_pin, OUTPUT);
    pinMode(G_pin, OUTPUT);
    pinMode(B_pin, OUTPUT);
  }

  void write(bool red, bool green, bool blue)
  {
    digitalWrite(R_pin, red);
    digitalWrite(G_pin, green);
    digitalWrite(B_pin, blue);
  }  
};

//***Objects***//
Servo helmet;
Servo neck;
RGB_Led left_eye, right_eye;

//***Vars***//
bool is_helmet_open = true;
bool is_neck_open = true;

bool is_butt_press = false;
//bool is_butt_press2 = false;

//***Functions***//
void printDataOfBot(ModeForPrint mode);

void setup()
{
  Serial.begin(9600);
  left_eye.connect(PIN_RLED_LEFT, PIN_GLED_LEFT, PIN_BLED_LEFT);
  right_eye.connect(PIN_RLED_RIGHT, PIN_GLED_RIGHT, PIN_BLED_RIGHT);

  pinMode(PIN_BUTT1, INPUT);
  //pinMode(PIN_BUTT2, INPUT);

  neck.attach(PIN_SERVO_NECK);
  helmet.attach(PIN_SERVO_HELMET);
}

void loop() 
{
  // Включить RGB_Led
  left_eye.write(true, true, true);
  right_eye.write(true, true, true);

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

  printDataOfBot(OF_ALL_INFO);
}


void printDataOfBot(ModeForPrint mode)
{
  switch (mode)
  {
    case OF_BUTTHON:
      Serial.print("Button 1:\t"); Serial.println(is_butt_press); 
      //Serial.print(" Button 2:\t"); Serial.println(is_butt_press2);
      break;
    case OF_SERVO_TURN:
      Serial.print("Servo Helmet:\t"); Serial.print(helmet.read());
      Serial.print("\tServo Neck:\t"); Serial.println(neck.read());
      break;
    case OF_POTENTIOMETR:
      Serial.print("Potentiometr:\t"); Serial.println(analogRead(PIN_POTENTIOMETR));
      break;
    case OF_INPUT:
      Serial.print("Potentiometr:\t"); Serial.print(analogRead(PIN_POTENTIOMETR));
      Serial.print("\tButton 1:\t"); Serial.println(is_butt_press); 
      //Serial.print("\tButton 2:\t"); Serial.println(is_butt_press2);
      break;
    case OF_ALL_INFO:
      Serial.print("\tButton 1:\t"); Serial.print(is_butt_press); 
      //Serial.print("\tButton 2:\t"); Serial.print(is_butt_press2);
      Serial.print("\tPotentiometr:\t"); Serial.print(analogRead(PIN_POTENTIOMETR));
      Serial.print("\tServo Helmet:\t"); Serial.print(helmet.read());
      Serial.print("\tServo Neck:\t"); Serial.println(neck.read());
      break;
    default:
      Serial.println("ERROR: Wrong printMode;");
  }
}
