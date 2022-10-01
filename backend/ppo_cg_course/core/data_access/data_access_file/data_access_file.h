#ifndef _DATA_ACCESS_FILE_H_
#define _DATA_ACCESS_FILE_H_

#include <fstream>
#include "data_access_file_base.h"

class DataAccessFileTxt: BaseDataAccessFile
{
    public:
        DataAccessFileTxt();
        ~DataAccessFileTxt();

        virtual int create(std::string path) override;
        virtual void update() override;
        virtual void remove() override;

        virtual std::string load(std::string path) override;
        void write(std::string path, std::string text);
};

#endif
