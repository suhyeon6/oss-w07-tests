#include <assert.h>
#include <stdio.h>
#include "filters.h"
int main(void)
{
    assert(brighten_channel(100, 40) == 140);
    assert(brighten_channel(240, 40) == 255);
    assert(brighten_channel(10, -40) == 0);
    unsigned char rgb[] = {90, 30, 0, 255, 255, 255};
    grayscale(rgb, sizeof rgb);
    assert(rgb[0] == 40 && rgb[1] == 40 && rgb[2] == 40);
    assert(rgb[3] == 255 && rgb[4] == 255 && rgb[5] == 255);
    puts("PASS filter contracts");
    return 0;
}
