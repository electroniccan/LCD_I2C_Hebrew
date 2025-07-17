# LCD_I2C_hebrew

**LCD_I2C_hebrew** is an Arduino library for controlling HD44780-compatible I2C LCD displays with native support for displaying Hebrew characters.

## Features

- Direct I2C communication (no dependency on LiquidCrystal_I2C)
- Hebrew character printing using `printHebrew()`
- Easy-to-use interface: `begin()`, `clear()`, `setCursor()`, `write()`, `print()`
- Includes 8 predefined Hebrew letters (Alef to Chet)
- Example sketch included under `examples/PrintHebrew`

## Usage

```cpp
#include "LCD_I2C_hebrew.h"

LCD_I2C_Hebrew lcd(0x27, 16, 2);

void setup() {
  lcd.begin();
  lcd.setCursor(0, 0);
  lcd.printHebrew("אבגדהוזח");
}

void loop() {}
```

## Limitations

HD44780 LCDs support only 8 custom characters at a time. This library currently includes only the first 8 Hebrew letters (א–ח). For full Hebrew support, the character set must be managed dynamically.

## License

This library is released under the MIT License.
