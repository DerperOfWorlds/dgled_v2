#include "Config.h"

#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

bool isPixelLegal(int x,int y) {
    if(x>=DATA_WIDTH||x<0||y>=DATA_HEIGHT||y<0){
        return false;
    } else {
        return true;
    }
}





#endif