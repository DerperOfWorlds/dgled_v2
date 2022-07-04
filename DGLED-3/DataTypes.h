#ifndef CONFIG_DATATYPES_H
#define CONFIG_DATATYPES_H

//deals with organizing  data

//current mode of the system
enum mode {
    OFF,
    CHILL,
    WORK,
    PARTY
};




//stores and organizes data for one LED "line"
class LEDLine {
    public:

        LEDLine();//default constructor for auto creation
        LEDLine(int _dataPin, int _Xoffset, int _Yoffset, int _numLEDs, int _Xaddr, int _Yaddr, int _Xdir=4, int _Ydir=0); 
        int getXpos(int index); //gets x postion of a specific LED given its index in the line / string
        int getYpos(int index); //same for y
        int getNumLEDs();
        int getDataPin();

        int getMaxXpos();
        int getMinXpos();
        int getMaxYpos();
        int getMinYpos();

        int getXaddr();
        int getYaddr();
    private:
        int dataPin;

        int Xoffset;
        int Yoffset;
 
        int Xaddr; //X and y start addresses
        int Yaddr; //postion within the matrix

        int numLEDs;

        int Xdir; //X direction in which string propagates. For example, the LED at index 0 is at x = 0. The LED at index 1 is at x = Xdir. LED at index 2 is x = 2*Xdir..
        int Ydir;
 


};

LEDLine::LEDLine() {
    dataPin = 0;
    Xoffset = 0;
    Yoffset = 0;
    numLEDs = 0;
    Xdir=0;
    Ydir=0;
}

LEDLine::LEDLine(int _dataPin, int _Xoffset, int _Yoffset, int _numLEDs, int _Xaddr, int _Yaddr, int _Xdir, int _Ydir) {
    dataPin = _dataPin;
    Xoffset = _Xoffset;
    Yoffset = _Yoffset;
    numLEDs = _numLEDs;

    Yaddr=_Yaddr;
    Xaddr=_Xaddr;

    Xdir=_Xdir;
    Ydir=_Ydir;
}

int LEDLine::getNumLEDs() {
    return numLEDs;
}

int LEDLine::getXpos(int index) {
    return Xoffset+index*Xdir;
}

int LEDLine::getYpos(int index) {
    return Yoffset+index*Ydir;
}

int LEDLine::getDataPin() {
    return dataPin;
}

int LEDLine::getMaxXpos() {
    if(Xdir>0){ //max position is in X positive
        return Xoffset+Xdir*numLEDs;
    }
    else if(Xdir<=0) { //max position is at start of led strip
        return Xoffset;
    }

}

int LEDLine::getMinXpos() {
    if(Xdir>=0){ //min position is start of led strip
        return Xoffset;
    }
    else if(Xdir<0) { //min position is at end of strip towards X-
        return Xoffset+Xdir*numLEDs;
    }  
}

int LEDLine::getMaxYpos() {
    if(Ydir>0){ //max position is in Y positive
        return Yoffset+Ydir*numLEDs;
    }
    else if(Ydir<=0) { //max position is at start of led strip
        return Yoffset;
    }

}

int LEDLine::getMinYpos() {
    if(Ydir>=0){ //min position is start of led strip
        return Yoffset;
    }
    else if(Ydir<0) { //min position is at end of strip towards Y-
        return Yoffset+Ydir*numLEDs;
    }  
}

int LEDLine::getXaddr() {
    return Xaddr;
}

int LEDLine::getYaddr() {
    return Yaddr;
}

//

/* 

class LEDarray
{

    LEDLine *array;
    int size;

    public:

        LEDarray (int _size)
        {
            size = _size;
            array = new LEDLine[_size];
        }
}; */





#endif