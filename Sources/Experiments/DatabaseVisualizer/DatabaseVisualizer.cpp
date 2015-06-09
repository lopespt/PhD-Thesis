#include <Utilities/SunDatabaseReader.hpp>
#include <QApplication>

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addPositionalArgument("folder", "Sun database folder", "folder");
    parser.process(app);

    SunDatabaseReader r(parser.positionalArguments()[0]);
    DatabaseVisualizerWidget w(&r);
    w.setVisible(true);

    return app.exec();
}
