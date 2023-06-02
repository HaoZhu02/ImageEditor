#ifndef CONVOLUTIONFILTER_H
#define CONVOLUTIONFILTER_H

#include <vector>
#include "../pixel.h"
#include "../imagefile.h"


void useConvolutionFilter(double filter[3][3], Image& anImage, std::vector<Pixel>& pixelBuffer);




#endif // CONVOLUTIONFILTER_H
