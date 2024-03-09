#include <Wire.h>
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

const int counterPin = 11;
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

String enteredString = "";
int targetAmount = 0;
bool itemSelected = false;

void setup() {
  pinMode(counterPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  if (!itemSelected) {
    Serial.println("Choose Item #");
    itemSelected = true;  
  }

  char customKey = customKeypad.getKey();

  if (customKey) {
    Serial.print("Key pressed: ");
    Serial.println(customKey);

    if (customKey == '*') {
      if (enteredString.length() > 0) {
        enteredString.remove(enteredString.length() - 1);
      }
    } else if (customKey == '#') {
      if (enteredString.length() == 0) {
        Serial.println("Pick a number");
      } else {
        int selectedItem = enteredString.toInt();
        switch (selectedItem) {
          case 1:
            targetAmount = 5;
            break;
          case 2:
            targetAmount = 10;
            break;
          case 3:
            targetAmount = 15;
            break;
          case 4:
            targetAmount = 20;
            break;
          default:
            Serial.println("Invalid Item");
            delay(2000);
            break;
        }

        if (targetAmount > 0) {
          Serial.println("Selected Item: " + String(selectedItem));
          Serial.println("Insert coins: " + String(targetAmount) + " Php");

          int balance = targetAmount;
          while (balance > 0) {
            if (digitalRead(counterPin) == HIGH) {
              delay(50);
              balance--;
              Serial.println("Balance: " + String(balance + 1) + " Php");
              while (digitalRead(counterPin) == HIGH) {
                delay(50);
              }
            }
          }

          Serial.println("Thank you!");
          delay(2000);
        }
        enteredString = "";
        itemSelected = false;  
      }
    } else if (customKey >= '0' && customKey <= '9') {
      enteredString += customKey;
    } else {
      Serial.println("Invalid Character");
      delay(2000);
    }
  }
}
