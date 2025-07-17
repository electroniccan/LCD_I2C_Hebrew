#include <Wire.h>
#include "LCD_I2C_hebrew.h"

LCD_I2C_Hebrew lcd(0x27, 16, 2);

void setup() {
    lcd.begin();
    lcd.setCursor(0, 0);
    lcd.printHebrew("\xE0\xE1 שלום");
}

void loop() {
}
