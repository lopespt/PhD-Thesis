#ifndef RANDOMWALK_HPP
#define RANDOMWALK_HPP

#include "FeaturesComplexNetwork.hpp"

class RandomWalk
{
public:
    RandomWalk();
    FeaturesComplexNetwork walk(int pathLen);
    static void normalizeGraph(FeaturesComplexNetwork& cn);

};

#endif // RANDOMWALK_HPP
