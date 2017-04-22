#include <stdio.h>
#include <math.h>
#include "ex.h"

int thisone;

int main(int argc, char* argv[]){

    int dpi = 72;
    int width = 640;
    int height = 480;
    int n = width * height;
    struct RGBType *pixels = (struct RGBType *) malloc(sizeof(struct RGBType) * n);
    
    for(int x = 0; x < width; x++){
        for(int y = 0; y < height; y++){
            thisone = y * width + x;
            pixels[thisone].r = 1;
            pixels[thisone].g = 0;
            pixels[thisone].b = 0;
        }
    }
    savebmp("scene.bmp", width,height,dpi,pixels);
    return 0;
}
