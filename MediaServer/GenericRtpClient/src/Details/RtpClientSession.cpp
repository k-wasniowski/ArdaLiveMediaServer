#include <MediaServer/GenericRtpClient/Details/RtpClientSession.hpp>

#include <Media/Core/MediaBuffer.hpp>
#include <Media/Core/Rtp/RtpPacket.hpp>
#include <Media/Core/VideoFrame.hpp>

#include <boost/bind/bind.hpp>

#include <iostream>

namespace MediaServer
{
    namespace Rtp
    {
        RtpClientSessionSharedPtr_t RtpClientSession::Create(boost::asio::io_context& ioContext,
                                                             boost::asio::ip::udp::endpoint endpoint,
                                                             Media::Sdp::SessionDescriptionSharedPtr_t pSessionDescription)
        {
            return std::make_shared<RtpClientSession>(ioContext, endpoint, pSessionDescription);
        }

        RtpClientSession::RtpClientSession(boost::asio::io_context& ioContext,
                                           boost::asio::ip::udp::endpoint endpoint,
                                           Media::Sdp::SessionDescriptionSharedPtr_t pSessionDescription)
            : m_ioContext{ioContext}
            , m_socket{m_ioContext, endpoint}
            , m_readStreamBuffer{}
            , m_pSessionDescription{pSessionDescription}
        {
            std::cout << "RtpClientSession::RtpClientSession()" << std::endl;
        }

        RtpClientSession::~RtpClientSession()
        {
            std::cout << "RtpClientSession::~RtpClientSession()" << std::endl;
        }

        void RtpClientSession::Initiate()
        {
            std::cout << "RtpClientSession::Initiate()" << std::endl;

            StartReading_();
        }

        void RtpClientSession::StartReading_()
        {
            m_socket.async_receive(boost::asio::buffer(m_readStreamBuffer),
                                   boost::bind(&RtpClientSession::OnMessage_,
                                               shared_from_this(),
                                               boost::asio::placeholders::error,
                                               boost::asio::placeholders::bytes_transferred));
        }

        void RtpClientSession::OnMessage_(const boost::system::error_code& errorCode, size_t bytesTransferred)
        {
            if (errorCode)
            {
                std::cout << "Error: " << errorCode.message() << std::endl;

                return;
            }

            std::vector<std::byte> data{};
            data.resize(bytesTransferred);
            std::copy(m_readStreamBuffer.begin(), m_readStreamBuffer.begin() + bytesTransferred, data.begin());

            auto pMediaBuffer = Media::Core::MediaBuffer::Create(std::move(data));
            auto pFrame = Media::Core::VideoFrame::Create(pMediaBuffer);

            StartReading_();
        }
    }
}