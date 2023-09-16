#include <iostream>
#include <vector>
using namespace std;

struct Image {
    struct Header {
        char idLength;
        char colorMapType;
        char dataTypeCode;
        short colorMapOrigin;
        short colorMapLength;
        char colorMapDepth;
        short xOrigin;
        short yOrigin;
        short width;
        short height;
        char bitsPerPixel;
        char imageDescriptor;
    };
    struct Pixel {
        unsigned char B;
        unsigned char G;
        unsigned char R;
    };

    Header header;
    vector<Pixel> pixel_vec;
    void loadFile(const string& name);
    void writeFile(const string& name);

    Pixel multiply(const Pixel& P1, const Pixel& P2);
    Pixel screen(const Pixel& P1, const Pixel& P2);
    Pixel subtract(const Pixel& P1, const Pixel& P2);
    Pixel addition(const Pixel& P1, const Pixel& P2);
    Pixel overlay(const Pixel& P1, const Pixel& P2);

    Pixel combine(const Pixel& red, const Pixel& blue, const Pixel& green);
    void flip();
    Pixel onlyred(const Pixel& P1);
    Pixel onlygreen(const Pixel& P1);
    Pixel onlyblue(const Pixel& P1);
    Pixel addred(const Pixel& P1, const float& num);
    Pixel addgreen(const Pixel& P1, const float& num);
    Pixel addblue(const Pixel& P1, const float& num);
    Pixel scalered(const Pixel& P1, const float& scale);
    Pixel scalegreen(const Pixel& P1, const float& scale);
    Pixel scaleblue(const Pixel& P1, const float& scale);
};