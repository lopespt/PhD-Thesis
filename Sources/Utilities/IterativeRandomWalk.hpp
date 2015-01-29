#ifndef ITERATIVERANDOMWALK_HPP
#define ITERATIVERANDOMWALK_HPP

#include <ComplexNetwork/ComplexNetwork.hpp>
#include <Utilities/CachedComplexNetwork.hpp>
#include "RandomWalk.hpp"
#include <stdlib.h>
#include <QVector>
#include <set>
using namespace std;
class IterativeRandomWalk
{
private:
    CachedComplexNetwork<int, double> cn;
    QVector<double> probs;
    QVector<double> probs2;
    typedef struct{
        node_id from;
        node_id to;
    }edges_list;

public:
    IterativeRandomWalk(FeaturesComplexNetwork *cn);
    IterativeRandomWalk(CachedComplexNetwork<int, double> *cn);
    void Execute(node_id start_node, unsigned int max_path_length);
    float getProbability(node_id node);
    QVector<double> getAllProbs();
};

#endif // ITERATIVERANDOMWALK_HPP
