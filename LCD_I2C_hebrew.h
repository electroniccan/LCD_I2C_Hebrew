#ifndef LCD_I2C_HEBREW_H
#define LCD_I2C_HEBREW_H

#include <Wire.h>
#include <Arduino.h>

class LCD_I2C_Hebrew {
public:
    LCD_I2C_Hebrew(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows);
    void begin();
    void clear();
    void setCursor(uint8_t col, uint8_t row);
    void write(uint8_t value);
    void print(const char* text);
    void printHebrew(const char* text);

private:
    uint8_t _addr;
    uint8_t _cols;
    uint8_t _rows;
    uint8_t _backlightVal;
    void send(uint8_t value, uint8_t mode);
    void write4bits(uint8_t value);
    void expanderWrite(uint8_t data);
    void pulseEnable(uint8_t data);
    void command(uint8_t value);
    void loadHebrewChars();
    byte hebrewChars[8][8];
    int getHebrewCharIndex(char ch);
};

#endif
