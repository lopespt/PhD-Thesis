//
// Created by Guilherme Wachs on 08/06/15.
//

#ifndef PHDTHESIS_ADDCIRCLESEGMENTATION_H
#define PHDTHESIS_ADDCIRCLESEGMENTATION_H

#include <Segmentation/Segmenter.hpp>
#include <Utilities/SupervisedImage.hpp>

class AddCircleSegmentation : public Segmenter {
private:
    SupervisedImage &img;
public:
    AddCircleSegmentation(SupervisedImage &img);

    virtual QList<SegmentedImage> execute(const QImage &img, int nSegmentations);

};


#endif //PHDTHESIS_ADDCIRCLESEGMENTATION_H

