#include "DatabaseVisualizerWidget.hpp"

#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <GuiUtilities/SupervisedImageViewerWidget.hpp>
#include <Utilities/DatabaseReader.hpp>
#include <assert.h>
#include <QObject>

DatabaseVisualizerWidget::DatabaseVisualizerWidget(DatabaseReader* reader, QWidget *parent) :
    QWidget(parent), reader(reader)
{
    assert(reader!=NULL);
    QVBoxLayout *layout = new QVBoxLayout;
    this->setLayout(layout);


    this->btnPrevious = new QPushButton("Previous");
    this->btnNext = new QPushButton("Next");
    this->viewer = new SupervisedImageViewerWidget;

    layout->addWidget(this->viewer);

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    layout->addLayout(bottomLayout);

    bottomLayout->addWidget(btnPrevious);
    bottomLayout->addWidget(btnNext);

    resize(450,300);

    QObject::connect(btnPrevious, &QPushButton::clicked, this, &DatabaseVisualizerWidget::goPrevious);
    QObject::connect(btnNext, &QPushButton::clicked, this, &DatabaseVisualizerWidget::goNext);
}

void DatabaseVisualizerWidget::goNext(){
    if(reader->hasNext())
        this->viewer->setSupervisedImage(reader->readNext());
}

void DatabaseVisualizerWidget::goPrevious(){
    if(reader->hasPrevious())
        this->viewer->setSupervisedImage(reader->readPrevious());
}
