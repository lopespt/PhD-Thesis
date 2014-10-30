#ifndef COMPLEXNETWORKTOMATLAB_HPP
#define COMPLEXNETWORKTOMATLAB_HPP

#include <QFile>
#include <ComplexNetwork/ComplexNetwork.hpp>
#include <Utilities/NodeString.hpp>
#include <Utilities/Link.hpp>

class ComplexNetworkToMatlab
{
public:
    static void convert(QString inputFile, QString outputFile){
        ComplexNetwork<NodeString, Link> cn;
        cn.load(inputFile.toStdString().c_str());
        ComplexNetwork<NodeString, Link>::node_iterator node_it;
        ComplexNetwork<NodeString, Link>::node_iterator node2_it;
        ComplexNetwork<NodeString, Link>::edge_iterator edge_it;

        QFile output(outputFile);
        output.open(QFile::WriteOnly);

        QFile outputLabels("labels.txt");
        outputLabels.open(QFile::WriteOnly);

        unsigned int i=0,j=0;
        output.write(QString("A = zeros(%1, %2);\n").arg(cn.getNodesCount()).arg(cn.getNodesCount()).toLatin1());
        for(node_it = cn.getNodesBeginIterator(); node_it != cn.getNodesEndIterator(); node_it++){
            j=0;
            outputLabels.write(QString("%1: %2\n").arg(i+1).arg(node_it->second->getAttribute().text).toLocal8Bit());
            for(node2_it = cn.getNodesBeginIterator(); node2_it != cn.getNodesEndIterator(); node2_it++){
                  auto e = cn.getEdge(node_it->second, node2_it->second);
                  if(e){
                        output.write(QString("A(%1,%2)=%3;\n").arg(i+1).arg(j+1).arg(e->getAttribute().getWeight()).toLocal8Bit());
                  }
                  j++;
            }
            i++;
        }
        outputLabels.close();
        output.close();

    }
};

#endif // COMPLEXNETWORKTOMATLAB_HPP
