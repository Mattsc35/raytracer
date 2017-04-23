#ifndef _LIGHT_H
#define _LIGHT_H

#include "color.h"

struct light {
    struct vect position;
    struct color color;
};

void init_light(struct light l){
    init_vect(l.position);
    l.color.red = 1;
    l.color.blue = 1;
    l.color.green = 1;
    l.color.special = 0;
};

#endif
