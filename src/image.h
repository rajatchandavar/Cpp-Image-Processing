#ifndef IMAGE_H
#define IMAGE_H

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
};

#endif