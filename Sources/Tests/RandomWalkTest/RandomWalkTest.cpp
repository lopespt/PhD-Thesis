#include <Utilities//IterativeRandomWalk.hpp>
#include <FeatureExtractors/FeatureFactoryAbstract.hpp>
#include <QList>

class getWeight {
public:
    float operator()(ComplexNetwork <shared_ptr<const FeatureAbstract>, Link> *cn, node_id from, node_id to) {
        return cn->getEdge(from, to)->getWeight();
    }
};

RandomWalkTest::RandomWalkTest() {
}

/*void printMatlab(const char *n, QVector <double> v) {
    printf("%s =[\n", n);
    for(double i: v) {
        printf("%f \n", i);
    }
    printf("];");
}*/

void RandomWalkTest::execute() {
    char buffer[100];
    FeaturesComplexNetwork cn;


    LabelFeatureFactory factory;
    QList<FeatureFactoryAbstract* > facts;
    facts.append(&factory);
    cn.load("/tmp/Implementation-Build/bin/labels.cn", facts);
    IterativeRandomWalk walk(&cn);
    walk.Execute(566, 1);
    QVector<double> v(cn.getNumNodes());
    for (auto n = cn.Begin(); n != cn.End(); n++) {
        v[n.getNodeId()] = walk.getProbability(n.getNodeId());
    }

    printf("S = {\n");
    for (node_id i = 0; i < cn.getNumNodes(); i++) {
        printf("'%s' \n", (*cn.getNode(i))->asString(buffer));
    }
    printf("};\n");

    printMatlab("A", v);

    walk.Execute(28, 1);
    for (auto n = cn.Begin(); n != cn.End(); n++) {
        v[n.getNodeId()] = walk.getProbability(n.getNodeId());
    }
    printMatlab("B", v);


    walk.Execute(5, 1);
    for (auto n = cn.Begin(); n != cn.End(); n++) {
        v[n.getNodeId()] = walk.getProbability(n.getNodeId());
    }
    printMatlab("C", v);
}
