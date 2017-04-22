#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct RGBType {
    double r;
    double g;
    double b;
};

void savebmp(const char *filename, int w, int h, int dpi, struct RGBType *data){
    FILE *f;
    int k = w*h;
    int s = 4*k;
    int filesize = 54 + s;
    double factor = 39.375;
    int m  = (int) factor;
    int ppm = dpi*m;
    unsigned char bmpfileheader[14] = {'B','M',0,0,0,0,0,0,0,0,54,0,0,0};
    unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0,24,0};
    for(int x = 2; x < 6; x++){
        bmpfileheader[x] = (unsigned char)(filesize >> (8 * (x-2)));
    }
    for(int x = 4; x < 29; x++){
        if(x < 9){
            bmpinfoheader[x] = (unsigned char)(w >> (8 * (x%4)));
        }
        else if(x < 12){
            bmpinfoheader[x] = (unsigned char)(h >> (8 * (x%4)));
        }
        else if(x > 20 && x < 25){
            bmpinfoheader[x] = (unsigned char)(s >> (8 * (x%4)));
        }
        else if(x > 25 && x < 29){
            bmpinfoheader[x] = (unsigned char)(ppm >> (8 * (x%4)));
        }
        else if(x > 29 && x < 33){
            bmpinfoheader[x] = (unsigned char)( ppm >> (8 *(x%4)));
        }
    }
    f = fopen(filename, "wb");

    fwrite(bmpfileheader,1,14,f);
    fwrite(bmpinfoheader,1,40,f);

    for(int i = 0; i < k; i++){
        struct RGBType rgb = data[i];
        double red = (data[i].r) * 255;
        double green = (data[i].g) * 255;
        double blue = (data[i].b) * 255;

        unsigned char color[3] = { (int)floor(blue), (int)floor(green), (int)floor(red)};

       fwrite(color,1,3,f);
     }
    
};
