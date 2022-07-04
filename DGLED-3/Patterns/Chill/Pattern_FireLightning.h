#include "../../HelperFunctions.h"

#include <Arduino.h>



struct firepeak {
    float x;
    float y;
    CRGB Color;
};

struct ember {
    float x; 
    float y;
    float ys;
    float xs;
};


#define FIRE_NUM 25
#define EMBER_NUM 50
//CRGB storage[DATA_HEIGHT][DATA_WIDTH];

//base color for fire
#define FIRE_COLOR CRGB::OrangeRed;

ember embers[EMBER_NUM];

void newRandomEmber(float _x, float _y) {
    int i=0;
    for(i=0;i<EMBER_NUM;i++) {
        if(isPixelLegal((int)embers[i].x,(int)embers[i].y)==false) {
            break;//this index will be ours
        } else {
            if(i==EMBER_NUM-1) { //no availible embers, break and set i to -1
                i=-1;
                break;
            }
        }
    }
    if(i==-1) {
        return;//do nothing if we don't have any spare embers
    } else {
        embers[i].x=_x;
        embers[i].y=_y;
        embers[i].xs=(float)random(50,100)/(float)200;
        embers[i].ys=(float)random(50,100)/(float)400;

        if(random(0,100)>50){embers[i].xs*=(float)-1;}
        if(random(0,100)>50){embers[i].ys*=(float)-1;}
    }

}

void Pattern_FireLightning() {

    static const int pattern_num = 0;

    static int counter=0;
    static int level;

    static firepeak firepeaks[FIRE_NUM];
    static firepeak Ending;
    static firepeak Beginning;

    static int firstRun=true; //set variables to default states
    if(firstRun==true){
        Beginning.x=0;
        Beginning.y=DATA_HEIGHT/2;
        Beginning.Color=FIRE_COLOR;

        Ending.x=DATA_WIDTH-1;
        Ending.y=DATA_HEIGHT/2;
        Ending.Color=FIRE_COLOR;

        for(int i=0;i<FIRE_NUM;i++)
        {
            firepeaks[i].x=random(0,DATA_WIDTH-1);
            firepeaks[i].y=random(0,DATA_HEIGHT-1);
            firepeaks[i].Color=FIRE_COLOR;
        }
        for(int i=0;i<FIRE_NUM;i++) {
            embers[i].x=-1;
            embers[i].xs=0;
            embers[i].ys=0;
            embers[i].y=-1;
        }
        for(int h=0;h<DATA_HEIGHT;h++){
            for(int w=0;w<DATA_WIDTH;w++)
            {
            // int rand = random(1,255);
                //if(on==true) {storage[h][w]=CRGB::Red;}
                outputs_chill[pattern_num][h][w]=CRGB::Black;
                //Serial.println(on);
            }   
        }
    }
    firstRun=false;

    bool correctOrder=false;
    
    while(correctOrder==false) { //sort firepeaks by x pos
        correctOrder=true;          //I've been informed that this is "bubblesort". Huh.
        for(int i=0;i<FIRE_NUM-1;i++){
            if(firepeaks[i].x>firepeaks[i+1].x) {
                firepeak temp = firepeaks[i]; //swap 
                firepeaks[i]=firepeaks[i+1];
                firepeaks[i+1]=temp;
                correctOrder=false;
            }
        }
    }
    
    //clear canvas
   /*  for(int h=0;h<DATA_HEIGHT;h++){
        for(int w=0;w<DATA_WIDTH;w++)
        {
        // int rand = random(1,255);
            //if(on==true) {storage[h][w]=CRGB::Red;}
            outputs_chill[pattern_num][h][w]=CRGB::Black;
            //Serial.println(on);
        }   
    }


 */


    for(int h=0;h<DATA_HEIGHT;h++){
        for(int w=0;w<DATA_WIDTH;w++)
        {
            if(outputs_chill[pattern_num][h][w].red>0||outputs_chill[pattern_num][h][w].green>0||outputs_chill[pattern_num][h][w].blue>0)
            {
                outputs_chill[pattern_num][h][w]=outputs_chill[pattern_num][h][w]-CRGB(6,6,6);    
            }
        }
    }
    //set first firepeak
    float xc=Beginning.x;
    float yc=Beginning.y;

    ///fire peak counter
    int fpc=0;


    float xn=firepeaks[fpc].x;
    float yn=firepeaks[fpc].y;

    float dx=xn-xc;//slope
    float dy=yn-yc;


    //draw fire
    for(int x=0;x<DATA_WIDTH;x++){
        float h=yc+(x-xc)*(dy/dx);
        
       // for(int i=(int)h;i>=0;i--) {
            if(isPixelLegal(x,h)==true) {
                outputs_chill[pattern_num][(int)h][x]=FIRE_COLOR;
            }
      //  }
        if(x>xn) { //next fire peak should be selected
            xc=xn;//current point is set to next point
            yc=yn;
            if(fpc>=FIRE_NUM-1) { //if we are at the last fire peak
                xn=Ending.x;//DATA_WIDTH-1;//next point is set to end of line 
                yn=Ending.y;//ending
            } else { //we are not at last fire peak
                if(random(0,100)>80) {
                    int numEmbers=random(0,1);
                    for(int i=0;i<numEmbers;i++){
                        newRandomEmber((float)x,h);
                    }
                }
                fpc++;
                xn=firepeaks[fpc].x;
                yn=firepeaks[fpc].y;
            }
            dx=xn-xc;
            dy=yn-yc;
        }

    }

    for(int i=0;i<FIRE_NUM;i++)
    {
        int rnd=random(1,100);
        if(rnd>74) { firepeaks[i].x+=0.2;} 
        else if(rnd<25) { firepeaks[i].x-=0.2;}

        rnd=random(1,100);
        if(rnd>74) { firepeaks[i].y+=0.2;} 
        else if(rnd<25) { firepeaks[i].y-=0.2;}

        if(firepeaks[i].x>(DATA_WIDTH)||firepeaks[i].x<-1) {firepeaks[i].x=random(0,DATA_WIDTH-1);}
        if(firepeaks[i].y>(DATA_HEIGHT)||firepeaks[i].y<-1) {firepeaks[i].y=random(0,DATA_HEIGHT-1);}
        //firepeaks[i].x
    }

    //randomize beginning    
    int rnd=random(1,100);
    if(rnd>74) { Beginning.y+=0.2;} 
    else if(rnd<25) { Beginning.y-=0.2;}

    if(Beginning.y>(DATA_HEIGHT)||Beginning.y<-1) {Beginning.y=random(0,DATA_HEIGHT-1);}

    //randomize ending    
    rnd=random(1,100);
    if(rnd>74) { Ending.y+=0.2;} 
    else if(rnd<25) { Ending.y-=0.2;}

    if(Ending.y>(DATA_HEIGHT)||Ending.y<-1) {Ending.y=random(0,DATA_HEIGHT-1);}

    for(int i=0;i<EMBER_NUM;i++) {
        if(isPixelLegal((int)embers[i].x,(int)embers[i].y)==true) {
            outputs_chill[pattern_num][(int)embers[i].y][(int)embers[i].x]+=(CRGB::Yellow/2);
            embers[i].x+=embers[i].xs;
            embers[i].y+=embers[i].ys;
        }
    }


   // counter++;
   // if(counter>60){counter=0; on=!on;}
}
