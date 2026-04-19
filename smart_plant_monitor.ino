#include <LiquidCrystal.h>

// LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Pins
const int ldrPin = A0;
const int ledGreen = 8;
const int ledRed = 9;
const int buzzer = 7;

// Seuil luminosité
const int threshold = 500;

// Temps buzzer
unsigned long previousBeep = 0;
const unsigned long interval = 5000; // 5 sec

void setup() {
  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(buzzer, OUTPUT);

  lcd.begin(16, 2);
  lcd.clear();

  Serial.begin(9600);
}

void loop() {

  int lightValue = analogRead(ldrPin);
  Serial.println(lightValue);

  lcd.setCursor(0, 0);
  lcd.print("Light: ");
  lcd.print(lightValue);
  lcd.print("   ");

  if (lightValue > threshold) {

    // Lumière OK
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledRed, LOW);
    digitalWrite(buzzer, LOW);

    lcd.setCursor(0, 1);
    lcd.print("Plant OK       ");
  }

  else {

    // Lumière faible
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledRed, HIGH);

    lcd.setCursor(0, 1);
    lcd.print("Move Plant     ");

    // bip toutes les 5 sec
    if (millis() - previousBeep >= interval) {
      previousBeep = millis();

      digitalWrite(buzzer, HIGH);
      delay(300);
      digitalWrite(buzzer, LOW);
    }
  }

  delay(200);
}