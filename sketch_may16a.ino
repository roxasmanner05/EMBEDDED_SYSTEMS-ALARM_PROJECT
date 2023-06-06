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

int LM35 = A2;

int i = 9;
byte lightIntensity;

MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
PS2Keyboard keyboard;

MD_MAX72XX::fontType_t newFont[] PROGMEM = //font yang digunakan
{
	0, 	// 0 
	0, 	// 1 
	0, 	// 2 
	0, 	// 3 
	0, 	// 4 
	0, 	// 5 
	0, 	// 6 
	0, 	// 7 
	0, 	// 8 
	0, 	// 9 
	0, 	// 10 
	0, 	// 11 
	0, 	// 12 
	0, 	// 13 
	0, 	// 14 
	0, 	// 15 
	0, 	// 16 
	0, 	// 17 
	0, 	// 18 
	0, 	// 19 
	0, 	// 20 
	0, 	// 21 
	0, 	// 22 
	0, 	// 23 
	0, 	// 24 
	0, 	// 25 
	0, 	// 26 
	0, 	// 27 
	0, 	// 28 
	0, 	// 29 
	0, 	// 30 
	0, 	// 31 
	1, 0, 	// 32 
	1, 94, 	// 33 !
	3, 12, 0, 12, 	// 34 
	5, 40, 124, 40, 124, 40, 	// 35 
	5, 68, 74, 255, 82, 34, 	// 36 
	6, 70, 38, 16, 8, 100, 98, 	// 37 
	5, 36, 90, 90, 36, 80, 	// 38 
	1, 12, 	// 39 
	3, 24, 36, 66, 	// 40 
	3, 66, 36, 24, 	// 41 
	5, 34, 20, 62, 20, 34, 	// 42 
	5, 16, 16, 124, 16, 16, 	// 43 
	2, 64, 32, 	// 44 
	5, 16, 16, 16, 16, 16, 	// 45 
	1, 64, 	// 46 
	5, 64, 32, 16, 8, 4, 	// 47 
	3, 127, 65, 127, 	// 48 
	3, 66, 127, 64, 	// 49 
	3, 115, 73, 79, 	// 50 
	3, 73, 73, 127, 	// 51 
	3, 15, 8, 127, 	// 52 
	3, 79, 73, 57, 	// 53 
	3, 126, 73, 113, 	// 54 
	3, 1, 1, 127, 	// 55 
	3, 127, 73, 127, 	// 56 
	3, 71, 41, 31, 	// 57 
	1, 20, 	// 58 
	1, 52, 	// 59 
	3, 16, 40, 68, 	// 60 
	4, 40, 40, 40, 40, 	// 61 
	3, 68, 40, 16, 	// 62 
	3, 6, 82, 14, 	// 63 
	0, 	// 64 
	3, 127, 9, 127, 	// 65 
	3, 127, 73, 54, 	// 66 
	3, 127, 65, 65, 	// 67 
	3, 127, 65, 62, 	// 68 
	3, 127, 73, 73, 	// 69 
	3, 127, 9, 9, 	// 70 
	3, 126, 65, 121, 	// 71 
	3, 127, 8, 127, 	// 72 
	3, 65, 127, 65, 	// 73 
	3, 33, 65, 63, 	// 74 
	3, 127, 8, 119, 	// 75 
	3, 127, 64, 64, 	// 76 
	4, 127, 6, 6, 127, 	// 77 
	4, 127, 6, 12, 127, 	// 78 
	3, 62, 65, 62, 	// 79 
	3, 127, 9, 6, 	// 80 
	4, 30, 33, 33, 94, 	// 81 
	3, 127, 9, 118, 	// 82 
	3, 111, 73, 115, 	// 83 
	3, 1, 127, 1, 	// 84 
	3, 127, 64, 127, 	// 85 
	3, 63, 64, 63, 	// 86 
	5, 63, 64, 63, 64, 63, 	// 87 
	4, 103, 28, 28, 99, 	// 88 
	3, 7, 120, 7, 	// 89 
	4, 113, 89, 77, 71, 	// 90 
	2, 127, 65, 	// 91 
	2, 0, 0, 	// 92 
	2, 65, 127, 	// 93 
	5, 8, 4, 2, 4, 8, 	// 94 
	3, 64, 64, 64, 	// 95 
	2, 6, 12, 	// 96 
	3, 116, 84, 124, 	// 97 
	3, 126, 72, 48, 	// 98 
	3, 124, 68, 68, 	// 99 
	3, 112, 80, 126, 	// 100 
	3, 124, 84, 92, 	// 101 
	3, 124, 18, 18, 	// 102 
	3, 76, 82, 62, 	// 103 
	3, 126, 16, 112, 	// 104 
	1, 122, 	// 105 
	2, 64, 58, 	// 106 
	3, 126, 24, 118, 	// 107 
	2, 62, 64, 	// 108 
	5, 124, 4, 124, 4, 124, 	// 109 
	3, 124, 4, 120, 	// 110 
	3, 56, 68, 56, 	// 111 
	3, 124, 20, 28, 	// 112 
	3, 28, 20, 124, 	// 113 
	3, 124, 4, 8, 	// 114 
	3, 72, 84, 36, 	// 115 
	3, 8, 124, 72, 	// 116 
	3, 60, 64, 124, 	// 117 
	3, 60, 64, 60, 	// 118 
	5, 60, 64, 60, 64, 60, 	// 119 
	4, 68, 56, 56, 68, 	// 120 
	3, 76, 80, 60, 	// 121 
	3, 100, 84, 76, 	// 122
	0, 	// 123
	0, 	// 124
	0, 	// 125
	0, 	// 126
	2, 0, 0, 	// 127
	0, 	// 128
	0, 	// 129
	0, 	// 130
	0, 	// 131
	0, 	// 132
	0, 	// 133
	0, 	// 134
	0, 	// 135
	0, 	// 136
	0, 	// 137
	0, 	// 138
	0, 	// 139
	0, 	// 140
	0, 	// 141
	0, 	// 142
	0, 	// 143
	0, 	// 144
	0, 	// 145
	0, 	// 146
	0, 	// 147
	0, 	// 148
	0, 	// 149
	0, 	// 150
	0, 	// 151
	0, 	// 152
	0, 	// 153
	0, 	// 154
	0, 	// 155
	0, 	// 156
	0, 	// 157
	0, 	// 158
	0, 	// 159
	0, 	// 160
	0, 	// 161
	0, 	// 162
	0, 	// 163
	0, 	// 164
	0, 	// 165
	0, 	// 166
	0, 	// 167
	0, 	// 168
	0, 	// 169
	0, 	// 170
	0, 	// 171
	0, 	// 172
	0, 	// 173
	0, 	// 174
	0, 	// 175
	2, 6, 6, 	// 176
	0, 	// 177
	0, 	// 178
	0, 	// 179
	0, 	// 180
	0, 	// 181
	0, 	// 182
	0, 	// 183
	0, 	// 184
	0, 	// 185
	0, 	// 186
	0, 	// 187
	0, 	// 188
	0, 	// 189
	0, 	// 190
	0, 	// 191
	0, 	// 192
	0, 	// 193
	0, 	// 194
	0, 	// 195
	0, 	// 196
	0, 	// 197
	0, 	// 198
	0, 	// 199
	0, 	// 200
	0, 	// 201
	0, 	// 202
	0, 	// 203
	0, 	// 204
	0, 	// 205
	0, 	// 206
	0, 	// 207
	0, 	// 208
	0, 	// 209
	0, 	// 210
	0, 	// 211
	0, 	// 212
	0, 	// 213
	0, 	// 214
	0, 	// 215
	0, 	// 216
	0, 	// 217
	0, 	// 218
	0, 	// 219
	0, 	// 220
	0, 	// 221
	0, 	// 222
	0, 	// 223
	0, 	// 224
	0, 	// 225
	0, 	// 226
	0, 	// 227
	0, 	// 228
	0, 	// 229
	0, 	// 230
	0, 	// 231
	0, 	// 232
	0, 	// 233
	0, 	// 234
	0, 	// 235
	0, 	// 236
	0, 	// 237
	0, 	// 238
	0, 	// 239
	0, 	// 240
	0, 	// 241
	0, 	// 242
	0, 	// 243
	0, 	// 244
	0, 	// 245
	0, 	// 246
	0, 	// 247
	0, 	// 248
	0, 	// 249
	0, 	// 250
	0, 	// 251
	0, 	// 252
	0, 	// 253
	0, 	// 254
	0, 	// 255
};
 
void setup()
{
  pinMode(A0, INPUT); //input LDR
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.begin(9600);
  P.begin();
  P.setInvert(false); 
  P.setIntensity(0);
  P.setFont(newFont);
  Wire.begin();
  keyboard.begin(8, 3);

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  P.displayText("Muhammad Risyad Ibenzani - 5024201043", PA_CENTER, 50, 0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  while (!P.displayAnimate());
}

String Hour;
String TIMP=" ";
String HOUR=" ";
String MINUTE=" ";
String SECOND=" ";
String DATA="";
 
String Day;
String Month;
String Year;
String CelSTR;
 
void loop()
{
  char key = keyboard.read();

  DateTime now = rtc.now();
  lightIntensity = analogRead(A0);
  if (lightIntensity <= 127)
  {
    P.setIntensity(10);
  }
  else if(lightIntensity >= 128)
  {
    P.setIntensity(0.5);
  }

  float t = temp();
  CelSTR = String(t,1);
  CelSTR = CelSTR + "°C";
  const char *CelC = CelSTR.c_str(); 

  HOUR = (now.hour());
  if (HOUR.length() < 2)
  {
    HOUR = "0"+ HOUR;
  }
 
  MINUTE = (now.minute());
  if (MINUTE.length() < 2)
  {
    MINUTE = "0"+ MINUTE;
  }

  SECOND = (now.second());
  if (SECOND.length() < 2)
  {
    SECOND = "0"+ SECOND;
  }
  
  if (now.second()%2 == 0)
  {
    TIMP = HOUR + ":" + MINUTE + ":" + SECOND;
  }
  else
  {
    TIMP = HOUR + " " + MINUTE + " " + SECOND;
  }
 
  const char *Timp = TIMP.c_str();
 
  Day = now.day();
  Month = now.month();
  Year = now.year() - 2000;
 
  String Date = Day + "-" + Month + "-" + Year;
  const char *Data = Date.c_str(); 

  if (key == '1')
  {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(800);
    digitalWrite(BUZZER_PIN, LOW);
    delay(800);
    digitalWrite(BUZZER_PIN, HIGH);
    P.displayText("1. 5024201043", PA_LEFT, 50, 1000, PA_SCROLL_LEFT, PA_SCROLL_LEFT); //tampil tanggal
    while (!P.displayAnimate());
    digitalWrite(BUZZER_PIN, LOW);
    loop();
  }
  if (key == '2')
  {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(800);
    digitalWrite(BUZZER_PIN, LOW);
    delay(800);
    digitalWrite(BUZZER_PIN, HIGH);
    P.displayText("2. 5024201043 Muhammad Risyad Ibenzani", PA_LEFT, 50, 1000, PA_SCROLL_LEFT, PA_SCROLL_LEFT); //tampil tanggal
    while (!P.displayAnimate());
    digitalWrite(BUZZER_PIN, LOW);
    loop();
  }
  if (key == '3')
  {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(800);
    digitalWrite(BUZZER_PIN, LOW);
    delay(800);
    digitalWrite(BUZZER_PIN, HIGH);
    P.displayText("3. ", PA_LEFT, 50, 1000, PA_SCROLL_LEFT, PA_SCROLL_LEFT); //tampil tanggal
    while (!P.displayAnimate());
    digitalWrite(BUZZER_PIN, LOW);
    loop();
  }

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
  else
  {
    P.displayText(Timp, PA_CENTER, 50, 0, PA_PRINT, PA_NO_EFFECT); // tampil jam
    while (!P.displayAnimate());
  }
}

float temp()
{
    //float t1 = analogRead(LM35);
    //float t = t1 * 0.48875855;
    float t1 = analogRead(LM35);
    float t = (t1 * 4.88);
    t = (t/10);
    return t;
}