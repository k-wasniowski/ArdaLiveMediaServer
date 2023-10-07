#include <MediaServer/GenericRtpClient/Details/RtpClientSession.hpp>
#include <MediaServer/GenericRtpClient/GenericRtpClient.hpp>

#include <Media/Sdp/SessionDescription.hpp>

#include <coroutine>
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
            , m_workGuard{boost::asio::make_work_guard(m_ioContext)}
            , m_threadPool{}
        {
            std::cout << "GenericRtpClient::GenericRtpClient()" << std::endl;

            for (auto i = 0; i < kDefaultNumberOfThreads; ++i)
            {
                m_threadPool.create_thread([this]() {
                    std::cout << "GenericRtpClient::GenericRtpClient() - Running thread!" << std::endl;
                    m_ioContext.run();
                    std::cout << "GenericRtpClient::GenericRtpClient() - Thread finished!" << std::endl;
                });
            }
        }

        GenericRtpClient::~GenericRtpClient()
        {
            std::cout << "GenericRtpClient::~GenericRtpClient()" << std::endl;

            m_workGuard.reset();
            m_ioContext.stop();
            m_threadPool.join_all();
        }

        bool GenericRtpClient::InitiateNewSession(std::string ip, uint16_t port, std::function<void(IMediaTrackSharedPtr_t pMediaTrack)> callback)
        {
            try
            {
                auto endpoint = boost::asio::ip::udp::endpoint(boost::asio::ip::make_address(ip), port);
                auto pRtpClientSession = RtpClientSession::Create(m_ioContext, endpoint);

                pRtpClientSession->Initiate(callback);

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
