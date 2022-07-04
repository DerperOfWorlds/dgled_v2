#include "../../HelperFunctions.h"

#include <Arduino.h>


void Pattern_SplatterPaint() {

    static const int pattern_num = 0;

    static int counter=0;
    static int level;

    static uint16_t dimension=0;

    

    static int firstRun=true; //set variables to default states
    if(firstRun==true){
       

    }
    firstRun=false;


    //fade pattern
    dimension+=1;
    //counter++;
    //if(counter>1){counter=0; on=!on;}
    static int speed=10;
    for(int h=0;h<DATA_HEIGHT;h++){
        for(int w=0;w<DATA_WIDTH;w++)
        {
            //if(outputs_chill[pattern_num][h][w].red>0)
            {
                uint8_t output=inoise8 (w*30, h*30, dimension*speed);
                output=qsub8(output,16);
                output=qadd8(output,scale8(output,39));
                output-=80;
                //output=qsub8(output,80);

                uint8_t output2=inoise8 (w*30, h*30, (dimension+60)*speed);
                output2=qsub8(output2,16);
                output2=qadd8(output2,scale8(output2,39));
                output2-=50;
                //output2=qsub8(output2,50);

                uint8_t output3=inoise8 (w*30, h*30, (dimension+120)*speed);
                output3=qsub8(output3,16);
                output3=qadd8(output3,scale8(output3,39));
                output3-=80;      
                //output3=qsub8(output3,80);         

                //outputs_chill[pattern_num][h][w]=CRGB(inoise8 ((uint16_t)w<<8, (uint16_t)h<<8, (uint16_t)dimension+2)<<8,inoise8 ((uint16_t)w<<8, (uint16_t)h<<8, (uint16_t)dimension<<8),0);
                outputs_party[pattern_num][h][w]=CRGB(output,output2,output3);
   
            }
        }
    }




}