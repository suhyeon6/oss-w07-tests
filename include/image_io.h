#ifndef IMAGE_IO_H
#define IMAGE_IO_H
unsigned char *load_rgb(const char *path, int *width, int *height);
int save_rgb(const char *path, int width, int height, const unsigned char *rgb);
void free_rgb(unsigned char *rgb);
#endif
