/*
 * Tiny4kOLED - Drivers for SSD1306 controlled dot matrix OLED/PLED 128x32 displays
 *
 * Based on ssd1306xled, re-written and extended by Stephen Denne
 * from 2017-04-25 at https://github.com/datacute/Tiny4kOLED
 *
 */
/*
 * SSD1306xLED - Drivers for SSD1306 controlled dot matrix OLED/PLED 128x64 displays
 *
 * @created: 2014-08-12
 * @author: Neven Boyanov
 *
 * Source code available at: https://bitbucket.org/tinusaur/ssd1306xled
 *
 */

// ----------------------------------------------------------------------------

#include <avr/pgmspace.h>

// ----------------------------------------------------------------------------

/* Standard ASCII 18x24 digit font */
const uint8_t ssd1306xled_font18x24_digits [] PROGMEM = {
 
  0x00,0x00,0x80,0xe0,0xf0,0x78,0x3c,0x1c,0x1c,0x1c,0x1c,0x3c,0x78,0xf0,0xe0,0x80,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x01,0x07,0x0f,0x1e,0x3c,0x38,0x38,0x38,0x38,0x3c,0x1e,0x0f,0x07,0x01,0x00,0x00, // 0
  0x00,0x00,0x80,0xc0,0xe0,0xf0,0x78,0xfc,0xfc,0xfc,0xfc,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x00,0x00,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x30,0x30,0x30,0x3f,0x3f,0x3f,0x3f,0x30,0x30,0x30,0x30,0x30,0x00,0x00, // 1
  0x00,0x00,0xc0,0xe0,0xf0,0x78,0x1c,0x1c,0x1c,0x1c,0x1c,0x3c,0xf8,0xf0,0xe0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xc0,0xe0,0xf0,0x78,0x3c,0x1f,0x0f,0x07,0x00,0x00,0x00,0x00,0x00,0x38,0x3c,0x3e,0x3f,0x37,0x33,0x31,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x00,0x00, // 2
  0x00,0x00,0xc0,0xe0,0xf0,0x78,0x3c,0x1c,0x1c,0x1c,0x1c,0x3c,0x78,0xf0,0xe0,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x38,0x3c,0x3c,0x7e,0xff,0xe7,0xc3,0x00,0x00,0x00,0x00,0x06,0x0e,0x1e,0x3c,0x38,0x30,0x30,0x30,0x30,0x38,0x3c,0x1f,0x0f,0x07,0x00,0x00, // 3
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xc0,0xe0,0xf0,0x78,0xfc,0xfc,0xfc,0x00,0x00,0x00,0x00,0x00,0x00,0xc0,0xf0,0xf8,0xbe,0x9f,0x87,0x83,0x80,0x80,0xff,0xff,0xff,0x80,0x80,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x3f,0x3f,0x3f,0x01,0x01,0x00,0x00, // 4
  0x00,0x00,0xfc,0xfc,0xfc,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x00,0x00,0x00,0x00,0x00,0x07,0x0f,0x0f,0x0e,0x0e,0x0e,0x0e,0x0e,0x0e,0x1c,0x3c,0xf8,0xf0,0xe0,0x00,0x00,0x00,0x00,0x0e,0x1e,0x3e,0x38,0x38,0x30,0x30,0x30,0x30,0x38,0x3e,0x1f,0x0f,0x07,0x00,0x00, // 5
  0x00,0x00,0x00,0xc0,0xf0,0xf8,0x38,0x1c,0x1c,0x1c,0x1c,0x1c,0x78,0x70,0x60,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0x70,0x38,0x1c,0x1c,0x1c,0x1c,0x1c,0x78,0xf8,0xf0,0xc0,0x00,0x00,0x00,0x00,0x01,0x07,0x1f,0x1e,0x38,0x30,0x30,0x30,0x30,0x38,0x3e,0x1f,0x0f,0x03,0x00,0x00, // 6
  0x00,0x00,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0xdc,0xfc,0xfc,0x7c,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xc0,0xf0,0xfc,0x3f,0x0f,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3e,0x3f,0x3f,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // 7
  0x00,0x00,0xe0,0xf8,0xf8,0x1c,0x0c,0x0c,0x0c,0x0c,0x0c,0x0c,0x1c,0xf8,0xf8,0xe0,0x00,0x00,0x00,0x00,0xc3,0xe7,0xff,0x3c,0x18,0x18,0x18,0x18,0x18,0x18,0x3c,0xff,0xe7,0xc3,0x00,0x00,0x00,0x00,0x07,0x1f,0x1f,0x38,0x30,0x30,0x30,0x30,0x30,0x30,0x38,0x1f,0x1f,0x07,0x00,0x00, // 8
  0x00,0x00,0xc0,0xf0,0xf8,0x7c,0x1c,0x0c,0x0c,0x0c,0x0c,0x1c,0x78,0xf8,0xe0,0x80,0x00,0x00,0x00,0x00,0x03,0x0f,0x1f,0x1e,0x38,0x38,0x38,0x38,0x38,0x1c,0x0e,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x06,0x0e,0x1e,0x38,0x38,0x38,0x38,0x38,0x1c,0x1f,0x0f,0x03,0x00,0x00,0x00, // 9
};

// ----------------------------------------------------------------------------

const DCfont TinyOLED4kfont18x24Digits = {
  (uint8_t *)ssd1306xled_font18x24_digits,
  18, // character width in pixels
  3, // character height in pages (8 pixels)
  48,57 // ASCII extents
};

// for backwards compatibility
#define FONT8X16DIGITS (&TinyOLED4kfont18x24Digits)
