#include "image_io.h"
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_JPEG
#define STBI_ONLY_PNG
#define STBI_MAX_DIMENSIONS 8192
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
unsigned char *load_rgb(const char *path, int *width, int *height)
{
    int channels;
    return stbi_load(path, width, height, &channels, 3);
}
int save_rgb(const char *path, int width, int height, const unsigned char *rgb)
{
    return stbi_write_png(path, width, height, 3, rgb, width * 3);
}
void free_rgb(unsigned char *rgb) { stbi_image_free(rgb); }
