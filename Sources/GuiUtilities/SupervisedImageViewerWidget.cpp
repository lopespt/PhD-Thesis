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
    this->setMouseTracking(true);
    this->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
}

void SupervisedImageViewerWidget::setSupervisedImage(SupervisedImage image){
    if(!m_supervised_image){
        m_supervised_image = new SupervisedImage(image);
    }
    else
        *m_supervised_image = image;

    m_original_pixmap = QPixmap::fromImage(*m_supervised_image->getImage());
    QPixmap p;
    for(int i=0;i<m_supervised_image->getRegions().size();i++){
        QPainter t(&m_original_pixmap);
        QColor c = QColor::fromHsv(i*255/(m_supervised_image->getRegions().size()-1), 255, 255, 50);
        t.setBrush(c);
        t.drawConvexPolygon(m_supervised_image->getRegions().at(i).getBoundary());
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
    //Scale PixMap to the widget size.
    float pix_r = m_original_pixmap.width()*1.0/m_original_pixmap.height();
    float wid_r = paint_pix_width*1.0/paint_pix_height;
    if(pix_r > wid_r)
        p = m_original_pixmap.scaledToWidth(paint_pix_width);
    else
        p = m_original_pixmap.scaledToHeight(paint_pix_height);

    scale_factor = paint_pix_width*1./m_original_pixmap.width();
    pic_x = paint_pix_width/2-p.width()/2;
    pic_y = paint_pix_height/2-p.height()/2;
    painter.drawPixmap(pic_x,pic_y, p);

    QString text = painter.fontMetrics().elidedText(m_supervised_image->getImagePath(),Qt::ElideLeft,this->width());
    painter.drawText(0, paint_pix_height, this->width(), this->height()-paint_pix_height, Qt::AlignCenter, text);
    painter.drawText(pointer_x+pic_x+10, pointer_y+pic_y, this->width(), 30, Qt::AlignLeft, pointer_label);

}

void SupervisedImageViewerWidget::mouseMoveEvent(QMouseEvent *evt){
    if(!m_original_pixmap)
        return;
    evt->accept();
    pointer_x = evt->x()-pic_x;
    pointer_y = evt->y()-pic_y;
    int px = pointer_x*1.0/p.width()*m_original_pixmap.width();
    int py = pointer_y*1.0/p.height()*m_original_pixmap.height();
    fflush(stdout);
    foreach(Region reg, this->m_supervised_image->getRegions()){
        if(reg.getBoundary().containsPoint(QPoint(px,py), Qt::OddEvenFill)){
            pointer_label = QString("label: %1").arg(reg.getLabel());
        }
    }
    repaint();

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
