#include <MediaServer/GenericRtpClient/GenericRtpClient.hpp>
#include <MediaServer/GenericRtpClient/Details/RtpClientSession.hpp>

#include <Media/Sdp/SessionDescription.hpp>

#include <iostream>

namespace MediaServer
{
    namespace Rtp
    {
        GenericRtpClientSharedPtr_t GenericRtpClient::Create(boost::asio::io_context& ioContext)
        {
            return std::make_shared<GenericRtpClient>(ioContext);
        }

        GenericRtpClient::GenericRtpClient(boost::asio::io_context& ioContext)
            : m_ioContext{ioContext}
        {}

        GenericRtpClient::~GenericRtpClient() {}

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
