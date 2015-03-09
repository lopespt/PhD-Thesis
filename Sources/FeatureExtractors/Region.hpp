#ifndef REGION__H
#define REGION__H


#include <QPolygon>
#include <QString>
#include <opencv/cv.h>
#include <Utilities/SupervisedImage.hpp>
#include <FeatureExtractors/QImageCV.hpp>

class QRect;

class SupervisedImage;
class Region{

    private:
        SupervisedImage *supervisedImage;
        const QImageCV *image;
        QPolygon boundary;
        QString label;
        QString path;
        mutable cv::Mat cvmask;

    public:
        Region(){}
        Region(const QImageCV* image, cv::Mat mask);
        Region(const QImageCV* image,  QPolygon boundary);
        Region(SupervisedImage* supervisedImage,const QImageCV *image, QPolygon boundary, QString label);
        void show_region();
        ~Region();
        QRect getBoundaryRect() const;
        QPolygon getBoundary() const;
        QRgb getPixel(int x, int y, bool *insideRegion=NULL) const;
        QRgb getPixelRelative(int x, int y, bool *insideRegion=NULL) const;
        QString getLabel() const;
        const SupervisedImage* getSupervisedImage() const;

        void setImage(QImageCV* img);
        const QImageCV* getImage() const;

        /**
         * Returns an opencv InputArray representing the region of interest in
         * the original image. The non-zeroed cells are RoI cells.
         */
        cv::Mat getMask() const ;
        

};

#endif
