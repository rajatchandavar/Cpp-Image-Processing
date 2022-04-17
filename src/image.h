#ifndef IMAGE_H
#define IMAGE_H

#include <cstdint>
#define STEG_HEADER_SIZE sizeof(uint32_t) * 8
#define BYTE_BOUND(value) value < 0 ? 0 : (value > 255 ? 255 : value);

#include <iostream>
#include "stb_image.h"
#include "stb_image_write.h"
#include <string>

enum image_type{
    png, jpg, bmp, tga
};


class image{
    public:
    uint8_t* data = NULL; //Picture data
    size_t size = 0; //size of data
    int w, h;
    int channels; //colour values per pixel RGB - 3

    image(const char* filename);
    image(int w, int h, int channels);//Blank image
    image(const image& img); //image copy constructor
    ~image();

    bool read(const char* filename);//function to read in from file
    bool write(const char* filename);

    image_type getfiletype(const char* filename);

    void grayscale_avg();

    void colormask(float r, float g, float b);

    void diffmap(image& img);

    void std_convolve_clamp_to_0(uint8_t channel, uint32_t ker_w, uint32_t ker_h, double* ker, uint32_t cr, uint32_t cc);
    

};

#endif