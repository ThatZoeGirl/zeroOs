#pragma once

//Chunk size for spi transfers
#define DATA_CHUNK_SIZE (6,144)

//Control pins
#define DC_PIN (25)
#define RST_PIN (24)

//Screen dimentions
#define Width (320)
#define Height (240)

//Screen effects
//uncomment for inverted colors
#define INVERTED_COLORS

#define RGB_ORDER
//#define GBR_ORDER

//orientation
//#define DEG0 // uncomment for O degree orientation
//#define DEG90 // uncomment for 90 degree orientation
//#define DEG180 // uncomment for 180 degree orientation
#define DEG270 // uncomment for 270 degree orientation

#ifdef DEG0
#define TFT_WIDTH (Height)
#define TFT_HEIGHT (Width)
#endif

#ifdef DEG180
#define TFT_WIDTH (Height)
#define TFT_HEIGHT (Width)
#endif

#ifdef DEG90
#define TFT_WIDTH (Width)
#define TFT_HEIGHT (Height)
#endif

#ifdef DEG270
#define TFT_WIDTH (Width)
#define TFT_HEIGHT (Height)
#endif