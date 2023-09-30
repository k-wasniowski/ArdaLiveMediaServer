#include <MediaServer/GenericRtpClient/Details/RtpClientSession.hpp>
#include <MediaServer/GenericRtpClient/GenericRtpClient.hpp>

#include <Media/Sdp/SessionDescription.hpp>

#include <iostream>

namespace
{
    constexpr auto kDefaultNumberOfThreads = 4;
}

namespace MediaServer
{
    namespace Rtp
    {
        GenericRtpClientSharedPtr_t GenericRtpClient::Create()
        {
            return std::make_shared<GenericRtpClient>();
        }

        GenericRtpClient::GenericRtpClient()
            : m_ioContext{}
        {
            for (auto i = 0; i < kDefaultNumberOfThreads; ++i)
            {
                m_threadPool.create_thread(boost::bind(&boost::asio::io_context::run, &m_ioContext));
            }
        }

        GenericRtpClient::~GenericRtpClient()
        {
            m_ioContext.stop();
            m_threadPool.join_all();
        }

        bool GenericRtpClient::InitiateNewSession(std::string ip, uint16_t port, std::string sessionDescription)
        {
            std::cout << "GenericRtpClient::InitiateNewClient()" << std::endl;

            try
            {
                auto endpoint = boost::asio::ip::udp::endpoint(boost::asio::ip::make_address(ip), port);
                auto pSessionDescription = Media::Sdp::SessionDescription::Parse(sessionDescription);
                auto pRtpClientSession = RtpClientSession::Create(m_ioContext, endpoint, pSessionDescription);

                pRtpClientSession->Initiate();

                return true;
            }
            catch (const std::exception& e)
            {
                std::cout << "Error: " << e.what() << std::endl;
                return false;
            }
        }
    }
}
