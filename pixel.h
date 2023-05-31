#ifndef PIXEL_H
#define PIXEL_H

#include <QColor>

class Pixel
{

private:
    int r;          // These are the color values RGBA a pixel has
    int g;
    int b;
    int a;

public:

    // Static
    static QColor toQColor(const Pixel&);
    static Pixel fromQColor(const QColor&);

    // Constructors
    Pixel();
    Pixel(int r, int g, int b, int a);
    Pixel(const Pixel &aPixel);

    // Getters
    int getR() const;
    int getG() const;
    int getB() const;
    int getA() const;

    // Setter
    void setPixel(int r, int g, int b, int a);

    // Operator Overload
    bool operator==(const Pixel &aPixel) const;
    bool operator!=(const Pixel &aPixel) const;

};

#endif // PIXEL_H
