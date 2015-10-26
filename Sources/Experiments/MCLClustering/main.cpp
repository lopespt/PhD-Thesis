//
// Created by Guilherme Wachs on 04/10/15.
//

#include <qcoreapplication.h>
#include <Utilities/ConfigParser.h>
#include <Utilities/FeaturesComplexNetwork/FeaturesComplexNetwork.hpp>
#include <Utilities/MCLClustering.hpp>
#include <Utilities/Utils.hpp>

int main(int argc, char *argv[]) {

    QCoreApplication app(argc, argv);
    ConfigParser p(app);

    QString input = p.getCnInput();

    FeaturesComplexNetwork cn;
    cn.load(input.toStdString().c_str(), p.getFactories());

    FeaturesComplexNetwork::ArcMap<double> weights(cn);
    GraphUtilities::getWeights(cn, weights);

    GraphUtilities::outputAbcFormat(cn, weights);

    return 0;
}
