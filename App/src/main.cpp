#include <HttpServer/Server.hpp>
#include <MediaServer/MediaManager/MediaManager.hpp>
#include <MediaServer/RtspClient/RtspClient.hpp>
#include <MediaServer/GenericRtpClient/GenericRtpClient.hpp>

#include <iostream>

int main()
{
    std::cout << "Initializing!" << std::endl;

    boost::asio::io_context ioContext{};

    auto pRtspClient = MediaServer::Rtsp::RtspClient::Create(ioContext);
    auto pGenericRtpClient = MediaServer::Rtp::GenericRtpClient::Create(ioContext);

    auto pMediaManager = MediaServer::MediaManager::Create();

    auto pHttpServer = HttpServer::Server::Create(pMediaManager);
    if (!pHttpServer)
    {
        return -1;
    }

    pHttpServer->Run();

    return 0;
}
