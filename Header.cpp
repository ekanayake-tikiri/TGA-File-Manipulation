#include <iostream>
#include <fstream>
#include "Header.h"
using namespace std;

void Image::loadFile(const string &name) {
    ifstream file(name, ios_base::binary);

    file.read((char*)&header.idLength, sizeof(header.idLength));
    file.read((char*)&header.colorMapType, sizeof(header.colorMapType));
    file.read((char*)&header.dataTypeCode, sizeof(header.dataTypeCode));
    file.read((char*)&header.colorMapOrigin, sizeof(header.colorMapOrigin));
    file.read((char*)&header.colorMapLength, sizeof(header.colorMapLength));
    file.read((char*)&header.colorMapDepth, sizeof(header.colorMapDepth));
    file.read((char*)&header.xOrigin, sizeof(header.xOrigin));
    file.read((char*)&header.yOrigin, sizeof(header.yOrigin));
    file.read((char*)&header.width, sizeof(header.width));
    file.read((char*)&header.height, sizeof(header.height));
    file.read((char*)&header.bitsPerPixel, sizeof(header.bitsPerPixel));
    file.read((char*)&header.imageDescriptor, sizeof(header.imageDescriptor));

    int pixel_num = header.width * header.height;
    for (int i = 0; i < pixel_num; i++) {
        Pixel pixel_temp;
        file.read((char*)&pixel_temp.B, sizeof(pixel_temp.B));
        file.read((char*)&pixel_temp.G, sizeof(pixel_temp.G));
        file.read((char*)&pixel_temp.R, sizeof(pixel_temp.R));
        pixel_vec.push_back(pixel_temp);
    }
}

void Image::writeFile(const string &name) {
    ofstream file(name, ios_base::binary);

    file.write((char*)&header.idLength, sizeof(header.idLength));
    file.write((char*)&header.colorMapType, sizeof(header.colorMapType));
    file.write((char*)&header.dataTypeCode, sizeof(header.dataTypeCode));
    file.write((char*)&header.colorMapOrigin, sizeof(header.colorMapOrigin));
    file.write((char*)&header.colorMapLength, sizeof(header.colorMapLength));
    file.write((char*)&header.colorMapDepth, sizeof(header.colorMapDepth));
    file.write((char*)&header.xOrigin, sizeof(header.xOrigin));
    file.write((char*)&header.yOrigin, sizeof(header.yOrigin));
    file.write((char*)&header.width, sizeof(header.width));
    file.write((char*)&header.height, sizeof(header.height));
    file.write((char*)&header.bitsPerPixel, sizeof(header.bitsPerPixel));
    file.write((char*)&header.imageDescriptor, sizeof(header.imageDescriptor));

    for (int i = 0; i < pixel_vec.size(); i++) {
        Pixel pixel_temp = pixel_vec[i];
        file.write((char*)&pixel_temp.B, sizeof(pixel_temp.B));
        file.write((char*)&pixel_temp.G, sizeof(pixel_temp.G));
        file.write((char*)&pixel_temp.R, sizeof(pixel_temp.R));
    }
}

Image::Pixel Image::multiply(const Pixel& P1, const Pixel& P2) {
    Pixel temp;
    float b_temp = ((P1.B * P2.B) / 255.0f) + 0.5f;
    float g_temp = ((P1.G * P2.G) / 255.0f) + 0.5f;
    float r_temp = ((P1.R * P2.R) / 255.0f) + 0.5f;

    temp.B = (unsigned char)b_temp;
    temp.G = (unsigned char)g_temp;
    temp.R = (unsigned char)r_temp;
    return temp;
}

Image::Pixel Image::screen(const Pixel& P1, const Pixel& P2) {
    Pixel temp;
    float NP1b = P1.B/255.0f;
    float NP1g = P1.G/255.0f;
    float NP1r = P1.R/255.0f;

    float NP2b = P2.B/255.0f;
    float NP2g = P2.G/255.0f;
    float NP2r = P2.R/255.0f;
    // needs to be 255.0f so that it's not integer math stored as a float

    float b_temp = ((1 - ((1 - NP1b) * (1 - NP2b))) * 255.0f) + 0.5f;
    float g_temp = ((1 - ((1 - NP1g) * (1 - NP2g))) * 255.0f) + 0.5f;
    float r_temp = ((1 - ((1 - NP1r) * (1 - NP2r))) * 255.0f) + 0.5f;

    temp.B = (unsigned char)(b_temp);
    temp.G = (unsigned char)(g_temp);
    temp.R = (unsigned char)(r_temp);
    return temp;
}

Image::Pixel Image::subtract(const Pixel& P1, const Pixel& P2) {
    Pixel temp;
    float b_temp = P1.B - P2.B;
    float g_temp = P1.G - P2.G;
    float r_temp = P1.R - P2.R;

    if (b_temp < 0) b_temp = 0;
    if (g_temp < 0) g_temp = 0;
    if (r_temp < 0) r_temp = 0;

    temp.B = (unsigned char)b_temp;
    temp.G = (unsigned char)g_temp;
    temp.R = (unsigned char)r_temp;
    return temp;
}

Image::Pixel Image::addition(const Pixel& P1, const Pixel& P2) {
    Pixel temp;
    float b_temp = P1.B + P2.B;
    float g_temp = P1.G + P2.G;
    float r_temp = P1.R + P2.R;

    if (b_temp > 255) b_temp = 255;
    if (g_temp > 255) g_temp = 255;
    if (r_temp > 255) r_temp = 255;

    temp.B = (unsigned char)b_temp;
    temp.G = (unsigned char)g_temp;
    temp.R = (unsigned char)r_temp;
    return temp;
}

Image::Pixel Image::overlay(const Pixel& P1, const Pixel& P2) {
    Pixel temp;
    float NP2b = P2.B/255.0f;
    float NP2g = P2.G/255.0f;
    float NP2r = P2.R/255.0f;
    float b_temp;
    float g_temp;
    float r_temp;

    if (NP2b <= 0.5f) { b_temp = 2 * NP2b * (P1.B/255.0f); }
    else { b_temp = 1 - (2 * (1 - (P1.B/255.0f)) * (1 - NP2b)); }

    if (NP2g <= 0.5f) { g_temp = 2 * NP2g * (P1.G/255.0f); }
    else { g_temp = 1 - (2 * (1 - (P1.G/255.0f)) * (1 - NP2g)); }

    if (NP2r <= 0.5f) { r_temp = 2 * NP2r * (P1.R/255.0f); }
    else { r_temp = 1 - (2 * (1 - (P1.R/255.0f)) * (1 - NP2r)); }

    temp.B = (unsigned char)((b_temp * 255.0f) + 0.5f);
    temp.G = (unsigned char)((g_temp * 255.0f) + 0.5f);
    temp.R = (unsigned char)((r_temp * 255.0f) + 0.5f);
    return temp;
}

Image::Pixel Image::onlyred(const Pixel& P1) {
    Pixel temp;
    temp.R = temp.B = temp.G = P1.R;
    return temp;
}

Image::Pixel Image::onlygreen(const Pixel& P1) {
    Pixel temp;
    temp.R = temp.B = temp.G = P1.G;
    return temp;
}

Image::Pixel Image::onlyblue(const Pixel& P1) {
    Pixel temp;
    temp.R = temp.B = temp.G = P1.B;
    return temp;
}

Image::Pixel Image::addred(const Pixel& P1, const float& num) {
    Pixel temp = P1;
    float r_temp = P1.R + num;
    if (r_temp > 255) r_temp = 255;
    if (r_temp < 0) r_temp = 0;
    temp.R = (unsigned char)r_temp;
    return temp;
}

Image::Pixel Image::addgreen(const Pixel& P1, const float& num) {
    Pixel temp = P1;
    float g_temp = P1.G + num;
    if (g_temp > 255) g_temp = 255;
    if (g_temp < 0) g_temp = 0;
    temp.G = (unsigned char)g_temp;
    return temp;
}

Image::Pixel Image::addblue(const Pixel& P1, const float& num) {
    Pixel temp = P1;
    float b_temp = P1.B + num;
    if (b_temp > 255) b_temp = 255;
    if (b_temp < 0) b_temp = 0;
    temp.B = (unsigned char)b_temp;
    return temp;
}

Image::Pixel Image::scalegreen(const Pixel& P1, const float& scale) {
    Pixel temp = P1;
    float temp_g = (P1.G/255.0f) * (scale);
    if (temp_g > 1) temp_g = 1;
    temp_g = (temp_g * 255.0f) + 0.5f;
    temp.G = (unsigned char)temp_g;
    return temp;
}

Image::Pixel Image::scaleblue(const Pixel& P1, const float& scale) {
    Pixel temp = P1;
    float temp_b = (P1.B/255.0f) * (scale);
    if (temp_b > 1) temp_b = 1;
    temp_b = (temp_b * 255.0f) + 0.5f;
    temp.B = (unsigned char)temp_b;
    return temp;
}

Image::Pixel Image::scalered(const Pixel& P1, const float& scale) {
    Pixel temp = P1;
    float temp_r = (P1.R/255.0f) * (scale);
    if (temp_r > 1) temp_r = 1;
    temp_r = (temp_r * 255.0f) + 0.5f;
    temp.R = (unsigned char)temp_r;
    return temp;
}

Image::Pixel Image::combine(const Pixel& red, const Pixel& blue, const Pixel& green) {
    Pixel temp;
    temp.R = red.R;
    temp.B = blue.B;
    temp.G = green.G;
    return temp;
}

void Image::flip() {
    vector<Pixel> temp = pixel_vec;
    for (int i = 0; i < temp.size(); i++) {
        temp[i] = pixel_vec[pixel_vec.size()- i - 1];
    }
    pixel_vec = temp;
}