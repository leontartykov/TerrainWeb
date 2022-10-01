#include "log_app.h"

LogApp::LogApp(){
}

LogApp::~LogApp(){

}

void LogApp::write_log_info(log_info_t &log_info)
{
    try
    {
        std::fstream log_file;
        log_file.open(_path_log_info_user, std::fstream::app);

        if (!log_file.is_open()){
            log_file.open(_path_log_info_user, std::fstream::in);

            if (!log_file.is_open()){
                return ;
            }
        }

        std::string info;
        if (log_info.type_log.compare("error") == 0)
        {
            info = log_info.type_log + ": " + std::to_string(log_info.number_error) + "; " + \
                                "user: " + log_info.user_login + "; " + log_info.file_name + \
                                "; " + log_info.class_name + "; " + log_info.function_name + "; " + "line: " + std::to_string(log_info.line_error) + \
                                "; " + log_info.message_error + "; " + log_info.time_error;

        }
        else if (log_info.type_log.compare("info") == 0){
            info = log_info.type_log + ": " + "user: " + log_info.user_login + "; " + log_info.message_error + \
                       "; " + log_info.time_error;
        }

        log_file << info;

        log_file.close();
    }
    catch (std::exception const &e){
        std::cerr << e.what() << '\n';
    }

}
