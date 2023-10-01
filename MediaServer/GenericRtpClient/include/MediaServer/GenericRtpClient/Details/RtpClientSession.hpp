#pragma once

#include <MediaServer/MediaManager/IMediaTrack.hpp>

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

        class RtpClientSession
            : public std::enable_shared_from_this<RtpClientSession>
            , public MediaServer::IMediaTrack
        {
        public:
            static RtpClientSessionSharedPtr_t Create(boost::asio::io_context& ioContext,
                                                      boost::asio::ip::udp::endpoint endpoint,
                                                      Media::Sdp::SessionDescriptionSharedPtr_t pSessionDescription);

            explicit RtpClientSession(boost::asio::io_context& ioContext,
                                      boost::asio::ip::udp::endpoint endpoint,
                                      Media::Sdp::SessionDescriptionSharedPtr_t pSessionDescription);

            virtual ~RtpClientSession();

            void Initiate(std::function<void(IMediaTrackSharedPtr_t pMediaTrack)> onInitiatedCallback);

        public:
            void Attach(MediaObserverSharedPtr_t pMediaObserver) override;

        protected:
            void StartReading_();

            void OnFirstMessage_(const boost::system::error_code& errorCode,
                                 size_t bytesTransferred,
                                 std::function<void(IMediaTrackSharedPtr_t pMediaTrack)> onInitiatedCallback);

            void OnMessage_(const boost::system::error_code& errorCode, size_t bytesTransferred);

        private:
            boost::asio::io_context& m_ioContext;
            boost::asio::ip::udp::socket m_socket;
            std::array<std::byte, 8192> m_readStreamBuffer;
            Media::Sdp::SessionDescriptionSharedPtr_t m_pSessionDescription;
        };
    }
}