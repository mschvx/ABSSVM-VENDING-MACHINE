#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 3;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[ROWS] = {8, 7, 6, 5};
byte colPins[COLS] = {4, 3, 2};

const int counterPin = 10; 
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

LiquidCrystal_I2C lcd(0x27, 16, 2);

String enteredString = "";
int balance = 0;
int targetAmount = 5;

void setup() {
  pinMode(counterPin, INPUT);
  lcd.backlight();
  lcd.init();
  lcd.print("Choose Item #");
  balance = targetAmount; 
}

void loop() {
  char customKey = customKeypad.getKey();

  if (customKey) {
    lcd.clear();
    lcd.print("Choose Item #");
    lcd.setCursor(0, 1);
    lcd.setBacklight(1);

    if (customKey == '*') {
      if (enteredString.length() > 0) {
        enteredString.remove(enteredString.length() - 1);
      }
    } else if (customKey == '#') {
      lcd.clear();
      if (enteredString.length() == 0) {
        lcd.print("Pick a number");
      } else {
        int selectedNumber = enteredString.toInt();
        switch (selectedNumber) {
          case 1:
            lcd.print("Insert coins: ");
            while (balance > 0) {
              if (digitalRead(counterPin) == HIGH) {
                delay(50);
                balance--;
                lcd.setCursor(0, 1);
                lcd.print("Balance: " + String(balance + 1) + " pesos");
                while (digitalRead(counterPin) == HIGH) {
                  delay(50);
                }
              }
            }
            lcd.clear();
            lcd.print("Thank you!");
            delay(2000);
            lcd.clear();
            lcd.print("Choose Item #");
            enteredString = "";
            balance = targetAmount; 
            break;

          default:
            lcd.print("INVALID NUMBER");
            delay(3000);
            lcd.clear();
            lcd.print("Choose Item #");
            enteredString = "";
            break;
        }
      }
      delay(3000);
      lcd.clear();
      lcd.print("Choose Item #");
      enteredString = "";
    } else if (customKey >= '0' && customKey <= '9') {
      enteredString = customKey;
    } else {
      lcd.print("INVALID NUMBER");
      delay(3000);
      lcd.clear();
      lcd.print("Choose Item #");
      enteredString = "";
    }

    lcd.setCursor(0, 1);
    lcd.print(enteredString);
  }
}
