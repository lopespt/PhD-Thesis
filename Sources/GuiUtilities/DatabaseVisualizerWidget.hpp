#ifndef DATABASEVISUALIZERWIDGET_HPP
#define DATABASEVISUALIZERWIDGET_HPP

#include <QWidget>

class QPushButton;
class SupervisedImageViewerWidget;
class DatabaseReader;

class DatabaseVisualizerWidget : public QWidget
{
    Q_OBJECT
private:
    QPushButton *btnPrevious, *btnNext;
    SupervisedImageViewerWidget *viewer;
    DatabaseReader *reader;
public:
    explicit DatabaseVisualizerWidget(DatabaseReader *reader, QWidget *parent = 0);

signals:
    void nextClicked();
    void previousClicked();

public slots:
    void goNext();
    void goPrevious();

};

#endif // DATABASEVISUALIZERWIDGET_HPP
