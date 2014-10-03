
#ifndef DATABASE_READER__HPP
#define DATABASE_READER__HPP

#include "SupervisedImage.hpp"

class DatabaseReader{
    private:

    public:
        virtual SupervisedImage readNext()=0;
        virtual SupervisedImage readPrevious()=0;
        virtual bool hasNext() const=0;
        virtual bool hasPrevious() const=0;

};


#endif

