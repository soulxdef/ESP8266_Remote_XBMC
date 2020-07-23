#define BLUEPIN 5
#define REDPIN 4
#define GREENPIN 2
#define PERIOD 30

#include <Arduino.h>

int R,G,B = 0;
int R_old,G_old,B_old = 0;
String RGB_Json = "{}";
int MODE = 0;
uint32_t timer = 0;

String set_RGB(int r,int g, int b)
{
    analogWrite(BLUEPIN, r);
    analogWrite(REDPIN, g);
    analogWrite(GREENPIN, b);
    return "R: " + String(r) + "G: " + String(g) + "B: " + String(b);
}

String RGB_TEST()
{
   set_RGB(255,0,0);
   delay(3000);
   set_RGB(0,255,0);
   delay(3000);
   set_RGB(0,0,255);
   delay(3000);
   set_RGB(0,0,0);
   return "Test Complite";
}

String RGB_init()
{
  RGB_Json = readFile("RGB.json");
  R = jsonReadtoInt(RGB_Json,"RED");
  G = jsonReadtoInt(RGB_Json,"GREEN");
  B = jsonReadtoInt(RGB_Json,"BLUE");
  MODE = jsonReadtoInt(RGB_Json,"MODE");
  pinMode(BLUEPIN, OUTPUT);
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  HTTP.on("/RGBjson.json", HTTP_GET, []() {
    HTTP.send(200, "application/json", RGB_Json);
  });
  return RGB_TEST();
}


void RandomColor()
{
  R = random(0, 255);
  G = random(0, 255);
  B = random(0, 255);
  RGB_Json = jsonWrite(RGB_Json,"RED",R);
  RGB_Json = jsonWrite(RGB_Json,"GREEN",G);
  RGB_Json = jsonWrite(RGB_Json,"BLUE",B);
  saveConfiRGB(RGB_Json);
}

void LedMode()
{
  if (millis() - timer > PERIOD) {
    if(R_old < R)
    {
      R_old++;    
    }else
    {
      R_old--;
    }
    if (G_old < G)
    {
      G_old++;
    }else
    {
      G--;
    }
    if (B_old < B)
    {
      B_old++;
    }else
    {
      B_old--;
    }
     
    set_RGB(R_old,G_old,B_old);
    timer = millis();
}
}