#include "DHT.h" //library sessor yang telah di includekan
#include <LiquidCrsytal_PCF8574.h>
#include <Wire.h>

#define DHTPIN 2 //Pin yang digunakan
#define DHTTYPE DHT11 //DHT 11

LiquidCrystal_PCF8574 lcd(0x27);

DHT dht(DHTPIN, DHTTYPE);

byte pin_termo[] = //icon water temperature
{
    B00100,
    B01010,
    B01010,
    B01110,
    B01110,
    B11111,
    B11111,
    B01110
};

byte puc_humd[8] = //icon for water
{
    B00100,
    B00100,
    B01010,
    B01010,
    B10001,
    B10001,
    B01110
};

void setup() {
    Serial.begin(9600);
    Serial.println("Pengujian DHT11");
    lcd.begin(16, 2);
    lcd.setBacklight(255);
    lcd.setCursor(0, 0);
    lcd.print("TRIAL DHT11");
    lcd.setCursor(0, 1);
    lcd.print("Java Creatiox");
    delay(2000);
    lcd.clear();
    lcd.createChar(1, pic_termo);
    lcd.createChar(2, pic_humd);
    dht.begin();
}

void loop() {
    delay(2000);

    //pembacaan data kelembaban
    float humidity_1 = dht.readHumidity();

    //pembacaan format celcius
    float celcius_1 =  dht.readTemperature();

    //pembacaan format Fahrenheit
    float fahrenheit_1 = dht.readtemperature(true);

    //mengecek pembacaan apakah terjadi kegagalan atau tidak
    if(isnan(humidity_1) || isnan(celcius_1) || isnan(fahrenheit_1)){
        Serial.println("Pembacaan dari module sessor gagal!");
        return;
    }
    //prosedur pembacaan data indeks panas dalam bentuk fahrenheit
    float htof = dht.computerHeatIndex(fahrenheit_1, humidity_1);

    //prosedur pembacaan data indeks panas dalam bentuk celcius
    float htoc = dht.computerHeatIndex(celcius_1, humidity_1, false);

    //pembacaan nila pembacaan data kelembaban
    Serial.print("Kelembaban: ");
    Serial.print(humidity_1);
    Serial.print(" %\t");

    //pembacaan nilai pembacaan data suhu
    Serial.print("Suhu : ");
    Serial.print(celcius_1);
    Serial.print("°");
    Serial.print("F");

    lcd.setCursor(0,0);
    lcd.print("DHT11 - LCD 16X2");
    lcd.setCursor(0, 1);
    lcd.write(1);
    lcd.setCursor(1,1);
    lcd.print(celcius_1);
    lcd.print((char)233);
    lcd.serCursor(9 ,1);
    lcd.write(2);
    lcd.setCursor(10, 1);
    lcd.print(humidity_1);
    lcd.print("%");
}