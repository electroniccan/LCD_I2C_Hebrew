# LCD_I2C_hebrew

**LCD_I2C_hebrew** is an Arduino library for controlling HD44780-compatible I2C LCD displays, with built-in support for displaying Hebrew characters.

## Features

- Native I2C communication (no dependency on `LiquidCrystal_I2C`)
- Hebrew character rendering via `printHebrew()`
- Dynamic loading of Hebrew letters to LCD CGRAM using `loadHebrewToCGRAM()`
- Simple API: `begin()`, `clear()`, `setCursor()`, `write()`, `print()`
- Includes all 27 Hebrew letters (including final forms)
- Example sketch available in `examples/PrintHebrew`

## Usage

```cpp
#include "LCD_I2C_hebrew.h"

LCD_I2C_Hebrew lcd(0x27, 16, 2);

void setup() {
  lcd.begin();
  const char* usedChars = "שלוםלך";
  lcd.loadHebrewToCGRAM(usedChars);
  lcd.setCursor(0, 0);
  lcd.write(0); // ש
  lcd.write(1); // ל
  lcd.write(2); // ו
  lcd.write(3); // ם
}

void loop() {}
```

## Limitations

HD44780 LCDs support only 8 custom characters at a time. To support full Hebrew rendering, this library includes a dynamic character loading function that lets you map up to 8 characters needed for a given display line.

## License

This library is released under the MIT License.