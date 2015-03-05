#include "ImageSegmentation.hpp"


ImageSegmentation::ImageSegmentation(const QImage &image, const QVector<QPolygon>& regions):
    image(image),
    regions(regions)
{

    
    
}

ImageSegmentation::~ImageSegmentation()
{

}

