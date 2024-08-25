#include <LiquidCrystal_I2C.h>
#include<dht.h>
#include <Wire.h>
#include <BMP180.h>

#define DHT11_PIN A0
#define mq135_pin A2

dht DHT;
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);
BMP180 myBMP(BMP180_ULTRAHIGHRES);

void ReadDHT(void);
void ReadBMP(void);
void ReadAir(void);
bool BMP_flag = 0;
bool DHT_flag = 0;


void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print(" IoT Weather ");
  delay(1500);

}

void loop() {
  // put your main code here, to run repeatedly:
  ReadDHT();
  ReadBMP();
  ReadAir();
}

// void ReadDHT(void)
// {
//   lcd.clear();
//   dht.begin();
//   dht.read(DHT11_PIN);
//   lcd.print(dht.readHumidity());
//   lcd.setCursor(0,1);
//   lcd.print(dht.readTemperature());
//   delay(2000);
// }

void  ReadDHT(void)
{
  // dht.begin();
  lcd.clear();
  int chk = DHT.read11(DHT11_PIN);
  lcd.print("TEMP: ");
  lcd.print(DHT.temperature);
  lcd.setCursor(0,1);
  lcd.print("HUMIDITY: ");
  lcd.print(DHT.humidity);
  delay(2000);
}

void ReadBMP(void)
{
  lcd.clear();
  if(myBMP.begin() != true)
  {
    lcd.setCursor(0,0);
    lcd.print("BMP180 Sensor");
    lcd.setCursor(0,1);
    lcd.print(" NOT FOUND");
    BMP_flag = 0;
    delay(1000);
  }
  else
  {
    BMP_flag = 1;
    lcd.setCursor(0,0);
    lcd.print("Pa(Grnd): ");
    lcd.print(myBMP.getPressure());
    lcd.setCursor(0,1);
    lcd.print("pa(sea):  ");
    lcd.print(myBMP.getSeaLevelPressure(115));
  }
  delay(2000);
}

void ReadAir(void)
{
  int airqlty = 0;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("AIR QUALITY:");
  airqlty = analogRead(mq135_pin);
  lcd.print(map(analogRead(mq135_pin), 0, 1024, 99, 0));
  lcd.print("%");
  lcd.setCursor(0, 1);
  if (airqlty <= 180)
    // lcd.print(airqlty);
    lcd.print("GOOD!");
  else if (airqlty > 180 && airqlty <= 225)
    lcd.print("POOR");
  else if (airqlty > 225 && airqlty <= 300)
    lcd.print("VERY BAD");
  else
    lcd.print("TOXIC");
  lcd.print(airqlty);
  delay(2000);
}