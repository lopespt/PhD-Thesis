#ifndef SUPERVISEDIMAGEVIEWERWIDGET_HPP
#define SUPERVISEDIMAGEVIEWERWIDGET_HPP

#include <QLabel>
#include <QObject>
#include <Utilities/SupervisedImage.hpp>
#include <QMouseEvent>

class SupervisedImageViewerWidget: public QLabel
{
    Q_OBJECT
private:
    SupervisedImage* m_supervised_image;
    const bool m_showSupervision;
    QPixmap m_original_pixmap;
    QString pointer_label;
    int pointer_x;
    int pointer_y;
    int pic_x;
    int pic_y;
    float scale_factor;
    QPixmap p;
public:
    SupervisedImageViewerWidget(QWidget *parent = 0);
    void setSupervisedImage(SupervisedImage image);
    QSize sizeHint() const;
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    ~SupervisedImageViewerWidget();

signals:

public slots:

};

#endif // SUPERVISEDIMAGEVIEWERWIDGET_HPP
