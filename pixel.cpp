#include "pixel.h"
#include "utilities.h"

// Default Constructor
Pixel::Pixel() : Pixel(0, 0, 0, 255)
{

}

// Parameter Constructor
Pixel::Pixel(int r, int g, int b, int a) : r(0), g(0), b(0), a(255)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

// Copy Constructor
Pixel::Pixel(const Pixel &aPixel)
{
    this->r = aPixel.getR();
    this->g = aPixel.getG();
    this->b = aPixel.getB();
    this->a = aPixel.getA();
}


// Getters

int Pixel::getR() const
{
    return this->r;
}

int Pixel::getG() const
{
    return this->g;
}

int Pixel::getB() const
{
    return this->b;
}

int Pixel::getA() const
{
    return this->a;
}


// Setter
void Pixel::setPixel(int r, int g, int b, int a)
{
    this->r = limit0_255(r);
    this->g = limit0_255(g);
    this->b = limit0_255(b);
    this->a = limit0_255(a);
}


// Static Colors

QColor Pixel::toQColor(const Pixel &oldColor)
{
    QColor newColor(oldColor.getR(), oldColor.getG(), oldColor.getB(), oldColor.getA());
    return newColor;
}

Pixel Pixel::fromQColor(const QColor &oldColor)
{
    int rColor;
    int gColor;
    int bColor;
    int aColor;

    oldColor.getRgb(&rColor, &gColor, &bColor, &aColor);

    return Pixel(rColor, gColor, bColor, aColor);
}
