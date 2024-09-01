#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Servo.h>

// Crear el objeto lcd dirección 0x27 y 16 columnas x 2 filas 
LiquidCrystal_I2C lcd(0x27, 16, 2); 
char contrasena[] = "2916";
char codigo[4];
int cont = 0;
Servo Servo_3;
const byte ROWS = 4;
const byte COLS = 4;
const int SolenoidPin = 3; // Cambiado a un pin válido

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {
  pinMode(SolenoidPin, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  Servo_3.write(0);
  Servo_3.attach(11, 500, 2500);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(4, 0);
  lcd.print("Contrasena");
  delay(1000); // Aumentado el delay para asegurar que el mensaje se muestre
}

void loop() {
  char customKey = customKeypad.getKey();
  if (customKey != NO_KEY) {
    codigo[cont] = customKey;
    Serial.print(codigo[cont]);
    cont++;
    if (cont == 4) {
      if (codigo[0] == contrasena[0] && codigo[1] == contrasena[1] && codigo[2] == contrasena[2] && codigo[3] == contrasena[3]) {
        Serial.println("Password correcta");
        Servo_3.write(90);
        lcd.setCursor(4, 1);
        lcd.print("Correcta");
        delay(1000); // Aumentado el delay para asegurar que el mensaje se muestre
      } else {
        Servo_3.write(0);
        Serial.println("Password incorrecta");
        lcd.setCursor(4, 1);
        lcd.print("Incorrecta");
        delay(1000); // Aumentado el delay para asegurar que el mensaje se muestre
      }
      cont = 0;
    }
  }
}
