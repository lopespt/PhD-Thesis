#ifndef SUPERVISEDIMAGEVIEWERWIDGET_HPP
#define SUPERVISEDIMAGEVIEWERWIDGET_HPP

#include <QLabel>
#include <Utilities/SupervisedImage.hpp>

class SupervisedImageViewerWidget : public QLabel
{
    Q_OBJECT
private:
    const SupervisedImage* m_supervised_image;
public:
    SupervisedImageViewerWidget(QWidget *parent = 0);
   // void setSupervisedImage(const SupervisedImage *image);

signals:

public slots:

};

#endif // SUPERVISEDIMAGEVIEWERWIDGET_HPP
