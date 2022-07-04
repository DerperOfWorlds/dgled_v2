#include "../../HelperFunctions.h"

#include <Arduino.h>



struct fbit {
    float x; 
    float y;
    float ys;
    float xs;
};

fbit randomFbit() {
    fbit retbit;
    retbit.x=random(1,DATA_WIDTH-1);
    retbit.y=4;
    retbit.ys=-0.15;
    retbit.xs=random(1,DATA_WIDTH-1)/(DATA_WIDTH-1);
    return retbit;
}


#define FBIT_NUM 20
//CRGB storage[DATA_HEIGHT][DATA_WIDTH];

//base color for fire
#define FIRE_COLOR CRGB::OrangeRed;

void Pattern_Fire() {

    static const int pattern_num = 1;

    static int counter=0;
    static int level;

    static fbit bits[FBIT_NUM];

    static int firstRun=true; //set variables to default states
    if(firstRun==true){
        for(int i=0;i<FBIT_NUM;i++)
        {
            bits[i]=randomFbit();
        }
        

    }
    firstRun=false;


    //fade pattern

    //counter++;
    //if(counter>1){counter=0; on=!on;}
    for(int h=0;h<DATA_HEIGHT;h++){
        for(int w=0;w<DATA_WIDTH;w++)
        {
            if(outputs_chill[pattern_num][h][w].red>0)
            {
                outputs_chill[pattern_num][h][w]=outputs_chill[pattern_num][h][w]-CRGB(1*((DATA_HEIGHT-1)-h),1*((DATA_HEIGHT-1)-h),1*((DATA_HEIGHT-1)-h));    
            }
        }
    }

    for(int i=0;i<FBIT_NUM;i++){

        if(isPixelLegal((int)bits[i].x,(int)bits[i].y)==true) {
            outputs_chill[pattern_num][(int)bits[i].y][(int)bits[i].x]=FIRE_COLOR;
        }
        bits[i].y+=bits[i].ys;
        bits[i].x+=bits[i].xs;
        if(bits[i].y<0){
            bits[i]=randomFbit();
        }
    }


   // counter++;
   // if(counter>60){counter=0; on=!on;}
}
