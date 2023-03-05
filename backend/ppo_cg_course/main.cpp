#include "./core/main_client.cpp"
#include "./server/main_server.cpp"

int usage(){
    std::cerr << "Usage for client: progname client";
    std::cerr << "Usage for server: progname server";
    return EXIT_FAILURE;
}

int main(int argc, char *argv[])
{
    std::string service;

    if (argc != 2){
        return usage();
    }

    service = argv[1];

    if (service == "client"){
        return main_client(argc, argv);
    }
    else if (service == "server"){
        return main_server(argc, argv);
    }
}
