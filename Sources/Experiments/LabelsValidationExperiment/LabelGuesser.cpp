#include "LabelGuesser.hpp"
#include <QString>
#include <string.h>

LabelGuesser::LabelGuesser(FeaturesComplexNetwork *cn):cn(cn)
{
    buildIndex();
}

void LabelGuesser::buildIndex(){
    char buffer[100];
    for(FeaturesComplexNetwork::NodeIterator i = cn->Begin(); i != cn->End() ; i++ ){
        QString key = QString::fromLocal8Bit((*i)->asString(buffer));
        index.insert(key, i.getNodeId());
    }
}

bool LabelGuesser::Guess(SupervisedImage *img, int guessRegionAt){
    char buffer[100];
    QHash<node_id, float> grades;

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
    float max = 0;
    node_id guessed;
    for(auto i = grades.begin(); i != grades.end(); i++){
        rank.push_back(QPair<node_id,float>(i.key(),i.value()));
    }

    qSort(rank.begin(), rank.end(), [&](QPair<node_id, float> a,
          QPair<node_id, float> b){
                return a.second*1.0/sqrt(cn->getNumEdges(a.first))  > b.second*1.0/sqrt(cn->getNumEdges(b.first));
          }
    );



    guessed = rank.first().first;

    (*cn->getNode(guessed))->asString(buffer);

    bool result = strcmp(buffer, img->getRegions().at(guessRegionAt).getLabel().toStdString().c_str())==0;

    //printf("%s%s%s%s: ", result?"->":"", buffer, result ? "==":"!=" ,img->getRegions().at(guessRegionAt).getLabel().toStdString().c_str() );
    for(int i=0;i<10 && i < rank.size();i++){
    //    printf(" %s |", (*cn->getNode(rank[i].first))->asString(buffer) );
    }
    //printf("\n");
    fflush(stdout);

    return result;
}
