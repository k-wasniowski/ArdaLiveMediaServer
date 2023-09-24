#include <MediaServer/GenericRtpClient/Details/RtpClientSession.hpp>

#include <boost/asio.hpp>

int main()
{
    boost::asio::io_context ioContext{};

    boost::asio::ip::udp::endpoint mediaEndpoint{boost::asio::ip::address::from_string("127.0.0.1"), 5004};
    auto pRtpClientSession = MediaServer::Rtp::RtpClientSession::Create(ioContext, mediaEndpoint);

    pRtpClientSession->Initiate();

    ioContext.run();

    return 0;
}