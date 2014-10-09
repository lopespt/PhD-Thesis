#include "SupervisedImageViewerWidget.hpp"
#include <QPixmap>
#include <QPainter>
#include <QColor>
#include <QColormap>
#include <QSizePolicy>
#include <QTransform>
#include <QPaintEvent>
#include <stdio.h>

SupervisedImageViewerWidget::SupervisedImageViewerWidget(QWidget *parent): QLabel(), m_supervised_image(NULL), m_showSupervision(true)
{
    this->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
}

void SupervisedImageViewerWidget::setSupervisedImage(const SupervisedImage* image){
    if(!m_supervised_image){
        m_supervised_image = new SupervisedImage(*image);
        printf("New\n");
    }
    else
        *m_supervised_image = *image;

    m_original_pixmap = QPixmap::fromImage(*image->getImage());
    QPixmap p;
    for(int i=0;i<image->getRegions().size();i++){
        QPainter t(&m_original_pixmap);
        QColor c = QColor::fromHsv(i*255/(image->getRegions().size()-1), 255, 255, 50);
        t.setBrush(c);
        t.drawConvexPolygon(image->getRegions().at(i)->getBoundary());
    }
    update();
}

void SupervisedImageViewerWidget::paintEvent(QPaintEvent *event){
    event->accept();
    if(m_original_pixmap.isNull())
        return;

    int paint_pix_width = this->width();
    int paint_pix_height = this->height()-20;

    QPainter painter(this);
    QPixmap p;
    //Scale PixMap to the widget size.
    float pix_r = m_original_pixmap.width()*1.0/m_original_pixmap.height();
    float wid_r = paint_pix_width*1.0/paint_pix_height;
    if(pix_r > wid_r)
        p = m_original_pixmap.scaledToWidth(paint_pix_width);
    else
        p = m_original_pixmap.scaledToHeight(paint_pix_height);
    painter.drawPixmap(paint_pix_width/2-p.width()/2,paint_pix_height/2-p.height()/2,p);

    QString text = painter.fontMetrics().elidedText(m_supervised_image->getImagePath(),Qt::ElideLeft,this->width());
    painter.drawText(0, paint_pix_height, this->width(), this->height()-paint_pix_height, Qt::AlignCenter, text);
}


QSize SupervisedImageViewerWidget::sizeHint() const{
    if(m_original_pixmap.isNull())
        return QSize(100,166);
    return m_original_pixmap.size();
}

SupervisedImageViewerWidget::~SupervisedImageViewerWidget(){
    if(m_supervised_image){
        //delete m_supervised_image;
    }
}
