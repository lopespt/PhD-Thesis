int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    QCommandLineParser parser;
    parser.addPositionalArgument("folder", "SUN Database Folder", "folder");
    parser.addPositionalArgument("complex_network", "Complex Network File", "complex_network");
    parser.addHelpOption();

    QString folder, complex_network;
    parser.process(app);

    folder = parser.positionalArguments()[0];
    complex_network = parser.positionalArguments()[1];


    //LabelsValidationExperiment
    LabelsValidationExperiment experiment(folder, complex_network);


    experiment.run();

    return 0;
}

