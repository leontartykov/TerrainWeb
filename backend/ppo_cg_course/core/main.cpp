#include <iostream>

#include "core/entry/entry.h"
#include "core/entry/app_command/app_command.h"
#include "core/entry/app_facade/app_facade.h"
#include "server/server.h"

int main(int argc, char *argv[])
{
    /*QCoreApplication a(argc, argv);
    std::unique_ptr<EntrySystem> system;
    system = std::unique_ptr<EntrySystem>(new EntrySystem());

    system->enter_system();
    return a.exec();*/
    boost::asio::io_service io_service;
    HTTPServerTCP http_server(io_service);
    io_service.run();

    return 0;
}
