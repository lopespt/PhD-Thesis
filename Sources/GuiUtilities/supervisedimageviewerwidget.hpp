#ifndef SUPERVISEDIMAGEVIEWERWIDGET_HPP
#define SUPERVISEDIMAGEVIEWERWIDGET_HPP

#include <QLabel>
#include <QObject>
#include <Utilities/SupervisedImage.hpp>

class SupervisedImageViewerWidget: public QLabel
{
    Q_OBJECT
private:
    SupervisedImage* m_supervised_image;
    const bool m_showSupervision;
    QPixmap m_original_pixmap;
public:
    SupervisedImageViewerWidget(QWidget *parent = 0);
    void setSupervisedImage(const SupervisedImage* image);
    QSize sizeHint() const;
    void paintEvent(QPaintEvent *);
    ~SupervisedImageViewerWidget();

signals:

public slots:

};

#endif // SUPERVISEDIMAGEVIEWERWIDGET_HPP
