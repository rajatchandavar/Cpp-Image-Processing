#include <algorithm>
#include <cstdint>
#include <cstring>
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "image.h"

image::image(const char* filename){
    if(read(filename)){
        std::cout << "Succesfully read " << filename << "\n";
        size = w * h * channels; //1 byte per channel
    }
    else{
        std::cout << "Failed to read" << filename << "\n";
    }
}

image::image(int _w, int _h, int _channels) : w(_w), h(_h), channels(_channels){
    size = w * h * channels;
    data = new uint8_t[size];
}

image::image(const image& img) : image(img.w, img.h, img.channels){
    memcpy(data, img.data, size);
}

image::~image(){
    stbi_image_free(data);
}

bool image::read(const char* filename){
    data = stbi_load(filename, &w, &h, &channels, 0);
    return data != NULL;
}

bool image::write(const char* filename){
    image_type type = getfiletype(filename);
    int success;
    switch (type){
        case png:
            success = stbi_write_png(filename, w, h, channels, data, w*channels);
            break;
        case jpg:
            success = stbi_write_jpg(filename, w, h, channels, data, 100);
            break;
        case bmp:
            success = stbi_write_bmp(filename, w, h, channels, data);
            break;
        case tga:
            success = stbi_write_bmp(filename, w, h, channels, data);
            break;
    }
    return success;
}

image_type image::getfiletype(const char* filename){
    const char* ext = strrchr(filename, '.');
    if (ext != nullptr){
        if(strcmp(ext, ".png") == 0){
            return png;
        }
        else if(strcmp(ext, ".jpg") == 0){
            return jpg;
        }
        else if(strcmp(ext, ".bmp") == 0){
            return bmp;
        }
        else if(strcmp(ext, ".tga") == 0){
            return tga;
        }
    }
    return png;
}

// Grayscale
void image::grayscale_avg(){
    // r+g+b/3 
    if (channels < 3){
        std::cout << "Image is probably Grayscale already\n";
    }
    else{
        for (int i = 0; i < size; i+=channels){
            int gray = (data[i] + data[i+1] + data[i+2])/3;
            memset(data+i, gray, 3);
        }
    }
}

//Modifying the Colour channels
void image::colormask(float r, float g, float b){
    if (channels < 3){
        std::cout << "Image is probably Grayscale already\n";
    }
    else{
        for (int i = 0; i < size; i += channels){
            data[i] *= r;
            data[i+1] *= g;
            data[i+2] *= b;
        }
    }
}

//diffmap - comparing 2 images

void image::diffmap(image& img){
    int compare_width = std::min(w, img.w);
    int compare_height = std::min(h, img.h);
    int compare_channels = std::min(channels, img.channels);

    for (uint32_t i = 0; i < compare_height; ++i){
        for (uint32_t j = 0; j < compare_width; ++j){
            for (uint8_t k = 0; k < compare_channels; ++k){
                data[(i*w + j)*channels + k] = BYTE_BOUND(abs(data[(i*w + j)*channels + k] - img.data[(i*img.w + j)*img.channels + k]));
            }
        }
    }
}






