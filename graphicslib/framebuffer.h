#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <stdint.h>
#include <stddef.h>

#define RGBA(rv, gv, bv, av) \
    (RGBAcolor_t)            \
    {                        \
        .r = rv,             \
        .g = gv,             \
        .b = bv,             \
        .a = av              \
    }

#define BLACK RGBA(0, 0, 0, 255)
#define WHITE RGBA(255, 255, 255, 255)
#define EMPTY RGBA(0, 0, 0, 0)
#define RED RGBA(255, 0, 0, 255)
#define GREEN RGBA(0, 255, 0, 255)
#define BLUE RGBA(0, 0, 255, 255)

typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} RGBAcolor_t;

typedef struct
{
    RGBAcolor_t *buffer;
    size_t width;
    size_t height;
} frameBuffer_t;

typedef struct 
{
    frameBuffer_t *fontFrameBuffers;
} font_t;



frameBuffer_t createFrameBuffer(size_t width, size_t height);
void deleteFrameBuffer(frameBuffer_t *buffer);

void setPixel(frameBuffer_t *buffer, size_t x, size_t y, RGBAcolor_t color);
void fillFrameBuffer(frameBuffer_t *buffer, RGBAcolor_t color);
RGBAcolor_t getPixel(frameBuffer_t *buffer, size_t x, size_t y);

void printFrameBuffer(frameBuffer_t *buffer);
void blendFrameBuffers(frameBuffer_t *buffer1, frameBuffer_t *buffer2, size_t offsetX, size_t offsetY);


void renderCharacter(frameBuffer_t *buffer, char character, const font_t *font, size_t x, size_t y, RGBAcolor_t color);
void renderString(frameBuffer_t *buffer, const char *string, const font_t *font, size_t x, size_t y, RGBAcolor_t color);

void renderCharacterWithPattern(frameBuffer_t *buffer, char character, const font_t *font, size_t x, size_t y, frameBuffer_t *colorPattern, size_t patternOffsetX, size_t patternOffsetY);
void renderStringWithPattern(frameBuffer_t *buffer, char *string, const font_t *font, size_t x, size_t y, frameBuffer_t *colorPattern, size_t patternOffsetX, size_t patternOffsetY);

#endif