//
// Created by Guilherme Wachs on 02/11/15.
//

#include <stdio.h>
#include <lemon/random.h>
#include <QCoreApplication>
#include <Utilities/ConfigParser.h>
#include <Utilities/FeaturesComplexNetwork/FeaturesComplexNetwork.hpp>
#include <FeatureExtractors/LabelFeature.hpp>
#include <QVector>

using namespace lemon;

typedef FeaturesComplexNetwork::Node Node;
typedef FeaturesComplexNetwork::NodeIt NodeIt;
typedef FeaturesComplexNetwork::ArcIt ArcIt;
int main(int argc, char *argv[]) {

    QCoreApplication app(argc, argv);
    ConfigParser parser(app);

    lemon::Random random(time(NULL));


    auto factories = parser.getFactories();
    FeaturesComplexNetwork cn;
    puts("Carregando");
    cn.load(parser.getCnInput().toStdString().c_str(), factories);
    puts("Carregado");

    puts("GerandoRedeAleatoria");
    FeaturesComplexNetwork cnRandom;
    int i=1;
    QVector<Node> cnRandomNodes(cn.getNumNodes());
    for( NodeIt it(cn); it != INVALID; ++it ){
        cnRandomNodes[i-1]=cnRandom.addNode(new LabelFeature(QString::number(i).toStdString().c_str()));
    }

    for(ArcIt arcs(cn); arcs != INVALID; ++arcs){
        Node from = cnRandomNodes[random.integer(cnRandomNodes.size())];
        Node to = cnRandomNodes[random.integer(cnRandomNodes.size())];
        cnRandom.addArc(from,to, cn.getLinkArcValue(arcs));
    }

    puts("Salvando Rede");
    cnRandom.save(parser.getCnOutput().toStdString().c_str());
    puts("Fim");

    return 0;
}