#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x20, 16, 2);

#define led 3
int baselineTemp = 15;
int celsius = 0;
int fahrenheit = 0;
int tempOffset = 0;
int bot = 7;

int estadoBot = 1;

const int sensorMoisturePin = A1;
const int sensorMoisturePower = 8;
int sensorMoisture;

void setup()
{
  pinMode(A0, INPUT);
  pinMode(led, OUTPUT);
  pinMode(sensorMoisturePower, OUTPUT);
  pinMode(bot, INPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("temp:");
  lcd.setCursor(11, 0);
  lcd.print("umid:"); // umid
  Serial.begin(9600);
}
void loop()
{
  digitalWrite(sensorMoisturePower,HIGH);
  delay(10);
  
  estadoBot = digitalRead(bot);
  
  
  baselineTemp = 15;
  int sensorValue = analogRead(A0);
  float voltage = sensorValue * (5.0 / 1023.0);
  celsius = (voltage - 0.5) * 100 + tempOffset;
  fahrenheit = ((celsius * 9) / 5 + 32);

  // leitura do sensor de umidade:
  sensorMoisture = analogRead(sensorMoisturePin);
  
  // int sensorMoisturePercentage = map(sensorMoisture, 0, 1023, 0, 100);
  int sensorMoisturePercentage = ((sensorMoisture / 1023.00) * 100);

  // leitura sensor de umidade:
  Serial.print("Moisture value:");
  Serial.println(sensorMoisture);
 
  Serial.print("Moisture percentage:");
  Serial.println(sensorMoisturePercentage);

  if (celsius > baselineTemp)
  {
    digitalWrite(led, HIGH);
  }
  else
  {
    digitalWrite(led, LOW);
  }

  lcd.setCursor(0, 1);
  lcd.print(celsius);
  lcd.print("C ");
  lcd.print(fahrenheit);
  lcd.print("F ");

  // umid
  lcd.setCursor(11, 1);
  lcd.print(sensorMoisturePercentage);
  lcd.print("%");

  delay(1000);
}
