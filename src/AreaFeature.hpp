
#ifndef AREA_FEATURE__HPP
#define AREA_FEATURE__HPP

#include "Feature.hpp"
#include "Region.hpp"

class AreaFeature:public Feature{

    public:
        AreaFeature(Region* region);
        void extractFeature();       

};

#endif

