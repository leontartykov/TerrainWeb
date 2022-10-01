#ifndef _DATA_ACCESS_FILE_BASE_H_
#define _DATA_ACCESS_FILE_BASE_H_

#include <iostream>

class BaseDataAccessFile
{
    public:
        BaseDataAccessFile() = default;
        virtual ~BaseDataAccessFile() = default;

        virtual int create(std::string path) = 0;
        virtual void update() = 0;
        virtual void remove() = 0;

        virtual std::string load(std::string path) = 0;
};

#endif
