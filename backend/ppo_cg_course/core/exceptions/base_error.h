#ifndef _BASE_ERROR_H_
#define _BASE_ERROR_H_

#include <exception>
#include "../log_app/log_app.h"

class BaseError: public std::exception
{
    protected:
        std::string error_info;
        LogApp log_app;

    public:
        BaseError(log_info_t &log_info){
            error_info = log_info.type_log + " (" + std::to_string(log_info.number_error) + "): "+ log_info.message_error;
            log_app.write_log_info(log_info);
        }

        virtual const char* what() const noexcept override{
            return error_info.c_str();
        }

        virtual ~BaseError() {}
};

#endif
