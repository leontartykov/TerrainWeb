#ifndef _DATA_ACCESS_BASE_H_
#define _DATA_ACCESS_BASE_H_

#include <iostream>

class BaseDataAccess
{
    public:
        BaseDataAccess() = default;
        virtual ~BaseDataAccess() = default;

        virtual int create(std::string path) = 0;
        virtual void update() = 0;
        virtual void remove() = 0;
        virtual std::string load(std::string path) = 0;
};

#endif
