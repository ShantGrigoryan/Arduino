#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET     -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, & Wire, OLED_RESET);

#define NUMFLAKES     10

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
float def = 25.11;
static const unsigned char PROGMEM logo_bmp[] =
{ 0b00000000, 0b11000000,
  0b00000001, 0b11000000,
  0b00000001, 0b11000000,
  0b00000011, 0b11100000,
  0b11110011, 0b11100000,
  0b11111110, 0b11111000,
  0b01111110, 0b11111111,
  0b00110011, 0b10011111,
  0b00011111, 0b11111100,
  0b00001101, 0b01110000,
  0b00011011, 0b10100000,
  0b00111111, 0b11100000,
  0b00111111, 0b11110000,
  0b01111100, 0b11110000,
  0b01110000, 0b01110000,
  0b00000000, 0b00110000
};

void setup() {
  
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.setTextColor(SSD1306_WHITE);

  pinMode(2 , INPUT_PULLUP);
  pinMode(3 , INPUT_PULLUP);
  pinMode(8 , OUTPUT);


  display.print("Runing start");
  Serial.print("Runing start");
  display.display();
  dht.begin();

}


void loop() {
  //haytararum a popoxakanner , veragrum a jermastijany u xonavutyuny
  float h = dht.readHumidity();


  float t = dht.readTemperature();

  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(2);
  display.println(t);
  display.println(h);

  Serial.print("Temperature --> ");
  Serial.println(t);
  Serial.println(h);
  if (digitalRead(2) == LOW) {
    delay(125);
    def += 0.1;
  }
  if (digitalRead(3) == LOW) {
    delay(125);
    def -= 0.1;
  }
  if (t >= def) {
    TempUp();
  }
  else {
    TempLow();
  }
  display.setCursor(65,10);
  display.print(round(def *100 )/100);
  Serial.print(round(def*10)/10); 
  display.display();
}

void TempUp() {
  digitalWrite(8 , HIGH);
}
void TempLow() {
  digitalWrite(8 , LOW);
}
