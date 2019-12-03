#include "includes/rtv1.h"

unsigned int calculate_light(unsigned int color, float light_intensity, float brilliance)
{
    unsigned int c[4];

    if (light_intensity < 0)
        light_intensity = 0;
    if (light_intensity > 1)
        light_intensity = 1;
    c[3] = color % 256;
    c[2] = (color >> 8) % 256;
    c[1] = (color >> 16) % 256;
    c[0] = (color >> 24) % 256;
    if (brilliance > 0)
    {
        brilliance = 1.0 - ((1.0 - brilliance) * 195);
        c[2] = c[2] + ((255 - c[2]) * brilliance);
        c[1] = c[1] + ((255 - c[1]) * brilliance);
        c[0] = c[0] + ((255 - c[0]) * brilliance);
    }
    else 
    {
        c[2] = c[2] * light_intensity;
        c[1] = c[1] * light_intensity;
        c[0] = c[0] * light_intensity;
    }
    return ((c[0] << 24) + (c[1] << 16) + (c[2] << 8) + c[3]);
}

