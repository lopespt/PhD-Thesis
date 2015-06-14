#include <QCoreApplication>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include "SUNRandomFolderGenerator.hpp"

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    QCommandLineParser parser;
    parser.addPositionalArgument("input", "SUN Database folder", "input folder");
    parser.addPositionalArgument("output", "New random SUN database folder", "output folder");
    parser.addPositionalArgument("number", "Number of images in new random SUN database", "number");
    parser.addHelpOption();

    parser.process(app);


    SUNRandomFolderGenerator gen(parser.positionalArguments()[0], parser.positionalArguments()[1],
                                 parser.positionalArguments()[2].toInt());
    gen.run();


    return 0;
}
