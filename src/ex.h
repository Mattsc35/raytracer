#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct RGBType {
    double r;
    double g;
    double b;
};

struct vect{
    double x;
    double y;
    double z;
};

void init_vect(struct vect v){
    v.x = 0;
    v.y = 0;
    v.z = 0;
};

struct vect normalize(struct vect v){
    double magnitude = (v.x*v.x) + (v.y*v.y) + (v.z*v.z); 
    struct vect new_v;
    new_v.x = v.x/magnitude;
    new_v.y = v.y/magnitude;
    new_v.z = v.z/magnitude;
    return new_v;
}

struct vect negative(struct vect v){
    struct vect new_v;
    new_v.x = -v.x;
    new_v.y = -v.y;
    new_v.z = -v.z;
    return new_v;
}

double dotProduct(struct vect v1, struct vect v2){
    double x_new = v1.x * v2.x;
    double y_new = v1.y * v2.y;
    double z_new = v1.z * v2.z;
    return x_new + y_new + z_new;
}

struct vect crossProduct(struct vect v1, struct vect v2){
    double x_new = v1.y * v2.z - v1.z * v2.y;
    double y_new = v1.x * v2.z - v1.z * v2.x;
    double z_new = v1.x * v2.y - v1.y * v2.z;
    struct vect v_new;
    v_new.x = x_new;
    v_new.y = y_new;
    v_new.z = z_new;
    return v_new;
}

struct vect vect_add(struct vect v1,struct vect v2){
    struct vect sum;
    sum.x = v1.x + v2.x;
    sum.y = v1.y + v2.y;
    sum.z = v1.z + v2.z;
    return sum;
}

struct vect vect_mult(struct vect v1,struct vect v2){
    struct vect mult;
    mult.x = v1.x * v2.x;
    mult.y = v1.y * v2.y;
    mult.z = v1.z * v2.z;
    return mult;
}

struct ray{
    struct vect origin;
    struct vect direction;
};

void init_ray(struct ray r){
    init_vect(r.origin);
    init_vect(r.direction);
    r.direction.x = 1;
};

struct camera {
    struct vect campos;
    struct vect camdir;
    struct vect camright;
    struct vect camdown;
};

void init_camera(struct camera c){
    init_vect(c.campos);
    init_vect(c.camdir);
    init_vect(c.camright);
    init_vect(c.camdown);
    c.camdir.z = 1;
};

void print_vector(struct vect v){
    printf("(%d,%d,%d)\n",v.x,v.y,v.z);
    fflush(stdout);
};

void print_ray(struct ray r){
    printf("ray origin:\n");
    print_vector(r.origin);
    printf("ray direction\n");
    print_vector(r.direction);
}
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
