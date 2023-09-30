#pragma once

#include <Media/Sdp/SessionDescription.hpp>

#include <boost/asio.hpp>

#include <memory>
#include <string>

namespace MediaServer
{
    namespace Rtp
    {
        class RtpClientSession;
        using RtpClientSessionSharedPtr_t = std::shared_ptr<RtpClientSession>;

        class RtpClientSession : public std::enable_shared_from_this<RtpClientSession>
        {
        public:
            static RtpClientSessionSharedPtr_t Create(boost::asio::io_context& ioContext,
                                                      boost::asio::ip::udp::endpoint endpoint,
                                                      Media::Sdp::SessionDescriptionSharedPtr_t pSessionDescription);

            explicit RtpClientSession(boost::asio::io_context& ioContext,
                                      boost::asio::ip::udp::endpoint endpoint,
                                      Media::Sdp::SessionDescriptionSharedPtr_t pSessionDescription);

            virtual ~RtpClientSession();

            void Initiate(std::function<void()> onInitiatedCallback);

        protected:
            void StartReading_();

            void OnMessage_(const boost::system::error_code& errorCode, size_t bytesTransferred);

        private:
            boost::asio::io_context& m_ioContext;
            boost::asio::ip::udp::socket m_socket;
            std::array<std::byte, 8192> m_readStreamBuffer;
            Media::Sdp::SessionDescriptionSharedPtr_t m_pSessionDescription;
        };
    }
}