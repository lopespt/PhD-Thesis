#ifndef UNORDERED_PAIR_HPP
#define UNORDERED_PAIR_HPP
#include <utility>

using namespace std;

template <typename _TP1, typename _TP2>
class unordered_pair: public pair<_TP1, _TP2>
{
public:
    unordered_pair(_TP1, _TP2);
};

template <typename _TP1, typename _TP2>
unordered_pair<_TP1, _TP2>::unordered_pair(_TP1 a, _TP2 b){
    if(a<b){
        this->first = a;
        this->second = b;
    }else{
        this->first = b;
        this->second = a;
    }
}
#endif // UNORDERED_PAIR_HPP
