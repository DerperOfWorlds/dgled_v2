#include "../../HelperFunctions.h"

#include <Arduino.h>

//labyrinth is patttern 1
static const int labyrinth_pattern_num = 1;

struct labyrinthbot {
    float x;
    float y;
    float xs;
    float ys;
};

#define BOT_NUM 5
//CRGB storage[DATA_HEIGHT][DATA_WIDTH];

#define SPEED 0.3

void Pattern_Labyrinth() {
    
    static int counter=0;
    static bool on=false;

    static labyrinthbot bots[BOT_NUM];

    static int firstRun=true; //set variables to default states
    if(firstRun==true){
        for(int h=0;h<DATA_HEIGHT;h++){
        for(int w=0;w<DATA_WIDTH;w++)
        {
            outputs_work[labyrinth_pattern_num][h][w]=CRGB::White;}
        }

        for(int i=0;i<BOT_NUM;i++)//initialize all bots
        {
            bots[i].x=random(0,DATA_WIDTH);
            bots[i].y=random(0,DATA_HEIGHT);
            if(random(0,100)>49) { //random direction
                bots[i].xs=SPEED;
                bots[i].ys=0;
            } else {
                bots[i].ys=SPEED;
                bots[i].xs=0;
            }
            if(random(0,100)>49) {//random direction
                bots[i].xs*=-1;
                bots[i].ys*=-1;
            }
        }
    }
    firstRun=false;

   counter++;
    
/*    if(counter>7) {
        //CRGB fade in colors
        for(int h=0;h<DATA_HEIGHT;h++){
            for(int w=0;w<DATA_WIDTH;w++)
            {
                if(outputs_work[labyrinth_pattern_num][h][w].red<255)
                {
                    outputs_work[labyrinth_pattern_num][h][w]=outputs_work[labyrinth_pattern_num][h][w]+CRGB(1,1,1);    
                }
            }
        }
        counter=0;
    } */
    
    
    for(int i=0;i<BOT_NUM;i++){

        //turn bot around if it tries to leave - no escaping
        if(bots[i].y<-2&&bots[i].ys<0){bots[i].ys*=-1;}
        if(bots[i].y>DATA_HEIGHT+2&&bots[i].ys>0){bots[i].ys*=-1;}
        if(bots[i].x>DATA_WIDTH&&bots[i].xs>0){bots[i].xs*=-1;}
        if(bots[i].x<0&&bots[i].xs<0){bots[i].xs*=-1;}
        
        if(random(0,100)>94) { //turn 5% of the time
            float temp=bots[i].xs;
            bots[i].xs=bots[i].ys;//swap x and y speed
            bots[i].ys=temp;

            if(random(0,100)>49){ //whether or not the turn is a left or a right turn is a 50-50 chance and is "random"
                bots[i].xs*=-1;
                bots[i].ys*=-1;
            }
        }

        //delete old position
        int iX=(int)bots[i].x;
        int iY=(int)bots[i].y;
        if(isPixelLegal(iX,iY)) {outputs_work[labyrinth_pattern_num][iY][iX]=CRGB::Black;}//bot position

        bots[i].x+=bots[i].xs;//increase position by speed
        bots[i].y+=bots[i].ys;

        //draw creature at new position
        iX=(int)bots[i].x;
        iY=(int)bots[i].y;
        if(isPixelLegal(iX,iY)) {outputs_work[labyrinth_pattern_num][iY][iX]=CRGB::Blue;}//bot position

        int px[3];//forward locations - used to refresh tiles creatures eat
        int py[3];



        if(bots[i].xs>0)      { px[0]=iX+1; px[1]=iX+1; px[2]=iX+1; py[0]=iY-1; py[1]=iY; py[2]=iY+1;}//right 
        else if(bots[i].xs<0) { px[0]=iX-1; px[1]=iX-1; px[2]=iX-1; py[0]=iY-1; py[1]=iY; py[2]=iY+1;}//left 
        else if(bots[i].ys>0) { py[0]=iY+1; py[1]=iY+1; py[2]=iY+1; px[0]=iX-1; px[1]=iX; px[2]=iX+1;}//up
        else if(bots[i].ys<0) { py[0]=iY-1; py[1]=iY-1; py[2]=iY-1; px[0]=iX-1; px[1]=iX; px[2]=iX+1;}//down 

        

        for(int j=0;j<3;j++) {
            if(isPixelLegal(px[j],py[j])) {outputs_work[labyrinth_pattern_num][py[j]][px[j]]=CRGB::White;}//white refresher position
        }
        
    }

 
}
