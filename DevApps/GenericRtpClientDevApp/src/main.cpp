#include <MediaServer/GenericRtpClient/GenericRtpClient.hpp>

#include <boost/asio.hpp>

int main()
{
    boost::asio::io_context ioContext{};

    auto pRtpClientSession = MediaServer::Rtp::GenericRtpClient::Create(ioContext);

    std::string address{"127.0.0.1"};
    uint16_t port = 5004;
    std::string sessionDescription = "v=0\r\n"
                                     "o=- 0 0 IN IP4 127.0.0.1\r\n"
                                     "s=No Name\r\n"
                                     "c=IN IP4 127.0.0.1\r\n"
                                     "t=0 0\r\n"
                                     "a=tool:libavformat 60.4.101\r\n"
                                     "m=video 5004 RTP/AVP 96\r\n"
                                     "b=AS:256\r\n"
                                     "a=rtpmap:96 VP8/90000\r\n";

    pRtpClientSession->InitiateNewSession(address, port, sessionDescription);

    ioContext.run();

    return 0;
}