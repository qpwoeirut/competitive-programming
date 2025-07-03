#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "dep/stb_image.h"
#include "dep/stb_image_write.h"

#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

int width, height, channels;
unsigned char* input;
std::vector<unsigned char> output;

const std::string input_filename = "casinofiles/barcodes.png";
const std::string output_filename = "casinofiles/output.png";

void init_io() {
    std::string input_path = (std::filesystem::current_path() / input_filename).string();
    input = stbi_load(input_path.c_str(), &width, &height, &channels, 3);
    output.resize(width * height * 3);
}

void write_output() {
    std::string output_path = (std::filesystem::current_path() / output_filename).string();
    stbi_write_png(output_path.c_str(), width, height, 3, output.data(), width * 3);
    stbi_image_free(input);
}

void get_pixel(int r, int c, int rgb[3]) {
    int idx = (r * width + c) * 3;
    for (int i = 0; i < 3; ++i) rgb[i] = input[idx + i];
}

void set_pixel(int r, int c, const int rgb[3]) {
    int idx = (r * width + c) * 3;
    for (int i = 0; i < 3; ++i) output[idx + i] = rgb[i];
}

int main() {
    init_io();

    std::cout << "Loaded image " << width << "x" << height << "\n";

    for (int r = 0; r < height; ++r) {
        for (int c = 0; c < width; ++c) {
            int rgb[3];
            get_pixel(r, c, rgb);
            set_pixel(r, c, rgb);
        }
    }

    write_output();
    return 0;
}
