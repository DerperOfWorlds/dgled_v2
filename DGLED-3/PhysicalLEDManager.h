//Physical LED layer manager
//drives physical LED outputs via hardware pins, and stores physical LED mappings


#include "Config.h"

#define FASTLED_ALLOW_INTERRUPTS 0
#define FASTLED_ESP32_I2S true

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

class PhysicalLEDManager {
    CRGB leds[NUM_LED_OUTPUTS][STRING_MAX]; //each LED output
    //pixelCanvas data; //input data matrix 

    public:
        PhysicalLEDManager();
        //void write();
        void Update(pixelCanvas data); //write out LED info, also optionally update input data matrix
};

//Constructor MUST BE UPDATED if more LED pins are added
PhysicalLEDManager::PhysicalLEDManager() {
    //data=_data;//initialize data target
    for(int i=0;i<NUM_LED_OUTPUTS;i++) { //add all led strips to FastLED
        switch(LEDlines[i].getDataPin()) {  //I admit this switch statement is horrible but it is necessary due to how FastLED's addLeds functio works
            case 32:
                pinMode(32,OUTPUT);
                FastLED.addLeds<LED_TYPE,32,COLOR_ORDER>(leds[i], STRING_MAX).setCorrection(TypicalLEDStrip);
                break;
            case 25:
                pinMode(25,OUTPUT);
                FastLED.addLeds<LED_TYPE,25,COLOR_ORDER>(leds[i], STRING_MAX).setCorrection(TypicalLEDStrip);
                break;
            case 27:
                pinMode(27,OUTPUT);
                FastLED.addLeds<LED_TYPE,27,COLOR_ORDER>(leds[i], STRING_MAX).setCorrection(TypicalLEDStrip);
                break;
            case 12:
                pinMode(12,OUTPUT);
                FastLED.addLeds<LED_TYPE,12,COLOR_ORDER>(leds[i], STRING_MAX).setCorrection(TypicalLEDStrip);
                break;
            case 33:
                pinMode(33,OUTPUT);
                FastLED.addLeds<LED_TYPE,33,COLOR_ORDER>(leds[i], STRING_MAX).setCorrection(TypicalLEDStrip);
                break;
            case 26:
                pinMode(26,OUTPUT);
                FastLED.addLeds<LED_TYPE,26,COLOR_ORDER>(leds[i], STRING_MAX).setCorrection(TypicalLEDStrip);
                break;
            case 14:
                pinMode(14,OUTPUT);
                FastLED.addLeds<LED_TYPE,14,COLOR_ORDER>(leds[i], STRING_MAX).setCorrection(TypicalLEDStrip);
                break;
            case 13:
                pinMode(13,OUTPUT);
                FastLED.addLeds<LED_TYPE,13,COLOR_ORDER>(leds[i], STRING_MAX).setCorrection(TypicalLEDStrip);
                break;
            default:

                Serial.println("ERROR: LED pin not defined in PhysicalLEDManager.h"); //error to serial console
                delay(3000);//allow user to review error message
                break;
        }
    }

    // set master brightness control
    FastLED.setBrightness(BRIGHTNESS);
}

//update can either just pull data and write it from input data matrix, or update the input data matrix pointer first and then write data out
void PhysicalLEDManager::Update(pixelCanvas data) {

    //if(_data!=NULL){ //update input canvas if applicable
       // data=_data;
   // }U

    //copy LEDs to the output (leds[][]) from input data matrix (data[][]) 
    for(int i=0;i<NUM_LED_OUTPUTS;i++) {
        for(int led = 0;led<LEDlines[i].getNumLEDs();led++)
        {
            leds[i][led]=data[LEDlines[i].getYaddr()][LEDlines[i].getXaddr()+led];
            leds[i][led]=CRGB::Green;
        }

    }

    FastLED.show();  //write out LED data to LEDs
    delay(100);
}