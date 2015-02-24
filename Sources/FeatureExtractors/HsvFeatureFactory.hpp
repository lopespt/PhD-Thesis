#ifndef HSVFEATUREFACTORY_HPP
#define HSVFEATUREFACTORY_HPP

#include "FeatureFactoryAbstract.hpp"
#include <opencv/cv.h>
#include <QString>
class HsvFeatureFactory: public FeatureFactoryAbstract
{
private:
    cv::Mat lastHsvImage;
    QString lastPath;
    int hd,sd,vd;
    /**frequency discretization**/
    int disc;
public:
    HsvFeatureFactory(int h, int s, int v, int disc);
    virtual FeatureAbstractPtr CreateFromRegion(const Region *r) const;
    virtual FeatureAbstractPtr CreateFromStream(istream &stream) const;
    vector<int> extractHSV(cv::Mat image, cv::Mat mask) const;
    vector<int> extractHSVFast(cv::Mat image, cv::Mat mask) const;
    ~HsvFeatureFactory();
};


#endif // HSVFEATUREFACTORY_HPP
