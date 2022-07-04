
#include "Config.h"

#include "Patterns/Chill/Pattern_FireLightning.h"
#include "Patterns/Chill/Pattern_Fire.h"
#include "Patterns/Chill/Pattern_ChillAurora.h"

#include "Patterns/Work/Pattern_Boxes.h"
#include "Patterns/Work/Pattern_Labyrinth.h"

#include "Patterns/Party/Pattern_SplatterPaint.h"

//PatternManager patternManager;
//PhysicalLEDManager ledOutput;

#define FRAMES_PER_SECOND  60



mode currentMode=CHILL;

typedef void (*PatternList[])();

PatternList work_Functions = {Pattern_Boxes, Pattern_Labyrinth};
PatternList chill_Functions = {Pattern_FireLightning, Pattern_Fire, Pattern_ChillAurora};
PatternList party_Functions = {Pattern_SplatterPaint};
int currentPattern=2;


CRGB outputs_work[NUM_WORK_PATTERNS][DATA_HEIGHT][DATA_WIDTH];
CRGB outputs_chill[NUM_CHILL_PATTERNS][DATA_HEIGHT][DATA_WIDTH];
CRGB outputs_party[NUM_PARTY_PATTERNS][DATA_HEIGHT][DATA_WIDTH];


CRGB leds[NUM_LED_OUTPUTS][STRING_MAX]; //each LED output



void setup() {
  //delay(3000); // 3 second delay for recovery
  randomSeed(analogRead(A0));
  //Serial.begin(115200); //start debug


  pinMode(32,OUTPUT);
  FastLED.addLeds<LED_TYPE,32,COLOR_ORDER>(leds[0], STRING_MAX).setCorrection(TypicalLEDStrip);

  pinMode(25,OUTPUT);
  FastLED.addLeds<LED_TYPE,25,COLOR_ORDER>(leds[1], STRING_MAX).setCorrection(TypicalLEDStrip);

  pinMode(27,OUTPUT);
  FastLED.addLeds<LED_TYPE,27,COLOR_ORDER>(leds[2], STRING_MAX).setCorrection(TypicalLEDStrip);

  pinMode(12,OUTPUT);
  FastLED.addLeds<LED_TYPE,12,COLOR_ORDER>(leds[3], STRING_MAX).setCorrection(TypicalLEDStrip);

  FastLED.setBrightness(BRIGHTNESS);

  
  delay(200);
}



/////TEST STUFF, TODO: REMOVE
//typedef void (*SimplePatternList[])();
//SimplePatternList gPatterns = { rainbow, rainbowWithGlitter, confetti, sinelon, juggle, bpm };
//SimplePatternList aaaaaaaaaaaaa = {rainbow};

//SimplePatternList gPatterns = {Pattern_Boxes1.Update};


//uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
//uint8_t gHue = 0; // rotating "base color" used by many of the patterns
  
void loop()
{
   
  // Call the current pattern function once, updating the 'leds' array
  //gPatterns[gCurrentPatternNumber]();

  // send the 'leds' array out to the actual LED strip
  
  // insert a delay to keep the framerate modest
 /// FastLED.delay(1000/FRAMES_PER_SECOND); 

    //work_Functions[currentPattern](); //run current pattern update function
   // chill_Functions[currentPattern]();//run current chill function
  //copy leds from pattern to output bufer

/*   for(int h=0;h<DATA_HEIGHT;h++) {
      for(int w = 0;w<DATA_WIDTH;w++) {
        
        if(currentMode==CHILL) {
          chill_Functions[currentPattern]();
          leds[h][w]=outputs_chill[currentPattern][h][w];
        }
        else if (currentMode==WORK){
          work_Functions[currentPattern]();
          leds[h][w]=outputs_work[currentPattern][h][w];
        } */
       // else if (currentMode==PARTY) {
        chill_Functions[currentPattern]();
        for(int h=0;h<DATA_HEIGHT;h++) {
      for(int w = 0;w<DATA_WIDTH;w++) {
          
          leds[h][w]=outputs_chill[currentPattern][h][w];}}
        //}
/*       
      }
  } */

  FastLED.show();
  delay(1000/FRAMES_PER_SECOND);

  // do some periodic updates
  //EVERY_N_MILLISECONDS( 20 ) {  } // slowly cycle the "base color" through the rainbow
  //EVERY_N_SECONDS( 10 ) { } // change patterns periodically
}

/* 
void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
} */
/* 
void rainbow() 
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, gHue, 7);
}

void rainbowWithGlitter() 
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(80);
}

void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}

void confetti() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
}

void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16( 13, 0, NUM_LEDS-1 );
  leds[pos] += CHSV( gHue, 255, 192);
}

void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }
}

void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 20);
  byte dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}

 */