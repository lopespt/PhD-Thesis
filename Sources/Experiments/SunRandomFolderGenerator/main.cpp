int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    QCommandLineOption iop("input folder", "SUN Database folder", "input folder");
    QCommandLineOption oop("output folder", "New random SUN database folder", "output folder");
    QCommandLineOption nop("number", "Number of images in new random SUN database", "number");
    QCommandLineParser parser;
    parser.addOption(iop);
    parser.addOption(oop);
    parser.addOption(nop);
    parser.addHelpOption();

    parser.process(app);


    SUNRandomFolderGenerator gen(parser.positionalArguments()[0], parser.positionalArguments()[1],
                                 parser.positionalArguments()[2].toInt());
    gen.run();


    return 0;
}
