#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include "Image.hpp"

Image::~Image() {
    
}

Image::Image(string name, int H, int W, uint8_t r, uint8_t g, uint8_t b) {
    fileName = name;
    height = H, width = W;
    clear(r,g,b);
}

void Image::SetPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b) {
    if(0<=x && x<width && 0<=y && y<height)
        img[x][y] = {r,g,b};
}

void Image::clear(uint8_t red, uint8_t green, uint8_t blue) {
    img.clear();
    pix unit = {red, green, blue};
    img.resize(height, vector<pix>(width, unit));
}

void Image::Generate() {

    int padding = 0;
    if(width%4) padding = 4 - (width%4);
    int r_width = width + padding;
    int fileSize = r_width*height*3 + 54;

    vector<uint8_t> fileHeader(14,0);
    vector<uint8_t> infoHeader(40,0);

    fileHeader[0] = 'B', fileHeader[1] = 'M';
    for(int i=0; i<4; ++i) fileHeader[i+2] = (uint8_t)(fileSize >> (i*8));
    fileHeader[10] = (uint8_t)54;

    infoHeader[0] = 40;
    for(int i=0; i<4; ++i) infoHeader[i+4] = (uint8_t)(width >> (i*8));
    for(int i=0; i<4; ++i) infoHeader[i+8] = (uint8_t)(height >> (i*8));
    infoHeader[12] = (uint8_t)1;
    infoHeader[14] = (uint8_t)24;

    ofstream ofs(fileName.c_str(), ios::binary | ios::out);
    for(int i=0; i<14; ++i) ofs << fileHeader[i];
    for(int i=0; i<40; ++i) ofs << infoHeader[i];
    for(int i=0; i<height; ++i) {
        for(int j=0; j<width; ++j) {
            ofs << img[i][j].b << img[i][j].g << img[i][j].r;
        }
        for(int j=0; j<padding; ++j) ofs << (uint8_t)0;
    }

    ofs.close();
    cout << "[+] Image Generated\n";

}