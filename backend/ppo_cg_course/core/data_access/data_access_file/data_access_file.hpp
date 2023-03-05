#include <string>
#include "data_access_file.h"

DataAccessFileTxt::DataAccessFileTxt(){
}

DataAccessFileTxt::~DataAccessFileTxt(){
}

/*!
 * \brief create file
 * \param path -- current path of the file
 */
int DataAccessFileTxt::create(std::string path)
{
    std::fstream file;
    file.open(path, std::fstream::out);

    if (!file.is_open()){
        std::cout << "Ошибка открытия файла.\n";
        return -1;
    }
    file.close();
    std::cout << "ok error" << std::endl;
    return 0;
}

void DataAccessFileTxt::update()
{
    //std::cout << "update fuction.\n" << std::endl;
}

void DataAccessFileTxt::remove()
{
    //std::cout << "remove fuction.\n" << std::endl;
}

/*!
 * \brief read file contents
 * \param path -- path to the file
 * \return text from the file
 */
std::string DataAccessFileTxt::load(std::string path)
{
    std::string read_text;
    std::fstream file;
    std::cout << path << std::endl;
    file.open(path, std::fstream::in);
    if (!file.is_open()){
        std::cout << "Ошибка открытия файла.\n";
        return "";
    }
    else{
        getline(file, read_text);
    }

    file.close();
    return read_text;
}

/*!
 \brief write text to file
 \param path -- path to the file
 \param text -- some text
 */
void DataAccessFileTxt::write(std::string path, std::string text)
{
    std::fstream file;
    file.open(path, std::fstream::out);

    if (!file.is_open()){
        std::cout << "Ошибка открытия файла.\n";
    }
    else{
        file << text;
    }
    file.close();
}
