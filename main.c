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
    unsigned int bufferOffset, screenOffset, lineCount;
    init();
    while (1)
    {   
        bufferOffset = 0;
        screenOffset = 0;
        lineCount = SV_LCD.height;
        while(lineCount--) {
            SV_DMA_BUFFER.control = 0x0;
            SV_DMA_BUFFER.source = (int)&bitmap + bufferOffset;
            SV_DMA_BUFFER.destination = (int)SV_VIDEO + screenOffset;
            SV_DMA_BUFFER.lenght = 0x3;
            SV_DMA_BUFFER.control = 0x80;
            bufferOffset += 0x28;
            screenOffset += 0x30;
        }
    }
}
