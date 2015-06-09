#ifndef OUTSIDESEGMENTATION_HPP
#define OUTSIDESEGMENTATION_HPP

#include <QList>
#include <Segmentation/SegmentedImage.hpp>

class QString;

class OutsideSegmentation {
private:
    const QString &path;
    //SegmentedImage seg;
public:
    OutsideSegmentation(const QString &path);

    ~OutsideSegmentation();
};

#endif // OUTSIDESEGMENTATION_HPP
