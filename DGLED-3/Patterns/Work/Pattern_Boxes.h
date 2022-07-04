#include "../../HelperFunctions.h"

#include <Arduino.h>

static const int boxes_pattern_num = 0;

struct pbbox {
    float x;
    float y=-2*DATA_HEIGHT;
    float xs;
    float ys;
};

pbbox randomBox() {
    pbbox retbox;
    retbox.x=random(0,DATA_WIDTH);
    retbox.xs=random(DATA_WIDTH/2,DATA_WIDTH);
    retbox.xs=retbox.xs/200;
    if(random(0,100)>49){
        retbox.xs=retbox.xs*-1;
    }

    if(random(0,100)>49) { //from above
        retbox.y=DATA_HEIGHT*2;
        retbox.ys=((float)(-1)*(float)random(1,100))/(float)100;
    } else { //from below
        retbox.y=-1*DATA_HEIGHT;
        retbox.ys=(float)random(1,100)/(float)100;
    }
    return retbox;
}

#define PBOX_NUM 10
//CRGB storage[DATA_HEIGHT][DATA_WIDTH];

void Pattern_Boxes() {
    
    static int counter=0;
    static bool on=false;

    static pbbox boxes[PBOX_NUM];

    static int firstRun=true; //set variables to default states
    if(firstRun==true){
        for(int h=0;h<DATA_HEIGHT;h++){
        for(int w=0;w<DATA_WIDTH;w++)
        {
            outputs_work[boxes_pattern_num][h][w]=CRGB::White;}
        }
        for(int i=0;i<PBOX_NUM;i++) {
            boxes[i]=randomBox();
        }
    }
    
    firstRun=false;



    
    for(int h=0;h<DATA_HEIGHT;h++){
        for(int w=0;w<DATA_WIDTH;w++)
        {
           // int rand = random(1,255);
            //if(on==true) {storage[h][w]=CRGB::Red;}
            outputs_work[boxes_pattern_num][h][w]=CRGB::White;
            //Serial.println(on);
        }
    }
    for(int i=0;i<PBOX_NUM;i++){
        if(boxes[i].y<(-1*DATA_HEIGHT)||boxes[i].y>(2*DATA_HEIGHT)||boxes[i].x>(2+DATA_WIDTH)||boxes[i].x<-1){
            boxes[i]=randomBox(); //reset box
        }
        boxes[i].x+=boxes[i].xs;//increase position
        boxes[i].y+=boxes[i].ys;
        for(int w=(int)boxes[i].x-1;w<=(int)boxes[i].x+1;w++) {
            for(int h=(int)boxes[i].y-1;h<=(int)boxes[i].y+1;h++) {
                if(isPixelLegal(w,h)==true) {
                    outputs_work[boxes_pattern_num][h][w]=CRGB::Black;
                }
            }
        }
    }

    counter++;
    if(counter>60){counter=0; on=!on;}
}
