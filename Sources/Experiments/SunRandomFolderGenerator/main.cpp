#include "SUNRandomFolderGenerator.hpp"
#include <QCoreApplication>
#include <QCommandLineOption>
#include <QCommandLineParser>

int main(int argc, char*argv[]){
    QCoreApplication app(argc,argv);

    QCommandLineOption iop("input folder", "SUN Database folder","input folder");
    QCommandLineOption oop("output folder", "New random SUN database folder","output folder");
    QCommandLineParser parser;
    parser.addOption(iop);
    parser.addOption(oop);
    parser.addHelpOption();

    parser.process(app);


    SUNRandomFolderGenerator gen(parser.positionalArguments()[0], parser.positionalArguments()[1]);
    gen.run();


    return 0;
}
