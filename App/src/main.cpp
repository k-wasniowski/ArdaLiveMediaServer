#include <HttpServer/Server.hpp>
#include <MediaServer/Server.hpp>

#include <iostream>

int main()
{
    std::cout << "Initializing!" << std::endl;

    auto pMediaServer = MediaServer::Server::Create();

    auto pHttpServer = HttpServer::Server::Create(pMediaServer);
    if (!pHttpServer)
    {
        return -1;
    }

    pMediaServer->Run();
    pHttpServer->Run();

    return 0;
}
