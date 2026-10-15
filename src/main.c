#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include "filters.h"
#include "image_io.h"
int main(int argc, char **argv)
{
    if (argc < 4 || argc > 5) {
        fprintf(stderr, "usage: %s input output.png gray|bright|invert [gain]\n", argv[0]);
        return 2;
    }
    const char *mode = argv[3];
    if (strcmp(mode,"gray") && strcmp(mode,"bright") && strcmp(mode,"invert")) {
        fputs("unknown filter\n", stderr); return 2;
    }
    if (argc == 5 && strcmp(mode,"bright")) {
        fputs("gain is supported only for bright\n", stderr); return 2;
    }
    int gain = DEFAULT_GAIN;
    if (argc == 5) {
        char *end; errno = 0;
        long parsed = strtol(argv[4], &end, 10);
        if (errno || end == argv[4] || *end || parsed < -255 || parsed > 255) {
            fputs("gain must be an integer in [-255, 255]\n", stderr); return 2;
        }
        gain = (int)parsed;
    }
    if (UCHAR_MAX != 255) { fputs("requires 8-bit unsigned char\n",stderr); return 2; }
    int width, height;
    unsigned char *rgb = load_rgb(argv[1], &width, &height);
    if (!rgb) { fputs("cannot load input image\n", stderr); return 2; }
    if (width <= 0 || height <= 0 || width > 4096 || height > 4096) {
        fputs("image too large\n", stderr); free_rgb(rgb); return 2;
    }
    size_t count = (size_t)width * height * 3;
    if (!strcmp(mode,"gray")) grayscale(rgb, count);
    else if (!strcmp(mode,"bright")) brighten(rgb, count, gain);
    else invert(rgb, count);
    int ok = save_rgb(argv[2], width, height, rgb);
    free_rgb(rgb);
    if (!ok) { fputs("cannot write output image\n", stderr); return 2; }
    printf("Created %s (%d x %d, %s)\n", argv[2], width, height, mode);
    return 0;
}
