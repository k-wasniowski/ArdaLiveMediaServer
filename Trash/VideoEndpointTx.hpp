#pragma once

#include "MediaServer/MediaManager/IMediaTrack.hpp"

#include "rtc/rtp.hpp"
#include "rtc/track.hpp"

#include <memory>

namespace Http
{
    namespace WebRTC
    {
        class VideoEndpointTx;
        using VideoEndpointTxSharedPtr_t = std::shared_ptr<VideoEndpointTx>;

        class VideoEndpointTx
            : public MediaServer::IMediaObserver
            , public std::enable_shared_from_this<VideoEndpointTx>
        {
        public:
            static VideoEndpointTxSharedPtr_t Create(std::shared_ptr<rtc::Track> pTrack);

            explicit VideoEndpointTx(std::shared_ptr<rtc::Track> pTrack);
            ~VideoEndpointTx() override;

            void OnFrame(rtc::binary frame) override;

        private:
            void Init_();

            void OnOpen_();

            void OnMessageVariant_(rtc::message_variant message);

            void OnBinaryMessage_(rtc::binary message);

            void OnStringMessage_(rtc::string message);

            void OnClosed_();

        private:
            std::shared_ptr<rtc::Track> m_pTrack;
        };
    }
}
