#ifndef RANDOMWALK_HPP
#define RANDOMWALK_HPP

#include <ComplexNetwork/ComplexNetwork.hpp>
#include <Utilities/FeaturesComplexNetwork.hpp>
#include <Utilities/CachedComplexNetwork.hpp>
class RandomWalk
{
private:
    RandomWalk();
public:
    static CachedComplexNetwork<int, double> walkOneStep(CachedComplexNetwork<int, double> cn);
    static CachedComplexNetwork<int, double> convertToWalkNetwork(FeaturesComplexNetwork cn);
    static CachedComplexNetwork<int, double> normalizeGraph(CachedComplexNetwork<int, double> cn);
    static CachedComplexNetwork<int, double> addAutoLoop(CachedComplexNetwork<int, double> cn);

};

#endif // RANDOMWALK_HPP
