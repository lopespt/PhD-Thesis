#include <stdio.h>
#include <QCoreApplication>
#include <QApplication>
#include "ComplexNetwork.hpp"
#include "tests/ComplexNetworkTest.cpp"
#include "SunDatabaseReader.hpp"
#include <QFile>

int main(int argc, char **argv){

    //QCoreApplication a(argc, argv);
    QApplication a(argc, argv);

    SunDatabaseReader r("/Users/wachs/Dropbox/Tese-Guilherme/Implementacoes/Doutorado/SunDatabasePartial/");
    SupervisedImage* s=r.readNext();
    s=r.readNext();
    //while((s=r.readNext())!=NULL){
    //s->show_image();
    //foreach(Region *r, s->getRegions()){
    Region *rr = s->getRegions().at(5);
        rr->show_region();
        bool t;
        int w = rr->getBoundaryRect().width();
        int h = rr->getBoundaryRect().height();
        int area = 0;
        printf("boundary: %d x %d\n", h,w);
        for(int i=0;i < w; i++){
            for(int j=0;j < h; j++){
                rr->getPixelRelative(i,j, &t);
                printf("%d, %d: ok? %d\n", i,j,t);
                if(t){
                    area++;
                }
            }
        }
        printf("%s: %d pixels^2\n", rr->getLabel().toStdString().c_str()  ,area);
        fflush(stdout);
    //}
    //}
    //initTest( 50000 , 50000000 );

    return a.exec();
}
