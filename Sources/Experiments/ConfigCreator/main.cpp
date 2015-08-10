//
// Created by Guilherme Wachs on 10/08/15.
//


#include <QSettings>
#include <qapplication.h>


int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    int h[] = {5,10,15,20,25,30,35};
    int s[] = {3,6,9};
    int v[] = {3,6,9};
    int f[] = {4,8,16,32};

    for(int hi : h){
        for(int si : s){
            for(int vi : v) {
                for(int fi : f) {

                    QSettings s(QString("config%1_%2_%3_%4.ini").arg(hi).arg(si).arg(vi).arg(fi),QSettings::IniFormat);
                    s.setValue("kfold/load", 0);
                    s.setValue("kfold/save", 1);
                    s.setValue("kfold/file", "images_set.kfold");
                    s.setValue("kfold/train_percentage", 0.7);

                    s.setValue("region_chooser/load", 0);
                    s.setValue("region_chooser/save", 1);
                    s.setValue("region_chooser/file", "chosenRegions.txt");
                    s.setValue("FeaturesComplexNetwork/load", 0);
                    s.setValue("FeaturesComplexNetwork/file", "train.cn");


                    s.setValue("factories_enabled/labels", 1);
                    s.setValue("factories_enabled/hsv", 1);
                    s.setValue("factories_enabled/orientation", 0);
                    s.setValue("factories_enabled/area", 0);


                    s.setValue("factories/hsv/hue_discretization", hi);
                    s.setValue("factories/hsv/saturation_discretization", si);
                    s.setValue("factories/hsv/value_discretization", vi);
                    s.setValue("factories/hsv/frequency_discretization", fi);

                    s.setValue("factories/orientation/orientation_discretization", 4);

                    s.setValue("factories/area/area_discretization", 4);

                    s.setValue("constructor_general/constructor_enabled", 1);
                    s.setValue("constructor_general/coocurrence_equation", "add");
                    s.setValue("constructor_general/save", 1);


                    s.setValue("constructor/reinforcement/learningRate", 0.3);
                    s.setValue("constructor/reinforcement/lamda", 80);

                    s.setValue("label_guesser_experiment/execute", 1);
                    s.setValue("label_guesser_experiment/walk_length", 1);
                    s.setValue("label_guesser_experiment/method", "xor");


                    s.setValue("label_guesser_experiment/output_file", QString("guesses%1_%2_%3_%4.txt").arg(hi).arg(si).arg(vi).arg(fi));

                }
            }
        }
    }

    return 0;
}