#include <Si4703_Breakout.h>
#include <Wire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int resetPin = 8;
int SDIO = A4;
int SCLK = A5;

Si4703_Breakout radio(resetPin, SDIO, SCLK);
int channel;
int volume;
int setVol;
int currCH;
int setCH;
char rdsBuffer[16];

void setup()
{
  lcd.begin(16, 2);
  Serial.begin(9600);
  int i;
  char a[5][20];
  strcpy(a[0], "FM Radio 2016");
  strcpy(a[1], "by Dimitar&Bobi");
  strcpy(a[2], "Volume 0-15");
  strcpy(a[3], "Freq 88-108MHz");
  strcpy(a[4], "Enjoy ^_^");
  for(i=0;i<4;i++){
    lcd.print(a[i]);
    delay(3000);
    lcd.setCursor(0,0);
    lcd.clear();
  }
  lcd.print(a[4]);

  radio.powerOn();
  volume = 10;
  radio.setVolume(volume);
}

void loop() {
    currCH = analogRead(A1)/5.12 +880;
    setCH = digitalRead(7);
    setVol = analogRead(A1)/68.27;
    if(setCH && channel != currCH){
      channel = analogRead(A1)/5.12 +880; 
      radio.setChannel(channel);
      displayInfo();
    }else if(!setCH && volume != setVol){
      volume = analogRead(A1)/68.27;
      radio.setVolume(volume);
      displayInfo();
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
   if(volume == 0){
    lcd.print("Mute");
   }else{
    lcd.print(volume);
   }
   
}
