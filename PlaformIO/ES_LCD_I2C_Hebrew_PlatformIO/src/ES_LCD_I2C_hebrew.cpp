
void LCD_I2C_Hebrew::loadHebrewToCGRAM(const char* chars) {
    for (uint8_t slot = 0; slot < 8 && chars[slot] != '\0'; slot++) {
        byte buffer[8];
        switch (chars[slot]) {
            case 'א': memcpy(buffer, alef, 8); break;
            case 'ב': memcpy(buffer, bet, 8); break;
            case 'ג': memcpy(buffer, gimel, 8); break;
            case 'ד': memcpy(buffer, dalet, 8); break;
            case 'ה': memcpy(buffer, hei, 8); break;
            case 'ו': memcpy(buffer, vav, 8); break;
            case 'ז': memcpy(buffer, zain, 8); break;
            case 'ח': memcpy(buffer, het, 8); break;
            case 'ט': memcpy(buffer, tet, 8); break;
            case 'י': memcpy(buffer, yod, 8); break;
            case 'כ': memcpy(buffer, kaf, 8); break;
            case 'ך': memcpy(buffer, kaf_sofit, 8); break;
            case 'ל': memcpy(buffer, lamed, 8); break;
            case 'מ': memcpy(buffer, mem, 8); break;
            case 'ם': memcpy(buffer, mem_sofit, 8); break;
            case 'נ': memcpy(buffer, nun, 8); break;
            case 'ן': memcpy(buffer, nun_sofit, 8); break;
            case 'ס': memcpy(buffer, samech, 8); break;
            case 'ע': memcpy(buffer, ayin, 8); break;
            case 'פ': memcpy(buffer, pe, 8); break;
            case 'ף': memcpy(buffer, pe_sofit, 8); break;
            case 'צ': memcpy(buffer, tsadi, 8); break;
            case 'ץ': memcpy(buffer, tsadi_sofit, 8); break;
            case 'ק': memcpy(buffer, qof, 8); break;
            case 'ר': memcpy(buffer, resh, 8); break;
            case 'ש': memcpy(buffer, shin, 8); break;
            case 'ת': memcpy(buffer, tav, 8); break;
            default: memset(buffer, 0, 8); break;
        }
        command(0x40 + slot * 8);
        for (int i = 0; i < 8; i++) {
            write(buffer[i]);
        }
    }
}
