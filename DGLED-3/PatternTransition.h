#include "Config.h"

//WIP
//provides a variety of transition functions to swap smoothly between two patterns
//e.g.
//fade, swipe left/right, swipe up/down, dissolve, 



class PatternTranstion {
    float pattern1[DATA_HEIGHT][DATA_WIDTH];
    float pattern2[DATA_HEIGHT][DATA_WIDTH];

    public:
        PatternTranstion();

        void StartRandomTransition();

        void Update();
};

PatternTranstion::PatternTranstion() {

}