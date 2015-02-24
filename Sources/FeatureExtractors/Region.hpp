#ifndef REGION__H
#define REGION__H


#include <QImage>
#include <QPolygon>
#include <QString>
#include <opencv/cv.h>
#include <Utilities/SupervisedImage.hpp>

class QRect;

class SupervisedImage;
class Region{

    private:
        SupervisedImage *supervisedImage;
        QImage *image;
        QPolygon boundary;
        QString label;
        QString path;
        mutable cv::Mat cvmask;

    public:
        Region(SupervisedImage* supervisedImage, QImage *image, QPolygon boundary, QString label);
        void show_region();
        ~Region();
        QRect getBoundaryRect() const;
        QPolygon getBoundary() const;
        QRgb getPixel(int x, int y, bool *insideRegion=NULL) const;
        QRgb getPixelRelative(int x, int y, bool *insideRegion=NULL) const;
        QString getLabel() const;
        const SupervisedImage* getSupervisedImage() const;

        /**
         * Returns an opencv InputArray representing the region of interest in
         * the original image. The non-zeroed cells are RoI cells.
         */
        cv::Mat getMask() const ;
        

};

#endif
