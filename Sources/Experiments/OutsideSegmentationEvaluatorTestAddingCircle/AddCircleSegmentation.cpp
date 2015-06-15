//
// Created by Guilherme Wachs on 08/06/15.
//

#include <Utilities/SupervisedImage.hpp>
#include <Segmentation/SegmentedImage.hpp>
#include "AddCircleSegmentation.hpp"

QList<SegmentedImage> AddCircleSegmentation::execute(const QImage &image, int nSegmentations) {
    QList<SegmentedImage> ret;

    for (int i = 1; i <= nSegmentations; ++i) {
        SupervisedImage temp = img;
        RegionMask nRegion(temp.getImage()->height(), temp.getImage()->width());
        circle(nRegion, temp.getImageCenter(), i * (image.width()/2.f/nSegmentations), cvScalarAll(255), -1);
        temp.addRegion("Noise", nRegion);
        ret << temp;
    }
    return ret;
}

AddCircleSegmentation::AddCircleSegmentation(SupervisedImage &img) : Segmenter(), img(img) {

}
