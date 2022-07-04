#include "..\\Config.h" //weirdly the ".." in the file path actually works to up in dir

#ifndef PATTERN_H
#define PATTERN_H

class Pattern {
    public:
        void Update(); //simulates pattern
        pixelCanvas getPattern();


    private:
       // CRGB buffer[DATA_HEIGHT][DATA_WIDTH];

};

pixelCanvas Pattern::getPattern() {
    //return buffer;
}

void Pattern::Update() {
    //... to be implemented by extender
}


#endif 