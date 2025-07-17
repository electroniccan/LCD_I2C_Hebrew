#include <Wire.h>
#include "ES_LCD_I2C_hebrew.h"

LCD_I2C_Hebrew lcd(0x27, 16, 2);

void setup() {
  lcd.begin();
  const char* usedChars = "שלוםך";
  lcd.loadHebrewToCGRAM(usedChars);
  lcd.setCursor(0, 0);
  lcd.write(0); // ש
  lcd.write(1); // ל
  lcd.write(2); // ו
  lcd.write(3); // ם
  lcd.write(4); // ך
}

void loop() {}