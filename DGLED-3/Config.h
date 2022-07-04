#include "DataTypes.h"
#include <FastLED.h>

FASTLED_USING_NAMESPACE

#ifndef CONFIG_H
#define CONFIG_H



//CONFIG FILE


//mode switch data pins
#define MODE1 11
#define MODE2 10


//LED OUTPUT 
#define NUM_LED_OUTPUTS   4
#define LED_TYPE    WS2811
#define COLOR_ORDER   RGB
#define BRIGHTNESS    40

                                //construtor format: DATA PIN, X OFFSET, Y OFFSET, NUMBER LEDS, ADDRESS OFFSET X, ADDRESS OFFSET Y, X DIRECTION, Y DIRECTION(not shown)
LEDLine LEDlines[NUM_LED_OUTPUTS]= {LEDLine(32,1,0,239,0,0,4),//right side LEDs
                                    LEDLine(25,0,4,239,0,1,4),
                                    LEDLine(27,2,8,239,0,2,4),
                                    LEDLine(12,1,12,239,0,3,4)};

                                   // LEDLine(33,1+116*4,0,123,116,0,4),//left side LEDS
                                   // LEDLine(26,0+116*4,4,123,116,1,4),
                                   // LEDLine(13,2+116*4,8,123,116,2,4),
                                   // LEDLine(14,1+116*4,12,123,116,3,4)};


////
//// OLD DATA
//// V     V 
///LED MAPPING INFO

//numerical canvas info
//numerical canvas tells patterns the max and min values they can use in their calculations. Pixels are computed from canvas values

#define MIN_X 0
#define MIN_Y 0

#define MAX_X 2+116*4+123*4
#define MAX_Y 12

//pixel array info
//pixel array size info. This array stores all the data for the matrix, and is integer based

#define DATA_WIDTH 116+123
#define DATA_HEIGHT 4

#define STRING_MAX 116+123 //maximum number of LEDS in 1 string

//typedefs to make some things easier
typedef CRGB (&pixelCanvas)[DATA_HEIGHT][DATA_WIDTH];


#define NUM_WORK_PATTERNS 5
#define NUM_CHILL_PATTERNS 5
#define NUM_PARTY_PATTERNS 5

extern CRGB outputs_work[NUM_WORK_PATTERNS][DATA_HEIGHT][DATA_WIDTH];
extern CRGB outputs_chill[NUM_CHILL_PATTERNS][DATA_HEIGHT][DATA_WIDTH];
extern CRGB outputs_party[NUM_PARTY_PATTERNS][DATA_HEIGHT][DATA_WIDTH];



//LED hardware pins, LED counts, and LED mapping offsets

///RIGHT SIDE LED BOARD

#define DATA_PIN_R1 32 //data pin of LED line
#define XOFFSET_R1 1 //start positions of each LED line
#define YOFFSET_R1 0

#define DATA_PIN_R2 25
#define XOFFSET_R2 0
#define YOFFSET_R2 4

#define DATA_PIN_R3 27
#define XOFFSET_R3 2
#define YOFFSET_R3 8

#define DATA_PIN_R4 12
#define XOFFSET_R4 1
#define YOFFSET_R4 12

#define NUM_LEDS_R 116 //num LEDS fr right side

///LEFT SIDE LED BOARD

#define DATA_PIN_L1 33
#define XOFFSET_L1 XOFFSET_R1+NUM_LEDS_R*4 //add to existing offset to get a virtual canvas of 
#define YOFFSET_L1 0

#define DATA_PIN_L2 26
#define XOFFSET_L2 XOFFSET_R2+NUM_LEDS_R*4
#define YOFFSET_L2 4

#define DATA_PIN_L3 14
#define XOFFSET_L3 XOFFSET_R3+NUM_LEDS_R*4
#define YOFFSET_L3 8

#define DATA_PIN_L4 13
#define XOFFSET_L4 XOFFSET_R4+NUM_LEDS_R*4
#define YOFFSET_L4 12

#define NUM_LEDS_L 123 //num LEDS fr left side 


///LED MAPPING INFO

//numerical canvas info
//numerical canvas tells patterns the max and min values they can use in their calculations. Pixels are computed from canvas values

#define MIN_X 0
#define MIN_Y 0

#define MAX_X XOFFSET_R3+NUM_LEDS_R*4+NUM_LEDS_L*4
#define MAX_Y 12

//pixel array info
//pixel array size info. This array stores all the data for the matrix, and is integer based

#define WIDTH NUM_LEDS_R+NUM_LEDS_L
#define HEIGHT 4










#endif