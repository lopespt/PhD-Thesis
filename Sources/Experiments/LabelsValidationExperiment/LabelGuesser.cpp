#include "LabelGuesser.hpp"
#include <QString>
#include <string.h>
#include <QSet>

LabelGuesser::LabelGuesser(FeaturesComplexNetwork *cn):cn(cn)
{
    //removeHubs();
    buildIndex();
}

void LabelGuesser::buildIndex(){
    char buffer[100];
    for(FeaturesComplexNetwork::NodeIterator i = cn->Begin(); i != cn->End() ; i++ ){
        QString key = QString::fromLocal8Bit((*i)->asString(buffer));
        index.insert(key, i.getNodeId());
    }
}

void LabelGuesser::removeHubs(){
    QVector<QPair<node_id, float>> degrees;
    for(auto n = cn->Begin(); n != cn->End(); n++ ){
            degrees.append(QPair<node_id,float>(n.getNodeId(), cn->getOutputDegree(n.getNodeId()) ));
    }

    qSort(degrees.begin(), degrees.end(), [&](QPair<node_id, float> a, QPair<node_id, float> b){return a.second > b.second;});

    for(int i=0;i<3;i++){
        hubs.insert(degrees[i].first);
    }

}

bool LabelGuesser::Guess(SupervisedImage *img, int guessRegionAt){
    char buffer[100];
    QHash<node_id, float> grades;
    QSet<node_id> image_nodes;

    for(int i=0;i<img->getRegions().size();i++){
        if(i!=guessRegionAt){
            node_id node = index[img->getRegions().at(i).getLabel()];
            image_nodes.insert(node);
        }
    }

    for(int i=0;i<img->getRegions().size();i++){
        if(i!=guessRegionAt){
            node_id node = index[img->getRegions().at(i).getLabel()];
            for(FeaturesComplexNetwork::EdgeIterator e = cn->EdgesBegin( node ); e != cn->EdgesEnd( node ); e++ ){
                    if (grades.contains(e.getToNodeId()))
                        grades[e.getToNodeId()]+= e->getWeight();
                    else
                        grades[e.getToNodeId()] = e->getWeight();
            }
        }
    }

    QList<QPair<node_id, float>> rank;
    node_id guessed;
    for(auto i = grades.begin(); i != grades.end(); i++){
        rank.push_back(QPair<node_id,float>(i.key(),i.value()));
    }

    qSort(rank.begin(), rank.end(), [&](QPair<node_id, float> a,
          QPair<node_id, float> b){
                return a.second*1.0  > b.second*1.0;
          }
    );


    guessed = rank.first().first;
    for(auto i = rank.begin(); i != rank.end(); i++){
        if( !hubs.contains(i->first) ){
            guessed = i->first;
            break;
        }
    }

    (*cn->getNode(guessed))->asString(buffer);

    bool result = strcmp(buffer, img->getRegions().at(guessRegionAt).getLabel().toStdString().c_str())==0;

    //printf("%s%s%s%s\n", result ? "acertou":"errou  ", buffer, result ? "==":"!=" ,img->getRegions().at(guessRegionAt).getLabel().toStdString().c_str() );
    //printf("%s%s%s%s: ", result ? "->":"", buffer, result ? "==":"!=" ,img->getRegions().at(guessRegionAt).getLabel().toStdString().c_str() );
    //for(int i=0;i<10 && i < rank.size();i++){
    //    printf(" %s |", (*cn->getNode(rank[i].first))->asString(buffer) );
    //}
    //printf("\n");
    fflush(stdout);

    return result;
}
