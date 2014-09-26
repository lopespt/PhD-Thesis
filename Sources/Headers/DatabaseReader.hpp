
#ifndef DATABASE_READER__HPP
#define DATABASE_READER__HPP

#include "SupervisedImage.hpp"

class DatabaseReader{
    private:

    public:
        virtual SupervisedImage* readNext()=0;

};


#endif

