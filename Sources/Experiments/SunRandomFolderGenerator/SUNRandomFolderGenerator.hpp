#ifndef SUNRANDOMFOLDERGENERATOR_HPP
#define SUNRANDOMFOLDERGENERATOR_HPP

#include <QString>
#include <QList>
class SupervisedImage;

class SUNRandomFolderGenerator
{
private:
    QString inputFolder, outputFolder;
    unsigned int num;
public:
    SUNRandomFolderGenerator(QString inputFolder, QString outputFolder, unsigned int num);
    void run();
    void copy(QString);
    QList<unsigned int> shuffledList(int n, int max);
};

#endif // SUNRANDOMFOLDERGENERATOR_HPP
