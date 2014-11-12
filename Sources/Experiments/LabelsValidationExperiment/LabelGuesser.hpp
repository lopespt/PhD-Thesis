#ifndef LABELGUESSER_HPP
#define LABELGUESSER_HPP

#include <FeatureExtractors/Region.hpp>
#include <Utilities/SupervisedImage.hpp>
#include <Utilities/FeaturesComplexNetwork.hpp>

class LabelGuesser
{
private:
    FeaturesComplexNetwork *cn;
    QHash<QString, node_id> index;
    void buildIndex();
public:
    LabelGuesser(FeaturesComplexNetwork *cn);
    bool Guess(SupervisedImage *img, int guessRegionAt);
};

#endif // LABELGUESSER_HPP
