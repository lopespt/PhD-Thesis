//
// Created by Guilherme Wachs on 13/08/15.
//

#include "MCLClustering.hpp"
#include <QProcess>
#include <QStringList>
#include <FeatureExtractors/LabelFeature.hpp>
#include <qtextstream.h>

float MCLClustering::execute() {

    QProcess proc;
    //proc.setArguments(QStringList() << "-" << "--abc" << "-o -");

    proc.start("/bin/bash");
    proc.waitForStarted();

    //proc.write("mcl - -I 4 --abc -te 4 -dump-interval all -o -\n");
    proc.write("mcl -  --abc -te 4 -dump-interval all -o -\n");

    char buff[2000];
    typedef QPair<FeaturesComplexNetwork::Node, float> Pt;

    QList<Pt> degrees;
    for(FeaturesComplexNetwork::NodeIt it(cn); it != INVALID; ++it){
        degrees.append(Pt(it, cn.getOutputWeightedDegree(it)));
    }

    qSort(degrees.begin(),degrees.end(), [](const Pt& a, const Pt& b){
        return a.second < b.second;
    });

    for(int i=0;i<cn.getNumNodes() * 0.2;i++){
    //    cn.erase(degrees[i].first);
    }

    for(FeaturesComplexNetwork::ArcIt it(cn); it != INVALID; ++it ){
        FeatureAbstractPtr n1 = cn.getNode(cn.source(it));
        FeatureAbstractPtr n2 = cn.getNode(cn.target(it));
        if(n1->getType() == 0 && n2->getType()==0) {
            sprintf(buff, "%d %d %f\n", cn.id(cn.source(it)) , cn.id(cn.target(it)), weights[it]);
            proc.write(buff);
        }
    }


    proc.closeWriteChannel();
    proc.waitForReadyRead();
    proc.waitForFinished();

    int i;
    clusters.clear();
    while(proc.canReadLine()){
        QTextStream stream(proc.readLine());

        QList<FeaturesComplexNetwork::Node> oneCluster;
        while(!stream.atEnd()){
            stream >> i;
            if(!stream.atEnd()) {
                FeaturesComplexNetwork::Node node = cn.nodeFromId(i);
                oneCluster << node;
                clusterNum[node] = clusters.size();
            }
        }
        clusters.append(oneCluster);
    }

    fprintf(stderr, "%s\n", proc.readAllStandardError().constData());

    return 0;
}


int MCLClustering::getClusterNum(FeaturesComplexNetwork::Node n) {
    return clusterNum[n];
}

QList<FeaturesComplexNetwork::Node> MCLClustering::getClusterNodes(int clusterNum) {
    return clusters[clusterNum];
}

int MCLClustering::getTotalClusters() {
    return clusters.size();
}

const FeaturesComplexNetwork::NodeMap <int> & MCLClustering::getClustersMap() {
    return clusterNum;
}
