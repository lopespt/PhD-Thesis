#ifndef REGION__H
#define REGION__H


#include <QImage>
#include <QPolygon>
#include <QString>

class QRect;
namespace cv{
    class Mat;
}

class Region{

    private:
        QImage *image;
        QPolygon boundary;
        QString label;
        //QLabel *l=NULL;

    public:
        Region(QImage *image, QPolygon boundary, QString label);
        void show_region();
        ~Region();
        QRect getBoundaryRect() const;
        QPolygon getBoundary() const;
        QRgb getPixel(int x, int y, bool *insideRegion=NULL) const;
        QRgb getPixelRelative(int x, int y, bool *insideRegion=NULL) const;
        QString getLabel() const;

        /**
         * Returns an opencv InputArray representing the region of interest in
         * the original image. The non-zeroed cells are RoI cells.
         */
        cv::Mat getMask() const;
        cv::Mat getCvImage() const;

        

};

#endif
