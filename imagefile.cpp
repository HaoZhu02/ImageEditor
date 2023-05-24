/*********************************
 * Author(s): Emmitt Carter
 * Date: 05-22-2023
*********************************/

#include "imagefile.h"

Image::Image(QString f) {
    this->file = f;
    find_file_type();
    find_file_size();
    find_px_area();
}

QString Image::get_file() {
    return this->file;
}

string Image::get_fileType() {
    return this->fileType;
}

int Image::get_pxLong() {
    return this->pxLong;
}

int Image::get_pxWide() {
    return this->pxWide;
}

float Image::get_bytes() {
    return this->bytes;
}

void Image::set_file(QString f) {
    this->file = f;
}

void Image::set_fileType(string s) {
    this->fileType = s;
}

void Image::set_pxLong(int l) {
    this->pxLong = l;
}

void Image::set_pxWide(int w) {
    this->pxWide = w;
}

void Image::set_bytes(float m) {
    this->bytes = m;
}

void Image::find_px_area() {
    String cvstr(this->file.toStdString());
    Mat m = imread(cvstr);
    this->pxLong = m.size[0];
    this->pxWide = m.size[1];
}

void Image::find_file_size() {
    QFileInfo f(this->file);
    this->bytes = f.size();
}

void Image::find_file_type() {
    QFileInfo f(this->file);
    QString type = f.suffix();
    this->fileType = type.toStdString();
}
