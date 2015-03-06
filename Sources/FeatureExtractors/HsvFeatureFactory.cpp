#include "HsvFeatureFactory.hpp"
#include "Region.hpp"
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "FeatureAbstract.hpp"
#include "HsvFeature.hpp"
int counter = 0;
unsigned long sumFast = 0;
unsigned long sumNormal = 0;
HsvFeatureFactory::HsvFeatureFactory(int h, int s, int v, int disc):FeatureFactoryAbstract(3),hd(h),sd(s),vd(v), disc(disc)
{
    /**
     * @brief assert that a uniform distribution will be truncated to upper value
     */
    assert( (int)(1.0/(h*s*v)*(disc-1)+0.5)>0 );
}

vector<int> HsvFeatureFactory::extractHSVFast(cv::Mat image, cv::Mat mask) const{
    vector<int> ret(hd*sd*vd, 0);
    assert(image.rows == mask.rows);
    assert(image.cols == mask.cols);
    assert(image.isContinuous() && mask.isContinuous());

    int h,s,v;
    int total=0;
    int shift;
    for(int i=0; i < image.rows; i++){
        for(int j=0; j < image.cols; j++){
            if( mask.data[i*mask.cols + j] > 0 ){
                shift = i*image.cols*3 + j*3;
                h = MIN(image.data[shift] /180.*(hd-1)+0.5, (hd-1)) ;
                s = MIN(image.data[shift + 1] /256.*(sd-1)+0.5, (hd-1)) ;
                v = MIN(image.data[shift + 2] /256.*(vd-1)+0.5, (hd-1)) ;
                ret[h*vd*sd+s*vd+v]++;
                total++;
            }
        }
    }
    for(unsigned int i=0;i<ret.size();i++){
        ret[i] = MIN(ret[i]*1./total*(disc-1)+0.5, (disc-1));
    }
    return ret;
}

vector<int> HsvFeatureFactory::extractHSV(cv::Mat image, cv::Mat mask) const{

    vector<int> ret(hd*sd*vd, 0);
    cv::cvtColor(image, image, CV_BGR2HSV);

    assert(image.rows == mask.rows);
    assert(image.cols == mask.cols);

    int h,s,v;
    int total=0;
    for(int i=0; i < image.rows; i++){
        for(int j=0; j < image.cols; j++){
            if( mask.at<uchar>(i,j) > 0 ){
                cv::Vec3b& c = image.at<cv::Vec3b>(i,j);
                h = MIN(c[0]/180.*(hd-1)+0.5, (hd-1)) ;
                s = MIN(c[1]/256.*(sd-1)+0.5, (sd-1));
                v = MIN(c[2]/256.*(vd-1)+0.5, (vd-1));
                ret[h*vd*sd+s*vd+v]++;
                total++;
            }
        }
    }
    //Normalize and discretize
    for(unsigned int i=0;i<ret.size();i++){
        ret[i] = ret[i]*1.0/total*(disc - 1)+0.5;
    }
    printf("\n");

    return ret;
}

FeatureAbstractPtr HsvFeatureFactory::CreateFromStream(istream &stream) const{
    int type_s;
    stream >> type_s;
    vector<int> ret(hd*sd*vd, 0);
    for(int i=0;i< hd*sd*vd; i++){
        stream >> ret[i];
    }
    return FeatureAbstractPtr(new HsvFeature(ret));
}

FeatureAbstractPtr HsvFeatureFactory::CreateFromRegion(const Region *r) const {
    FeatureAbstractPtr hsvFeature(new HsvFeature(extractHSVFast(r->getSupervisedImage()->getCvHsvImage(),r->getMask())));
    return hsvFeature;
}

HsvFeatureFactory::~HsvFeatureFactory()
{

}

