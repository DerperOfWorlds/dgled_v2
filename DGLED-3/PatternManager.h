//Simulates patterns and transitions between them


//#include "Patterns/Pattern.h"
#include "Config.h"
#include "PatternTransition.h"

//patterns
//#include "Pattern_Boxes.h"



#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

//lists of function update and return buffer functions
typedef void (*PatternUpdateList[])();
PatternUpdateList work_UpdateFunctions = {BoxUpdate};



class PatternManager {

    // List of patterns to cycle through.  Each is defined as a separate function below.
    mode currentMode=WORK;
    bool modeTransition=false; //pushes a quick pattern change to get to new mode

    //update functions: simulates pattern
   // PatternList party_UpdateFunctions = {rainbow};

   // PatternList chill_UpdateFunctions = {};

    //display get functions - gets pointer to buffer used by pattern
    pixelCanvas (*party_DisplayFunctions[0])() = {};
    pixelCanvas (*work_DisplayFunctions[1])() = {};   
    pixelCanvas (*chill_DisplayFunctions[0])() = {};

    uint8_t currentPattern = 0; // Index number of which pattern is current
    uint8_t oldPattern = 0;     //old pattern. During a pattern transition, the older pattern becomes the old pattern and the new pattern is the current one

    public:
        PatternManager();

        pixelCanvas Update();
        void setMode(mode _mode);
};

PatternManager::PatternManager() {
   // patternUpdateFunctions={ rainbow, rainbowWithGlitter, confetti, sinelon, juggle, bpm };
}

//set mode
void PatternManager::setMode(mode _mode) {
    if(currentMode!=_mode) {//only change mode if new requested mode is different than current mode
        currentMode=_mode;
        modeTransition=true;
    }
}

pixelCanvas PatternManager::Update()
{
    switch (currentMode) {
        case CHILL:

            break; //shouldn't need this but paranoid lol
        case WORK:
            work_UpdateFunctions[currentPattern](); //run update function to ensure current pattern is simulated
            return work_DisplayFunctions[currentPattern](); //eventaully add transitions here

            break; //shouldn't need this but paranoid lol
        case PARTY:

            break; //shouldn't need this but paranoid lol
    }
}