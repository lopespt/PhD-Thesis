#ifndef LABELGUESSER_HPP
#define LABELGUESSER_HPP

#include <FeatureExtractors/Region.hpp>
#include <Utilities/SupervisedImage.hpp>
#include <Utilities/FeaturesComplexNetwork/FeaturesComplexNetwork.hpp>
#include <QString>

class LabelGuesser {
private:
    FeaturesComplexNetwork *cn;
    QSet<node_id> hubs;
    QHash<QString, node_id> index;

    void buildIndex();

public:
    LabelGuesser(FeaturesComplexNetwork *cn);

    bool Guess(SupervisedImage *img, int guessRegionAt);

    void removeHubs();
};

#endif // LABELGUESSER_HPP
