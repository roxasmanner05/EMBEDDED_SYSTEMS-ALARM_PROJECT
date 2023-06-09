#include <MD_Parola.h>
#include <Wire.h>
#include "RTClib.h"
#include <PS2Keyboard.h>

RTC_DS1307 rtc;
 
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CLK_PIN   13
#define DATA_PIN  11
#define CS_PIN    10

#define BUZZER_PIN 7

#define KB_DATA_PIN 8
#define KB_CLK_PIN 3
PS2Keyboard keyboard;

const int LM35 = A2;

byte lightIntensity;

MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

bool alarmState_1 = false;
String alarmhour_1 = "";
String alarmminute_1 = "";
//String alarmdate_1 = "";
//String alarmmonth_1 = "";
//String alarmyear_1 = "";
char *alarmmessage_1 = "5024201043";

bool alarmState_2 = false;
String alarmhour_2 = "";
String alarmminute_2 = "";
//String alarmdate_2 = "";
//String alarmmonth_2 = "";
//String alarmyear_2 = "";
char *alarmmessage_2 = "5024201043 Muhammad Risyad Ibenzani";

bool alarmState_3 = false;
String alarmhour_3 = "";
String alarmminute_3 = "";
//String alarmdate_3 = "";
//String alarmmonth_3 = "";
//String alarmyear_3 = "";
char *alarmmessage_3 = "TEST";

void setup()
{
  pinMode(A0, INPUT); //LDR SENSOR PIN
  pinMode(BUZZER_PIN, OUTPUT); //BUZZER INIT
  Serial.begin(9600);
  P.begin(); //BEGIN PAROLA
  P.setInvert(false); 
  P.setIntensity(0);
  Wire.begin();
  keyboard.begin(KB_DATA_PIN, KB_CLK_PIN); //BEGIN KEYBOARD

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  P.displayText("Muhammad Risyad Ibenzani - 5024201043", PA_CENTER, 50, 0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  while (!P.displayAnimate());
}

String Hour;
String TIMP=" ";
String HOUR=" ";
int hour = 0;
String MINUTE=" ";
int minute = 0;
String SECOND=" ";
int second = 0;
String DATA="";
 
String Day;
int day = 0;
String Month;
int month = 0;
String Year;
int year = 0;
String CelSTR;

int defaultState;

char bracket[20] = ""; //BUFFER FOR TEXT/INPUT FIELD
int length = 0;
char TIMECHAR[20] = ""; //HOLDER FOR TIME INPUT
char DATECHAR[20] = ""; //HOLDER FOR DATE INPUT

void loop()
{
  brightness(); //LIGHT SENSOR AUTO BRIGHTNESS

  char key = keyboard.read(); //READ KEYBOARD INPUT

  while (defaultState == 4)
  {
    setAlarm3();
  }
  while (defaultState == 3)
  {
    setAlarm2();
  }
  while (defaultState == 2)
  {
    setAlarm1();
  }
  while (defaultState == 1)
  {
    TimeSet();
  }
  while (defaultState == 0) 
  {
    clock();
  }
}

void brightness()
{
  lightIntensity = analogRead(A0);

  if (lightIntensity <= 127)
  {
    P.setIntensity(10);
  }
  else if(lightIntensity >= 128)
  {
    P.setIntensity(0.5);
  }
}

void clock() //DEFAULT STATE
{
  brightness();

  char key = keyboard.read();
  DateTime now = rtc.now();

  float t = temp();
  CelSTR = String(t,1);
  CelSTR = CelSTR + "°C";
  const char *CelC = CelSTR.c_str(); 

  HOUR = (now.hour());
  hour = (now.hour());
  if (HOUR.length() < 2)
  {
    HOUR = "0"+ HOUR;
  }
 
  MINUTE = (now.minute());
  minute = (now.minute());
  if (MINUTE.length() < 2)
  {
    MINUTE = "0"+ MINUTE;
  }

  SECOND = (now.second());
  second = (now.second());
  if (SECOND.length() < 2)
  {
    SECOND = "0"+ SECOND;
  }
  
  if (now.second() % 2 == 0) //flasher untuk tanda ":" pada jam
  {
    TIMP = HOUR + ":" + MINUTE + ":" + SECOND;
  }
  else
  {
    TIMP = HOUR + " " + MINUTE + " " + SECOND;
  }
  
  const char *Timp = TIMP.c_str();
 
  Day = now.day();
  day = now.day();
  Month = now.month();
  month = now.month();
  Year = now.year() - 2000;
  year = now.year();
  if (Year.length() < 2)
  {
    Year = "0" + Year;
  }
 
  String Date = Day + "-" + Month + "-" + Year;
  const char *Data = Date.c_str(); 
  checkAlarm();

  if (now.second() == 10 || now.second() == 40)
  {
    P.displayText(Data, PA_CENTER, 75, 3000, PA_PRINT, PA_NO_EFFECT); //tampil tanggal
    while (!P.displayAnimate());
  }
  else if (now.second() == 13 || now.second() == 43)
  {
    P.displayText(CelC, PA_CENTER, 75, 3000, PA_PRINT, PA_NO_EFFECT); //tampil suhu
    while (!P.displayAnimate());
  }
  else if (alarmState_1 == true)
  {
    digitalWrite(BUZZER_PIN, HIGH);
    P.displayText(alarmmessage_1, PA_CENTER, 75, 3000, PA_SCROLL_LEFT, PA_SCROLL_LEFT); //alarm1
    while (!P.displayAnimate());
    digitalWrite(BUZZER_PIN, LOW);
    alarmhour_1 = "";
    alarmminute_1 = "";
    alarmState_1 = false;
    loop();
  }
  else if (alarmState_2 == true)
  {
    digitalWrite(BUZZER_PIN, HIGH);
    P.displayText(alarmmessage_2, PA_CENTER, 75, 3000, PA_SCROLL_LEFT, PA_SCROLL_LEFT); //alarm2
    while (!P.displayAnimate());
    digitalWrite(BUZZER_PIN, LOW);
    alarmhour_2 = "";
    alarmminute_2 = "";
    alarmState_2 = false;
    loop();
  }
  else if (alarmState_3 == true)
  {
    digitalWrite(BUZZER_PIN, HIGH);
    P.displayText(alarmmessage_3, PA_CENTER, 75, 3000, PA_SCROLL_LEFT, PA_SCROLL_LEFT); //alarm3
    while (!P.displayAnimate());
    digitalWrite(BUZZER_PIN, LOW);
    alarmhour_3 = "";
    alarmminute_3 = "";
    alarmState_3 = false;
    loop();
  }
  else if (key == PS2_ESC)
  {
    defaultState = 1;
    loop();
  }
  else if (key == '1')
  {
    defaultState = 2;
    loop();
  }
  else if (key == '2')
  {
    defaultState = 3;
    loop();
  }
  else if (key == '3')
  {
    defaultState = 4;
    loop();
  }
  else
  {
    P.displayText(Timp, PA_CENTER, 50, 0, PA_PRINT, PA_NO_EFFECT); // tampil jam
    while (!P.displayAnimate());
  }
}

String hourInput;
String minuteInput;
String secondInput;
String dayInput;
String monthInput;
String yearInput;

void TimeSet()
{
  brightness();
  if(keyboard.available())
  {
    char key = keyboard.read();
    bracket[length] = key;

    if (key == PS2_DELETE)
    {
      length--;
      if (length <= 0)
      {
        length = 0;
      }
    }
    else if (key == PS2_ESC)
    {
      defaultState = 0;
      memset(bracket, 0, 20);
      length = 0;
      P.displayClear();
      loop();
    }
    else 
    {
      if (key >= '0' && key <= '9')
      {
        length++;
      }
      
      if (length > 8)
      {
        length = 8;
      }
    }
    if (key == PS2_ENTER)
    {
      if (strlen(bracket) == 7)
      {
        strcat (TIMECHAR, bracket);

        hourInput = String(TIMECHAR).substring(0,2);
        minuteInput = String(TIMECHAR).substring(2,4);
        secondInput = String(TIMECHAR).substring(4,7);
        rtc.adjust(DateTime(year,month,day, hourInput.toInt(),minuteInput.toInt(),secondInput.toInt()));
      }
      else if(strlen(bracket) == 9)
      {
        strcat (DATECHAR, bracket);

        dayInput = String(DATECHAR).substring(0,2);
        monthInput = String(DATECHAR).substring(2,4);
        yearInput = String(DATECHAR).substring(4,8);
        rtc.adjust(DateTime(yearInput.toInt(),monthInput.toInt(),dayInput.toInt(), hour,minute,second));
      }
      
      defaultState = false;
      memset(bracket, 0, 20);
      memset(TIMECHAR, 0, 20);
      memset(DATECHAR, 0, 20);
      length = 0;
      P.displayClear();
      loop();
    }

  }
  P.displayText(bracket, PA_LEFT, 75, 0, PA_PRINT, PA_NO_EFFECT);
  P.displayAnimate();
}

void setAlarm1()
{
  brightness();
  if(keyboard.available())
  {
    char key = keyboard.read();
    bracket[length] = key;

    if (key == PS2_DELETE)
    {
      length--;
      if (length <= 0)
      {
        length = 0;
      }
    }
    else if (key == PS2_ESC)
    {
      defaultState = 0;
      memset(bracket, 0, 20);
      length = 0;
      P.displayClear();
      loop();
    }
    else 
    {
      if (key >= '0' && key <= '9')
      {
        length++;
      }
      
      if (length > 8)
      {
        length = 8;
      }
    }
    if (key == PS2_ENTER)
    {
      if (strlen(bracket) == 5)
      {
        strcat (TIMECHAR, bracket);

        alarmhour_1 = String(TIMECHAR).substring(0,2);
        alarmminute_1 = String(TIMECHAR).substring(2,4);
      }
      defaultState = 0;
      memset(bracket, 0, 20);
      memset(TIMECHAR, 0, 20);
      length = 0;
      P.displayClear();
      loop();
    }
  }
  P.displayText(bracket, PA_LEFT, 75, 0, PA_PRINT, PA_NO_EFFECT);
  P.displayAnimate();
}

void setAlarm2()
{
  brightness();
  if(keyboard.available())
  {
    char key = keyboard.read();
    bracket[length] = key;

    if (key == PS2_DELETE)
    {
      length--;
      if (length <= 0)
      {
        length = 0;
      }
    }
    else if (key == PS2_ESC)
    {
      defaultState = 0;
      memset(bracket, 0, 20);
      length = 0;
      P.displayClear();
      loop();
    }
    else 
    {
      if (key >= '0' && key <= '9')
      {
        length++;
      }
      
      if (length > 8)
      {
        length = 8;
      }
    }
    if (key == PS2_ENTER)
    {
      if (strlen(bracket) == 5)
      {
        strcat (TIMECHAR, bracket);

        alarmhour_2 = String(TIMECHAR).substring(0,2);
        alarmminute_2 = String(TIMECHAR).substring(2,4);
      }
      defaultState = 0;
      memset(bracket, 0, 20);
      memset(TIMECHAR, 0, 20);
      length = 0;
      P.displayClear();
      loop();
    }
  }
  P.displayText(bracket, PA_LEFT, 75, 0, PA_PRINT, PA_NO_EFFECT);
  P.displayAnimate();
}

void setAlarm3()
{
  brightness();
  if(keyboard.available())
  {
    char key = keyboard.read();
    bracket[length] = key;

    if (key == PS2_DELETE)
    {
      length--;
      if (length <= 0)
      {
        length = 0;
      }
    }
    else if (key == PS2_ESC)
    {
      defaultState = 0;
      memset(bracket, 0, 20);
      length = 0;
      P.displayClear();
      loop();
    }
    else 
    {
      if (key >= '0' && key <= '9')
      {
        length++;
      }
      
      if (length > 8)
      {
        length = 8;
      }
    }
    if (key == PS2_ENTER)
    {
      if (strlen(bracket) == 5)
      {
        strcat (TIMECHAR, bracket);

        alarmhour_3 = String(TIMECHAR).substring(0,2);
        alarmminute_3 = String(TIMECHAR).substring(2,4);
      }
      defaultState = 0;
      memset(bracket, 0, 20);
      memset(TIMECHAR, 0, 20);
      length = 0;
      P.displayClear();
      loop();
    }
  }
  P.displayText(bracket, PA_LEFT, 75, 0, PA_PRINT, PA_NO_EFFECT);
  P.displayAnimate();
}

void checkAlarm()
{
  if (alarmhour_1.toInt() == hour && alarmminute_1.toInt() == minute)
  {
    alarmState_1 = true;
  }
  if (alarmhour_2.toInt() == hour && alarmminute_2.toInt() == minute)
  {
    alarmState_2 = true;
  }
  if (alarmhour_3.toInt() == hour && alarmminute_3.toInt() == minute)
  {
    alarmState_3 = true;
  }
}

float temp()
{
  float t1 = analogRead(LM35);
  //float t = (t1 * 4.8875855);
  //t = (t/10);
  float t = t1 /2.0479;
  return t;
}