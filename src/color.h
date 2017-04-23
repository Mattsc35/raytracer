#ifndef _COLOR_H
#define _COLOR_H

struct color{
    double red;
    double green;
    double blue;
    double special;
};

void init_color(struct color c){
    c.red = 0.5;
    c.green = 0.5;
    c.blue = 0.5;
};


#endif
