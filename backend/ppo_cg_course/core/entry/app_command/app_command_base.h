#ifndef _APP_COMMAND_BASE_H_
#define _APP_COMMAND_BASE_H_

#include <QProcess>
#include <QString>
#include <memory>
#include <iostream>

class BaseAppCommand
{
    public:
        virtual ~BaseAppCommand() = 0;
        virtual void execute() = 0;
};

#endif
