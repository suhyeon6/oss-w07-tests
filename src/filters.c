#include "filters.h"

unsigned char brighten_channel(unsigned char value, int delta)
{
    int result = value + delta;
    if (result > 255) result = 255;
    if (result < 0) result = 0;
    return (unsigned char)result;
}

void brighten(unsigned char *rgb, size_t count, int delta)
{
    for (size_t i = 0; i < count; ++i)
        rgb[i] = brighten_channel(rgb[i], delta);
}

void grayscale(unsigned char *rgb, size_t count)
{
    for (size_t i = 0; i < count; i += 3) {
        int gray = (rgb[i] + rgb[i+1] + rgb[i+2]) / 3;
        rgb[i] = rgb[i+1] = rgb[i+2] = (unsigned char)gray;
    }
}

void invert(unsigned char *rgb, size_t count)
{
    for (size_t i = 0; i < count; ++i)
        rgb[i] = 255 - rgb[i];
}
