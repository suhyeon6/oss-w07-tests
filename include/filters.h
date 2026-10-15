#ifndef FILTERS_H
#define FILTERS_H
#include <stddef.h>
#define DEFAULT_GAIN 60
unsigned char brighten_channel(unsigned char value, int delta);
void brighten(unsigned char *rgb, size_t count, int delta);
void grayscale(unsigned char *rgb, size_t count);
void invert(unsigned char *rgb, size_t count);
#endif
