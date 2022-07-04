#include "../../HelperFunctions.h"

#include <Arduino.h>


void Pattern_ChillAurora() {

    static const int pattern_num = 2;

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
    static int speed=5;
    static int zoom=40;
    for(int h=0;h<DATA_HEIGHT;h++){
        for(int w=0;w<DATA_WIDTH;w++)
        {
            //if(outputs_chill[pattern_num][h][w].red>0)
            {

                uint8_t scalefactor=inoise8 (w*10, h*10, dimension*speed);
                scalefactor=qsub8(scalefactor,16);
                scalefactor=qadd8(scalefactor,scale8(scalefactor,39));


                                                ///orginally was h*zoom
                uint8_t output=inoise8 (w*zoom, h*(zoom/3), dimension*speed);
                output=qsub8(output,16);
                output=qadd8(output,scale8(output,39));
                output=qsub8(output,130);
                output=qmul8(output,2);
                
                output=scale8(output,scalefactor);
                //output*=2;

                uint8_t output2=inoise8 (w*zoom, h*(zoom/3), (dimension+40)*speed);
                output2=qsub8(output2,16);
                output2=qadd8(output2,scale8(output2,39));
                output2=qsub8(output2,135);
                output2=qmul8(output2,2);
                //output2*=2;
                output2=scale8(output2,scalefactor);
                //outputs_chill[pattern_num][h][w]=CRGB(inoise8 ((uint16_t)w<<8, (uint16_t)h<<8, (uint16_t)dimension+2)<<8,inoise8 ((uint16_t)w<<8, (uint16_t)h<<8, (uint16_t)dimension<<8),0);
                outputs_chill[pattern_num][h][w]=CRGB(scale8(output,30),output2,output);
   
            }
        }
    }




}