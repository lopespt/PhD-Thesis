//
// Created by Guilherme Wachs on 13/08/15.
//

#include "Modularity.hpp"
#include <QProcess>
#include <QStringList>
#include <FeatureExtractors/LabelFeature.hpp>

float Modularity::execute() {

    QProcess proc;
    //proc.setArguments(QStringList() << "-" << "--abc" << "-o -");

    proc.start("/bin/bash");
    proc.waitForStarted();

    proc.write("mcl - -I 4 --abc -te 4 -dump-interval all -o -\n");

    char buff[2000];
    typedef QPair<FeaturesComplexNetwork::Node, float> Pt;

    QList<Pt> degrees;
    for(FeaturesComplexNetwork::NodeIt it(cn); it != INVALID; ++it){
        degrees.append(Pt(it, cn.getOutputDegree(it)));
    }

    qSort(degrees.begin(),degrees.end(), [](const Pt& a, const Pt& b){
        return a.second < b.second;
    });

    for(int i=0;i<cn.getNumNodes() * 0.2;i++){
        cn.erase(degrees[i].first);
    }

    for(FeaturesComplexNetwork::ArcIt it(cn); it != INVALID; ++it ){
        FeatureAbstractPtr n1 = cn.getNode(cn.source(it));
        FeatureAbstractPtr n2 = cn.getNode(cn.target(it));
        if(n1->getType() == 0 && n2->getType()==0) {
            QString str1(n1->asString(buff));
            QString str2(n2->asString(buff));

            str1.replace(" ","_");
            str2.replace(" ","_");

            sprintf(buff, "%s %s %f\n", str1.toStdString().c_str(), str2.toStdString().c_str(), weights[it]);
            printf("%s", buff);
            proc.write(buff);
        }
    }


    proc.closeWriteChannel();
    proc.waitForReadyRead();
    proc.waitForFinished();

    puts(proc.readAll().constData());
    fprintf(stderr, "%s\n", proc.readAllStandardError().constData());


    return 0;
}
