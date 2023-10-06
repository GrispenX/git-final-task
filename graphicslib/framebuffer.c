#include <framebuffer.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static RGBAcolor_t blendColor(RGBAcolor_t color2, RGBAcolor_t color1)
{
    if(color1.a == 0) {return color2;}
    if(color2.a == 0) {return color1;}
    RGBAcolor_t colorOut;
    colorOut.a = color1.a + color2.a * (255 - color1.a);
    colorOut.r = (color1.r * color1.a + color2.r * color2.a * (255 - color1.a)) / colorOut.a;
    colorOut.g = (color1.g * color1.a + color2.g * color2.a * (255 - color1.a)) / colorOut.a;
    colorOut.b = (color1.b * color1.a + color2.b * color2.a * (255 - color1.a)) / colorOut.a;
    return colorOut;
}

void blendFrameBuffers(frameBuffer_t *buffer1, frameBuffer_t *buffer2, size_t offsetX, size_t offsetY)
{
    for(int h = 0; h < buffer2->height; h++)
    {
        for(int w = 0; w < buffer2->width; w++)
        {
            RGBAcolor_t color1 = buffer1->buffer[buffer1->width * (h + offsetY) + w + offsetX];
            RGBAcolor_t color2 = buffer2->buffer[buffer2->width * h + w];

            setPixel(buffer1, w + offsetX, h + offsetY, blendColor(color1, color2));
        }
    }
}

frameBuffer_t createFrameBuffer(size_t width, size_t height)
{
    frameBuffer_t buffer;
    buffer.buffer = calloc(sizeof(RGBAcolor_t) * width * height, 1);
    buffer.width = width;
    buffer.height = height;
    return buffer;
}

void deleteFrameBuffer(frameBuffer_t *buffer)
{
    free(buffer->buffer);
}

void setPixel(frameBuffer_t* buffer,size_t x, size_t y, RGBAcolor_t color)
{
    if(x >= buffer->width || y >= buffer->height) {return;}
    buffer->buffer[buffer->width * y + x] = color;
}

void fillFrameBuffer(frameBuffer_t* buffer,RGBAcolor_t color)
{
    for(int h = 0; h < buffer->height; h++)
    {
        for(int w = 0; w < buffer->width; w++)
        {
            setPixel(buffer, w, h, color);
        }
    }
}

RGBAcolor_t getPixel(frameBuffer_t* buffer, size_t x, size_t y)
{
    if(x >= buffer->width || y >= buffer->height) {return BLACK;}
    return buffer->buffer[buffer->width * y + x];
}

void printFrameBuffer(frameBuffer_t* buffer)
{
    printf("\033[%ldA", buffer->height);
    for (int h = 0; h < buffer->height; h++)
        {
            for(int w = 0; w < buffer->width; w++)
            {
                RGBAcolor_t getColor = getPixel(buffer, w, h);
                printf("\033[38;2;%d;%d;%dm██", getColor.r, getColor.g, getColor.b);
            }
            printf("\n");
        }
}


void renderCharacter(frameBuffer_t *buffer, char character, const font_t *font, size_t x, size_t y, RGBAcolor_t color)
{
    const size_t charWidth = font->fontFrameBuffers[character].width;
    const size_t charHeight = font->fontFrameBuffers[character].height;
    frameBuffer_t renderedChar = createFrameBuffer(charWidth, charHeight);
    for(int h = 0; h < charHeight; h++)
    {
        for(int w = 0; w < charWidth; w++)
        {
            RGBAcolor_t currentPixel = getPixel(&font->fontFrameBuffers[character], w, h);
            currentPixel.r &= color.r;
            currentPixel.g &= color.g;
            currentPixel.b &= color.b;
            currentPixel.a = color.a;
            setPixel(&renderedChar, w, h, currentPixel);
        }
    }
    blendFrameBuffers(buffer, &renderedChar, x, y);
    deleteFrameBuffer(&renderedChar);
}

void renderString(frameBuffer_t *buffer, const char *string, const font_t *font, size_t x, size_t y, RGBAcolor_t color)
{
    for(int i = 0; i < strlen(string); i++)
    {
       renderCharacter(buffer, string[i], font, x, y, color);
       x = x + font->fontFrameBuffers[string[i]].width + 1;
    }
}

void renderCharacterWithPattern(frameBuffer_t *buffer, char character, const font_t *font, size_t x, size_t y, frameBuffer_t *colorPattern, size_t patternOffsetX, size_t patternOffsetY)
{
    const size_t charWidth = font->fontFrameBuffers[character].width;
    const size_t charHeight = font->fontFrameBuffers[character].height;
    frameBuffer_t renderedChar = createFrameBuffer(charWidth, charHeight);
    for(int h = 0; h < charHeight; h++)
    {
        for(int w = 0; w < charWidth; w++)
        {
            RGBAcolor_t currentPixel = getPixel(&font->fontFrameBuffers[character], w, h);
            RGBAcolor_t currentPattern = getPixel(colorPattern, w + patternOffsetX, h + patternOffsetY);
            currentPixel.r &= currentPattern.r;
            currentPixel.g &= currentPattern.g;
            currentPixel.b &= currentPattern.b;
            currentPixel.a &= currentPattern.a;
            setPixel(&renderedChar, w, h, currentPixel);
        }
    }
    blendFrameBuffers(buffer, &renderedChar, x, y);
    deleteFrameBuffer(&renderedChar);
}

void renderStringWithPattern(frameBuffer_t *buffer, char *string, const font_t *font, size_t x, size_t y, frameBuffer_t *colorPattern, size_t patternOffsetX, size_t patternOffsetY)
{
    for(int i = 0; i < strlen(string); i++)
    {
        renderCharacterWithPattern(buffer, string[i], font, x, y, colorPattern, patternOffsetX, patternOffsetY);
        size_t charWidth = font->fontFrameBuffers[string[i]].width;
        patternOffsetX += charWidth + 1;
        x += charWidth + 1;
    }
}