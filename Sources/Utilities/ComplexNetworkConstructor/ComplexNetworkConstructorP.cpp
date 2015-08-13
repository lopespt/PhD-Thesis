//
// Created by Guilherme Wachs on 12/08/15.
//

#include <Utilities/SupervisedImage.hpp>
#include <QLinkedList>
#include <Utilities/DatabaseReader/DatabaseReader.hpp>
#include <QThreadPool>
#include "ComplexNetworkConstructorP.hpp"
#include <QMutex>

unsigned int ComplexNetworkConstructorP::numP=1;
std::mutex ComplexNetworkConstructorP::mtx;

void ComplexNetworkConstructorP::build() {
    QThreadPool pool;
    pool.setMaxThreadCount(16);
    for(int i=0;i<16;i++) {
        pool.start(new ComplexNetworkConstructorP(cn, reader, extractors, coOcurrenceEquationPolicy, &this->index));
    }
    pool.waitForDone();
    fflush(stdout);
    cn.refreshCache();
}

void ComplexNetworkConstructorP::run() {
    while (reader.hasNext()) {
        //printf("Entrei\n");
        QList<int> regionsIds;
        QLinkedList<FeatureAbstractPtr> features;
        SupervisedImage img = reader.readNext();
        if (numP % 10 == 0)
            printf("Reading image(%u/%d): %s%s\n", numP, reader.getTotal(), img.getImagePath().size() > 60 ? "..." : "",
                   img.getImagePath().right(60).toStdString().c_str());

        for (int idx = 0; idx < img.getRegions().size(); idx++) {
            Region r = img.getRegions().at(idx);
            for (QList<const FeatureFactoryAbstract *>::iterator i = extractors.begin(); i != extractors.end(); i++) {
                features.append(move((*i)->CreateFromRegion(&r)));
                regionsIds.append(idx);
            }
        }
        //printf("Nodes: %ld , Edges: %ld\n", cn.getNumNodes(), cn.getNumEdges());
        mtx.lock();
        makeCoOccurrences(features, regionsIds);
        mtx.unlock();
        numP++;
        //printf("Sai\n");
    }
}

void ComplexNetworkConstructorP::makeCoOccurrences(QLinkedList<FeatureAbstractPtr> &features, QList<int> &regionsIds) {

    QLinkedList<FeaturesComplexNetwork::Node> nodes;


    //Cria nós ou pesquisa existentes
    for (auto &f: features) {
        FeaturesComplexNetwork::Node id;
        if (!cache->contains(f)) {
            FeatureAbstractPtr temp = f;
            id = cn.addNode(f);
            cache->insert(temp, id);
        } else {
            id = (*cache)[f];
        }
        nodes.append(id);
    }

    unsigned int i = 0, j = 0;
    for (QLinkedList<FeaturesComplexNetwork::Node>::const_iterator it1 = nodes.begin(); it1 != nodes.end(); it1++) {
        j = i + 1;
        for (QLinkedList<FeaturesComplexNetwork::Node>::const_iterator it2 = it1 + 1; it2 != nodes.end(); it2++) {
            reinforceLink(*it1, *it2, regionsIds[i] == regionsIds[j]);
            if (*it2 != *it1)
                reinforceLink(*it2, *it1, regionsIds[i] == regionsIds[j]);
            this->time++;
            j++;
        }
        i++;
    }
}
