#include <stdio.h>
#include <math.h>
#include "ex.h"
#include "color.h"
#include "light.h"

int thisone;
struct vect x;
struct vect y;
struct vect z;

int main(int argc, char* argv[]){

    int dpi = 72;
    int width = 640;
    int height = 480;
    int n = width * height;
    struct RGBType *pixels = (struct RGBType *) malloc(sizeof(struct RGBType) * n);
    init_vect(x);
    x.x = 1;
    init_vect(y);
    y.y = 1;
    init_vect(z);
    z.z = 1;

    struct vect look_at;
    init_vect(look_at);
    struct vect campos;
    campos.x = 3;
    campos.y = 1.5;
    campos.z = -4;
    struct vect diff_btw;

    diff_btw.x = campos.x - look_at.x;
    diff_btw.y = campos.y - look_at.y;
    diff_btw.z = campos.z - look_at.z;

    struct vect camdir = normalize(negative(diff_btw));
    struct vect camright = normalize(crossProduct(y, camdir));
    struct vect camdown = crossProduct(camright, camdir);
    struct camera scene_cam;
    scene_cam.campos = campos;
    scene_cam.camdir = camdir;
    scene_cam.camright = camright;
    scene_cam.camdown = camdown;

    struct color white_light;
    white_light.red = 1.0;
    white_light.blue= 1.0;
    white_light.green= 1.0;
    white_light.special = 1.0;

    for(int x = 0; x < width; x++){
        for(int y = 0; y < height; y++){
            thisone = y * width + x;
            pixels[thisone].r = 1;
            pixels[thisone].g = 0;
            pixels[thisone].b = 0;
        }
    }
    savebmp("bitmaps/scene.bmp", width,height,dpi,pixels);
    return 0;
}
