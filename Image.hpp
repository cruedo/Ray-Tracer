#ifndef IMAGE_H
#define IMAGE_H

struct pix {
    uint8_t r{0};
    uint8_t g{0};
    uint8_t b{0};

    bool operator!=(pix &C) {
        return (r!=C.r || g!=C.g || b!=C.b);
    }
};


class Image {

    int width;
    int height;
    std::string fileName;
    std::vector<std::vector<pix>> img;

public:
    Image(std::string name, int H = 200, int W = 200, uint8_t r=0, uint8_t g=0, uint8_t b=0);
    ~Image();
    void Generate();
    void clear(uint8_t red=255, uint8_t green=255, uint8_t blue=255);
    void SetPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b);
};


#endif