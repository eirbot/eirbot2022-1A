#include <Arduino.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

// Afficheur LCD
int rs = 12;
int en = 11;
int d4 = 5;
int d5 = 4;
int d6 = 3;
int d7 = 2;
int counter = 0;

// Interrupteurs
int scorePlusPin = 7;
int scoreMoinsPin = 6;
int sensorPin = 9;
int coteTablePin = A0;
int stratPin = 8;
int departure = A1;

int an1 = A2;
int an2 = A3;

// Serial
int _RX = A4;
int _TX = A5;

// Variables gloables
int strat;
int score;
int sensor;
int coteTable;

// Varaibles séries
String serial;
String serial_prec;

// Variables de tempp;
static unsigned int p_LCD = 100;
static unsigned int p_switch = 10;

// Robot démarrer ou non
int depart = 0;

SoftwareSerial nucleo(_RX, _TX);
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void switchs_read()
{
  strat = digitalRead(stratPin);

  if (digitalRead(scorePlusPin))
  {
    score = score + 1;
    delay(150);
  }
  if (digitalRead(scoreMoinsPin) && score > 0)
  {
    score = score - 1;
    delay(150);
  }

  sensor = digitalRead(sensorPin);

  coteTable = digitalRead(an1);
}

void switchs_print()
{
  if (strat)
  {
    lcd.setCursor(0, 2);
    lcd.print("      ");
    lcd.setCursor(0, 2);
    lcd.print("Automatic");
  }
  else
  {
    lcd.setCursor(0, 2);
    lcd.print("         ");
    lcd.setCursor(0, 2);
    lcd.print("Manual");
  }
  if (sensor)
  {
    lcd.setCursor(7, 1);
    lcd.print("   ");
    lcd.setCursor(7, 1);
    lcd.print("ON");
  }
  else
  {
    lcd.setCursor(7, 1);
    lcd.print("  ");
    lcd.setCursor(7, 1);
    lcd.print("OFF");
  }
  if (coteTable)
  {
    lcd.setCursor(7, 3);
    lcd.print("      ");
    lcd.setCursor(7, 3);
    lcd.print("Jaune");
  }
  else
  {
    lcd.setCursor(7, 3);
    lcd.print("     ");
    lcd.setCursor(7, 3);
    lcd.print("Violet");
  }
  lcd.setCursor(6, 0);
  lcd.print("    ");
  lcd.setCursor(6, 0);
  lcd.print(score);
}

void serial_read()
{
  String c;
  c = nucleo.read();
  if (c != "-1")
  {

    serial = c;
  }
  // serial = nucleo.read();
  //  Serial.print("overflow : ");
  //  Serial.println(nucleo.overflow());
  //  return (byte) nucleo.read();
  //  if (nucleo.available() && nucleo.listen()==0))
  //  }
}

void serial_LCD()
{
  lcd.setCursor(14, 0);
  lcd.print("  ");
  lcd.setCursor(14, 0);
  lcd.print(serial);
}

void serial_LCD_messages()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  if (serial == "10")
  {
    lcd.print("C'est parti le robot !!");
  }
  if (serial == "20")
  {
    lcd.print("La statuette a ete recuperee !!");
  }
  if (serial == "40")
  {
    lcd.print("Aller le robot !!");
  }
  if (serial == "50")
  {
    lcd.print("Unchart'eirb <3, aller on y va !!");
  }
  delay(5000);
  lcd.clear();
}

void send_2_nucleo()
{
  byte valeur_envoie;
  if (serial == 0)
  {
    valeur_envoie = 0;
  }
  else
  {
    valeur_envoie = 1 + strat + 2 * sensor + 4 * coteTable;
  }
  if ((String)valeur_envoie != serial)
  {
    nucleo.write(valeur_envoie);
  }
}


void setup()
{
  Serial.begin(9600);
  nucleo.begin(9600);

  lcd.begin(16, 4);
  lcd.setCursor(0, 0);
  lcd.print("Score:");
  lcd.setCursor(0, 1);
  lcd.print("Sensor:");
  lcd.setCursor(0, 2);
  lcd.print("Automatic");
  lcd.setCursor(0, 3);
  lcd.print("Switch:");

  pinMode(scorePlusPin, INPUT);
  pinMode(scoreMoinsPin, INPUT);
  pinMode(sensorPin, INPUT);
  pinMode(coteTablePin, INPUT);

  pinMode(stratPin, INPUT);
}

void loop()
{
  static unsigned int mem_LCD = millis();
  static unsigned int mem_switchs = millis();
  serial_read();
  if (serial == "10")
  {
    depart = 1;
  }
  if (depart == 0)
  {
    if (millis() - mem_switchs >= p_switch)
    {
      switchs_read();
      mem_LCD += p_switch;
    }
    if (millis() - mem_LCD >= p_LCD)
    {
      switchs_print();
      serial_LCD();
      mem_LCD += p_LCD;
    }
    send_2_nucleo();
  }
  else if (depart == 1)
  {
    if (millis() - mem_LCD >= p_LCD)
    {
      if (serial == "30")
      {
        lcd.print("Score:");
        lcd.setCursor(6, 0);
        lcd.print(20);
        while (true)
        {
          delay(5000);
        }
      }
      serial_LCD_messages();
      mem_LCD += p_LCD;
    }
  }
}
