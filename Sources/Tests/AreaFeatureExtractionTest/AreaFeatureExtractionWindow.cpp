#include "AreaFeatureExtractionWindow.hpp"

AreaFeatureExtractionWindow::AreaFeatureExtractionWindow(QString databasePath, QWidget *parent) :
    QWidget(parent), reader(databasePath)
{
    m_vbox = new QVBoxLayout();
    m_supervisedWidget = new SupervisedImageViewerWidget();
    m_vbox->addWidget(m_supervisedWidget);

    m_hbox = new QHBoxLayout();
    m_vbox->addLayout(m_hbox);

    m_previous_button = new QPushButton("Previous");
    m_next_button = new QPushButton("Next");
    m_hbox->addWidget(m_previous_button);
    m_hbox->addWidget(m_next_button);

    this->setLayout(m_vbox);
    QObject::connect(m_previous_button, SIGNAL(clicked()), this, SLOT(show_previous()));
    QObject::connect(m_next_button, SIGNAL(clicked()), this, SLOT(show_next()));

}

void AreaFeatureExtractionWindow::show_previous(){
    SupervisedImage s = reader.readPrevious();
    m_supervisedWidget->setSupervisedImage(s);
}

void AreaFeatureExtractionWindow::show_next(){
    SupervisedImage s = reader.readNext();
    m_supervisedWidget->setSupervisedImage(s);
}
