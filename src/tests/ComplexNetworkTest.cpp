
#include "../ComplexNetwork.hpp"
#include <math.h> 
#include <time.h>
#include <random>
#include <fstream>

class node_t{
    public:
        int v1;
        int v2;

    bool operator< (const node_t &other) const {
        if(this->v1 != other.v1)
            return other.v1 > this->v1;
        return other.v2 > this->v1;
    }

    node_t(int v1, int v2):v1(v1), v2(v2){
    }       

};

int memoryInUse(){

    FILE *f = popen("ps -e -o rss -o comm|grep PhD", "r");
    int res;
    fscanf(f, "%d", &res);
    pclose(f);
    return res;
}

void initTest(long int num_nodes, long int max_edges){
    

    for(long int nn = 2000; nn <= num_nodes; nn+= 2000){
        ComplexNetwork<node_t, int> cn;
        for(int i=0;i< nn;i++){
            cn.addNode(new Node<node_t, int>(node_t(i,i+1)));
        }

        std::srand(std::time(NULL));
        const long int max = max_edges;
        time_t last_time = time(NULL);
        time_t initial_time = time(NULL);
        long int density=0;
        int last_density=-1;
        for(long int  i=0; i < max && density<100  ;i++){
            int a = rand()%nn;
            int b = rand()%nn;
            cn.addEdge(new Edge<node_t, int>(cn.getNode(node_t(a,a+1)), cn.getNode(node_t(b,b+1)), a+b));
            density = (i+1)*2./((nn+1)*nn)*100;
            if( density != last_density  ){
                last_density = density;
                last_time = time(NULL);
                printf("nodes: %-7ld \t edges: %-11ld \t density: %3ld %%  \t memory: %5d Mb  time: %7ld secs \n", nn, i+1, density , memoryInUse()/1024, time(NULL)-initial_time );
            }

        }
    }

}



