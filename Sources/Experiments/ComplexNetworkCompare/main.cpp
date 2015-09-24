//
// Created by Guilherme Wachs on 06/08/15.
//

#include <stdio.h>
#include <Utilities/FeaturesComplexNetwork/FeaturesComplexNetwork.hpp>
#include <QCoreApplication>
#include <Utilities/ConfigParser.h>
#include <FeatureExtractors/HsvFeatureFactory.hpp>
#include <FeatureExtractors/AreaFeatureFactory.hpp>
#include <FeatureExtractors/OrientationFeatureFactory.hpp>
#include <FeatureExtractors/LabelFeatureFactory.hpp>

void configureParse(QCommandLineParser &p, QCoreApplication &app){
    p.addHelpOption();
    p.addPositionalArgument("cn1", "Complex Network 1", "cn1");
    p.addPositionalArgument("cn2", "Complex Network 2", "cn2");
    p.addOption(QCommandLineOption("h", "H Discretization","h",0));
    p.addOption(QCommandLineOption("s", "S Discretization","s",0));
    p.addOption(QCommandLineOption("v", "V Discretization","v",0));
    p.addOption(QCommandLineOption("f", "Y Discretization","f",0));
    p.addOption(QCommandLineOption("a", "Area Discretization","a",0));
    p.addOption(QCommandLineOption("o", "Orientation Discretization","a",0));
    p.addOption(QCommandLineOption("l", "Labels"));

    p.process(app);
    if(p.positionalArguments().size() < 2) {
        puts("See HELP");
        exit(0);
    }
}

QList<const FeatureFactoryAbstract*> getFactories(QCommandLineParser &p){
    QList<const FeatureFactoryAbstract*> lista;
    if(p.isSet("f")) {
        lista.append(new HsvFeatureFactory(p.value("H").toInt(),p.value("S").toInt(),p.value("v").toInt(),p.value("f").toInt()));
    }

    if(p.isSet("a")) {
        lista.append(new AreaFeatureFactory(p.value("a").toInt()));
    }
    if(p.isSet("o")) {
        lista.append(new OrientationFeatureFactory(p.value("o").toUInt()));
    }
    if(p.isSet("l")) {
        lista.append(new LabelFeatureFactory());
    }

    return lista;
}

void clearFactories(QList<const FeatureFactoryAbstract* > &f) {
    for (auto i : f) {
        delete i;
    }
}

int compareCn(const FeaturesComplexNetwork &cn1, const FeaturesComplexNetwork &cn2) {

    if(cn1.getNumNodes() != cn2.getNumNodes())
        return 1;

    if(cn1.getNumArcs() != cn2.getNumArcs())
        return 1;

    for(FeaturesComplexNetwork::ArcIt it(cn1); it != INVALID; ++it ){
        auto fromFeat = cn1.getNode( cn1.source(it) );
        auto toFeat = cn1.getNode( cn1.target(it) );
        auto type = cn1.getLinkArcValue(it);

        auto from = cn2.getNodeFromFeature(fromFeat);
        auto to = cn2.getNodeFromFeature(toFeat);

        FeaturesComplexNetwork::Arc it2 = cn2.getArc(from,to, type.getLinkType());

        if( cn2.getLinkArcValue(it2).getWeight() != cn1.getLinkArcValue(it).getWeight() ){
            return 1;
        }
        if( cn2.getLinkArcValue(it2).getTime() != cn1.getLinkArcValue(it).getTime() ){
            return 1;
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    QCommandLineParser p;
    configureParse(p,app);

    try{
        FeaturesComplexNetwork cn1;
        FeaturesComplexNetwork cn2;

        auto f  = getFactories(p);
        cn1.load(p.positionalArguments()[0].toStdString().c_str(), f);
        cn2.load(p.positionalArguments()[1].toStdString().c_str(), f);

        if(compareCn(cn1, cn2) == 0){
            puts("Equals");
        }else{
            puts("Differents");
        }
        clearFactories(f);

    }catch (std::exception *e){
        puts(e->what());
    }
    return 0;
}


