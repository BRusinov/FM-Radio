#include <Si4703_Breakout.h>
#include <Wire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int resetPin = 8;
int SDIO = A4;
int SCLK = A5;

Si4703_Breakout radio(resetPin, SDIO, SCLK);
int channel;
int volume = 10;
char rdsBuffer[10];

void setup()
{
  lcd.begin(16, 2);
  Serial.begin(9600);
  int i;
  char a[5][20];
  strcpy(a[0], "a b stations");
  strcpy(a[1], "+ - Volume 0-15");
  strcpy(a[2], "u d Seek up/down");
  strcpy(a[3], "r Listen for RDS");
  strcpy(a[4], "command letter:");
  for(i=0;i<4;i++){
    lcd.print(a[i]);
    delay(3000);
    lcd.setCursor(0,0);
    lcd.clear();
  }
  lcd.print(a[4]);

  radio.powerOn();
  radio.setVolume(10);
}

void loop() {
  if (Serial.available())
  {
    char ch = Serial.read();
    if (ch == 'u') 
    {
      channel = radio.seekUp();
      displayInfo();
    } 
    else if (ch == 'd') 
    {
      channel = radio.seekDown();
      displayInfo();
    } 
    else if (ch == '+') 
    {
      volume ++;
      if (volume == 16) volume = 15;
      radio.setVolume(volume);
      displayInfo();
    } 
    else if (ch == '-') 
    {
      volume --;
      if (volume < 0) volume = 0;
      radio.setVolume(volume);
      displayInfo();
    } 
    else if (ch == 'a')
    {
      channel = 1003;
      radio.setChannel(channel);
      displayInfo();
    }
    else if (ch == 'c')
    {
      channel = 876;
      radio.setChannel(channel);
      displayInfo();
    }
    else if (ch == 'b')
    {
      channel = 1030; 
      radio.setChannel(channel);
      displayInfo();
    }
    else if (ch == 'p')
    {
      channel = 1069; 
      radio.setChannel(channel);
      displayInfo();
    }
    else if (ch == 'h')
    {
      channel = 991; 
      radio.setChannel(channel);
      displayInfo();
    }
    else if (ch == 'r')
    {
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("RDS listening..."); 
     radio.readRDS(rdsBuffer, 15000);
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("RDS heard:");
     lcd.setCursor(0,1);
     lcd.print(rdsBuffer);     
    }
  }
}

void displayInfo()
{
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Channel:"); 
   lcd.setCursor(9,0);
   lcd.print(channel);
   lcd.setCursor(13,0);
   lcd.print("MHz");
   lcd.setCursor(0,1);
   lcd.print("Volume:"); 
   lcd.setCursor(8,1);
   lcd.print(volume);
}
