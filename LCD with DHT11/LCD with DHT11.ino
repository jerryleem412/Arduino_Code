#include <LiquidCrystal.h>
#include "DHT.h"

#define DHTPIN 6
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const int rs = 8, en = 7, d4 = 12, d5 = 11, d6 = 10, d7 = 9;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

byte degree[8] = {
  0b01000,
  0b10100,
  0b01000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

void setup() {

Serial.begin(9600);
dht.begin();
lcd.begin(20, 4);
lcd.print("I LOVE Alyssa!");
lcd.createChar(0, degree);

}

void loop() {

float h = dht.readHumidity();
float t = dht.readTemperature();
float f = dht.readTemperature(true);

if (isnan(h) || isnan(t) || isnan(f)) {
  Serial.println(F("Failed to read from DHT sensor!"));
  return;
}

float hif = dht.computeHeatIndex(f, h);
float hic = dht.computeHeatIndex(t, h, false);

lcd.setCursor(0, 1);
lcd.print("Temp: ");
lcd.print(f);
lcd.write(byte(0));
lcd.print("F");
lcd.setCursor(0,2);
lcd.print("Rel Humidity: ");
lcd.print(h);
lcd.setCursor(0,3);
lcd.print("Heat Index: ");
lcd.print(hif);
lcd.write(byte(0));
lcd.print("F");

delay(6000);


}
