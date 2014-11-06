
#include <Utilities/SunDatabaseReader.hpp>
#include <Utilities/SupervisedImage.hpp>
#include <FeatureExtractors/Region.hpp>
#include <opencv/cv.h>
#include <opencv/highgui.h>

int main(int argc, char* argv[]){

    SunDatabaseReader reader("/Users/wachs/Dropbox/Tese-Guilherme/Implementacoes/Doutorado/Sun1/");
    while(reader.hasNext()){
        SupervisedImage i = reader.readNext();
       cv::Mat m = i.getRegions()[0].getMask();
        //cv::Mat m = i.getRegions()[0].getCvImage();
        cv::imshow("img", m);
        cv::waitKey();
    }

    return 0;
}
