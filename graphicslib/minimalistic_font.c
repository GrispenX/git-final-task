#include "minimalistic_font.h"

#define O {0,0,0,0}
#define I {255,255,255,255}


frameBuffer_t font[255] = {
    ['0'] = (frameBuffer_t){
        .buffer = (RGBAcolor_t[]){I, I, I,
                                  I, O, I,
                                  I, O, I,
                                  I, O, I,
                                  I, I, I},
        .width = 3,
        .height = 5
    },
    ['1'] = (frameBuffer_t){
        .buffer = (RGBAcolor_t[]){I, I, O,
                                  O, I, O,
                                  O, I, O,
                                  O, I, O,
                                  I, I, I},
        .width = 3,
        .height = 5
    },
    ['2'] = (frameBuffer_t){
        .buffer = (RGBAcolor_t[]){I, I, I,
                                  O, O, I,
                                  I, I, I,
                                  I, O, O,
                                  I, I, I},
        .width = 3,
        .height = 5
    },
    ['3'] = (frameBuffer_t){
        .buffer = (RGBAcolor_t[]){I, I, I,
                                  O, O, I,
                                  I, I, I,
                                  O, O, I,
                                  I, I, I},
        .width = 3,
        .height = 5
    },
    ['4'] = (frameBuffer_t){
        .buffer = (RGBAcolor_t[]){I, O, I,
                                  I, O, I,
                                  I, I, I,
                                  O, O, I,
                                  O, O, I},
        .width = 3,
        .height = 5
    },
    ['5'] = (frameBuffer_t){
        .buffer = (RGBAcolor_t[]){I, I, I,
                                  I, O, O,
                                  I, I, I,
                                  O, O, I,
                                  I, I, I},
        .width = 3,
        .height = 5
    },
    ['6'] = (frameBuffer_t){
        .buffer = (RGBAcolor_t[]){I, I, I,
                                  I, O, O,
                                  I, I, I,
                                  I, O, I,
                                  I, I, I},
        .width = 3,
        .height = 5
    },
    ['7'] = (frameBuffer_t){
        .buffer = (RGBAcolor_t[]){I, I, I,
                                  O, O, I,
                                  O, I, O,
                                  O, I, O,
                                  O, I, O},
        .width = 3,
        .height = 5
    },
    ['8'] = (frameBuffer_t){
        .buffer = (RGBAcolor_t[]){I, I, I,
                                  I, O, I,
                                  I, I, I,
                                  I, O, I,
                                  I, I, I},
        .width = 3,
        .height = 5
    },
    ['9'] = (frameBuffer_t){
        .buffer = (RGBAcolor_t[]){I, I, I,
                                  I, O, I,
                                  I, I, I,
                                  O, O, I,
                                  I, I, I},
        .width = 3,
        .height = 5
    },
    [':'] = (frameBuffer_t){
        .buffer = (RGBAcolor_t[]){O,
                                  I,
                                  O,
                                  I,
                                  O},
        .width = 1,
        .height = 5
    },
};

static font_t minimalisticFontInternal = {
    .fontFrameBuffers = font
};

const font_t *minimalisticFont = &minimalisticFontInternal;