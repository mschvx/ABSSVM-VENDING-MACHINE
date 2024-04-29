#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Servo.h> 

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

const int counterPin = 9; 
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

LiquidCrystal_I2C lcd(0x27, 16, 2);

String enteredString = "";
int balance = 0;
int targetAmount1 = 5;
int targetAmount2 = 10;
int targetAmount3 = 15;
int targetAmount4 = 20;

Servo servo1; 
Servo servo2;
Servo servo3;
Servo servo4;

void setup() {
  pinMode(counterPin, INPUT);
  lcd.backlight();
  lcd.init();
  lcd.print("Choose Item #");
  servo1.attach(10); 
  servo2.attach(11);
  servo3.attach(12);
  servo4.attach(13);
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
            balance = targetAmount1; 
            lcd.print("Insert Coins: ");
            while (balance > 0) {
              if (digitalRead(counterPin) == HIGH) {
                delay(50);
                balance--;
                lcd.setCursor(0, 1);
                lcd.print("Balance: " + String(balance + 1) + " Php       ");
                while (digitalRead(counterPin) == HIGH) {
                  delay(50);
                }
              }
            }
            lcd.clear();
            lcd.print("Thank You!");
            delay(2000);
            servo1.write(45); 
            delay(1000);
            servo1.write(90); 
            lcd.clear();
            lcd.print("Choose Item #");
            enteredString = "";
            break;

          case 2:
            lcd.print("Insert Coins: ");
            balance = targetAmount2;
            while (balance > 0) {
              if (digitalRead(counterPin) == HIGH) {
                delay(50);
                balance--;
                lcd.setCursor(0, 1);
                lcd.print("Balance: " + String(balance + 1) + " Php       ");
                while (digitalRead(counterPin) == HIGH) {
                  delay(50);
                }
              }
            }  
            lcd.clear();
            lcd.print("Thank You!");
            delay(2000);
            servo2.write(50); 
            delay(1000);
            servo2.write(90); 
            lcd.clear();
            lcd.print("Choose Item #");
            enteredString = "";
            break;

          case 3:
            lcd.print("Insert Coins: ");
            balance = targetAmount3;
            while (balance > 0) {
              if (digitalRead(counterPin) == HIGH) {
                delay(50);
                balance--;
                lcd.setCursor(0, 1);
                lcd.print("Balance: " + String(balance + 1) + " Php       ");
                while (digitalRead(counterPin) == HIGH) {
                  delay(50);
                }
              }
            }  
            lcd.clear();
            lcd.print("Thank You!");
            delay(2000);
            servo3.write(68); 
            delay(1000);
            servo3.write(90); 
            lcd.clear();
            lcd.print("Choose Item #");
            enteredString = "";
            break;

          case 4:
            lcd.print("Insert Coins: ");
            balance = targetAmount4;
            while (balance > 0) {
              if (digitalRead(counterPin) == HIGH) {
                delay(50);
                balance--;
                lcd.setCursor(0, 1);
                lcd.print("Balance: " + String(balance + 1) + " Php       ");
                while (digitalRead(counterPin) == HIGH) {
                  delay(50);
                }
              }
            }  
            lcd.clear();
            lcd.print("Thank You!");
            delay(2000);
            servo4.write(70);
            delay(1000);
            servo4.write(90);
            lcd.clear();
            lcd.print("Choose Item #");
            enteredString = "";
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
      delay(1000);
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