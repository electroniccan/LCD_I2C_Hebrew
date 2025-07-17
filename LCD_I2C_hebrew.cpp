#include "LCD_I2C_hebrew.h"

// LCD commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_FUNCTIONSET 0x20
#define LCD_SETDDRAMADDR 0x80

#define LCD_ENTRYLEFT 0x02
#define LCD_DISPLAYON 0x04
#define LCD_2LINE 0x08
#define LCD_5x8DOTS 0x00
#define LCD_BACKLIGHT 0x08
#define LCD_ENABLE_BIT 0x04
#define LCD_RS 0x01

LCD_I2C_Hebrew::LCD_I2C_Hebrew(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows)
    : _addr(lcd_Addr), _cols(lcd_cols), _rows(lcd_rows), _backlightVal(LCD_BACKLIGHT) {}

void LCD_I2C_Hebrew::begin() {
    Wire.begin();
    delay(50);
    expanderWrite(_backlightVal);
    delay(1000);
    write4bits(0x03 << 4); delay(5);
    write4bits(0x03 << 4); delay(5);
    write4bits(0x03 << 4); delay(1);
    write4bits(0x02 << 4); delay(1);
    command(LCD_FUNCTIONSET | LCD_2LINE | LCD_5x8DOTS);
    command(LCD_DISPLAYCONTROL | LCD_DISPLAYON);
    command(LCD_CLEARDISPLAY);
    command(LCD_ENTRYMODESET | LCD_ENTRYLEFT);
    delay(2);
    loadHebrewChars();
}

void LCD_I2C_Hebrew::clear() {
    command(LCD_CLEARDISPLAY);
    delay(2);
}

void LCD_I2C_Hebrew::setCursor(uint8_t col, uint8_t row) {
    static const uint8_t row_offsets[] = {0x00, 0x40, 0x14, 0x54};
    command(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

void LCD_I2C_Hebrew::write(uint8_t value) {
    send(value, LCD_RS);
}

void LCD_I2C_Hebrew::print(const char* text) {
    while (*text) {
        write(*text++);
    }
}

void LCD_I2C_Hebrew::printHebrew(const char* text) {
    while (*text) {
        int idx = getHebrewCharIndex(*text);
        if (idx >= 0) {
            write(idx);
        } else {
            write(*text);
        }
        text++;
    }
}

void LCD_I2C_Hebrew::command(uint8_t value) {
    send(value, 0);
}

void LCD_I2C_Hebrew::send(uint8_t value, uint8_t mode) {
    uint8_t high = value & 0xF0;
    uint8_t low = (value << 4) & 0xF0;
    write4bits(high | mode);
    write4bits(low | mode);
}

void LCD_I2C_Hebrew::write4bits(uint8_t value) {
    expanderWrite(value);
    pulseEnable(value);
}

void LCD_I2C_Hebrew::expanderWrite(uint8_t data) {
    Wire.beginTransmission(_addr);
    Wire.write(data | _backlightVal);
    Wire.endTransmission();
}

void LCD_I2C_Hebrew::pulseEnable(uint8_t data) {
    expanderWrite(data | LCD_ENABLE_BIT);
    delayMicroseconds(1);
    expanderWrite(data & ~LCD_ENABLE_BIT);
    delayMicroseconds(50);
}

void LCD_I2C_Hebrew::loadHebrewChars() {
    byte alef[8] = {B00100, B01010, B01010, B11111, B10001, B10001, B10001, B00000};
    byte bet[8]  = {B11110, B10001, B10001, B11110, B10000, B10000, B10000, B00000};
    byte gimel[8]= {B00111, B00001, B00001, B01111, B00001, B00001, B01111, B00000};
    byte dalet[8]= {B01111, B01001, B01001, B11111, B10001, B10001, B10001, B00000};
    byte hei[8]  = {B11111, B01000, B01000, B01110, B01000, B01000, B01110, B00000};
    byte vav[8]  = {B00100, B00100, B00100, B00100, B00100, B00100, B00100, B00000};
    byte zain[8] = {B01110, B00100, B00100, B00100, B00100, B00100, B00100, B00000};
    byte het[8]  = {B10001, B10001, B10001, B11111, B10001, B10001, B10001, B00000};

    memcpy(hebrewChars[0], alef, 8);
    memcpy(hebrewChars[1], bet, 8);
    memcpy(hebrewChars[2], gimel, 8);
    memcpy(hebrewChars[3], dalet, 8);
    memcpy(hebrewChars[4], hei, 8);
    memcpy(hebrewChars[5], vav, 8);
    memcpy(hebrewChars[6], zain, 8);
    memcpy(hebrewChars[7], het, 8);

    for (int i = 0; i < 8; i++) {
        command(0x40 + (i * 8));
        for (int j = 0; j < 8; j++) {
            write(hebrewChars[i][j]);
        }
    }
}

int LCD_I2C_Hebrew::getHebrewCharIndex(char ch) {
    switch (ch) {
        case 'א': return 0;
        case 'ב': return 1;
        case 'ג': return 2;
        case 'ד': return 3;
        case 'ה': return 4;
        case 'ו': return 5;
        case 'ז': return 6;
        case 'ח': return 7;
        default: return -1;
    }
}
