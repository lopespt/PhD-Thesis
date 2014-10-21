#include <ComplexNetwork/ComplexNetwork.hpp>
#include <Utilities/Link.hpp>
#include <ComplexNetwork/NodeString.hpp>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QCoreApplication>
#include "ComplexNetworkToMatlab.hpp"

int main(int argc, char *argv[]){

    QCoreApplication app(argc,argv);

    if(strcmp(argv[1],"--help")==0){

    }

    ComplexNetwork<NodeString, Link> cn;
    //cn.load();

    QCommandLineParser parser;
    parser.addPositionalArgument("Input File","Complex Network Input File", "Input_File");
    parser.addPositionalArgument("Output File","Matlab Output File", "Output_File");

    parser.addHelpOption();
    parser.process(app);

    QString input_file = parser.positionalArguments().at(0);
    QString output_file = parser.positionalArguments().at(1);

    ComplexNetworkToMatlab::convert(input_file, output_file);

    return 0;
}
