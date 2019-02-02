#include <stdint.h>
#include <iostream>
#include "base64.h"



#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main() {
    int width, height, bpp;

    uint8_t* rgb_image = stbi_load("test.png", &width, &height, &bpp, 3);

//    std::cout << rgb_image << std::endl;
  
    const std::string imageString = rgb_image.to_string();
    std::string imageBase64 = base64_encode(
            reinterpret_cast<const unsigned char*>(imageString.c_str()), 
            imageString.length());
    std::cout << "Encoded Image: " << imageBase64 << std::endl;

    stbi_image_free(rgb_image);


    return 0;
}

