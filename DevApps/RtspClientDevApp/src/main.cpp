#include <MediaServer/RtspClient/RtspClient.hpp>

#include <boost/asio.hpp>

int main()
{
    boost::asio::io_context ioContext{};

    auto pRtspClient = MediaServer::Rtsp::RtspClient::Create(ioContext);

    pRtspClient->InitiateNewStream("192.168.0.234", 1024);

    ioContext.run();

    return 0;
}