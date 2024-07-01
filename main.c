#include <supervision.h>
#include <string.h>
#include <stdio.h>
#include "bitmap.h"

struct __sv_dma_buffer
{
    unsigned int source;
    unsigned int destination;
    unsigned char lenght; //*16
    unsigned char control;
};
#define SV_DMA_BUFFER (*(struct __sv_dma_buffer *)0x2008)

#define SV_BUS ((unsigned char*)0x8000)

static void init(void)
{
    SV_LCD.width = 160;
    SV_LCD.height = 160;
}

void main(void)
{
    init();
    while (1)
    {
        //top half of screen
        *SV_BUS = 0xFF;
        SV_DMA_BUFFER.source = (int)&bitmap;
        SV_DMA_BUFFER.destination = (int)SV_VIDEO;
        SV_DMA_BUFFER.lenght = 0xF0;
        SV_DMA_BUFFER.control = 0x80;

        //bottom half of screan
        *SV_BUS = 0xFF;
        SV_DMA_BUFFER.source = (int)&bitmap;
        SV_DMA_BUFFER.destination = (int)SV_VIDEO + 0xF00;
        SV_DMA_BUFFER.lenght = 0xF0;
        SV_DMA_BUFFER.control = 0x80;
    }
}
