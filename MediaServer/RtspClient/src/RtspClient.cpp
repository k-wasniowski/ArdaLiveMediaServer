#include <MediaServer/RtspClient/RtspClient.hpp>
#include <MediaServer/RtspClient/Details/RtspClientSession.hpp>

#include <iostream>

namespace MediaServer
{
    namespace Rtsp
    {
        RtspClientSharedPtr_t RtspClient::Create(boost::asio::io_context& ioContext)
        {
            return std::make_shared<RtspClient>(ioContext);
        }

        RtspClient::RtspClient(boost::asio::io_context& ioContext)
            : m_ioContext{ioContext}
        {
            std::cout << "RtspClient created!" << std::endl;
        }

        RtspClient::~RtspClient()
        {
            std::cout << "RtspClient destroyed!" << std::endl;
        }

        bool RtspClient::InitiateNewStream(std::string address, uint16_t port)
        {
            std::cout << "Initiating new stream!" << std::endl;
            auto pRtspClientSession = RtspClientSession::Create(m_ioContext);
            pRtspClientSession->Connect(address, port);

            return true;
        }
    }
}