// Copyright 2023 The Arda Project Authors. All rights reserved.
//
// Copying, utilizing or revealing any part or entirety of this file
// and its contents without proper authorization is not allowed.

#pragma once

#include <MediaServer/MediaManager/IMediaTrack.hpp>

#include <rtc/rtc.hpp>

#include <memory>

namespace Http
{
    namespace WebRTC
    {
        class VideoEndpointRx;
        using VideoEndpointRxSharedPtr_t = std::shared_ptr<VideoEndpointRx>;

        class VideoEndpointRx
            : public MediaServer::IMediaTrack
            , public std::enable_shared_from_this<VideoEndpointRx>
        {
        public:
            static VideoEndpointRxSharedPtr_t Create(std::shared_ptr<rtc::Track> pTrack);

            explicit VideoEndpointRx(std::shared_ptr<rtc::Track> pTrack);
            ~VideoEndpointRx() override;

            void Attach(MediaServer::MediaObserverSharedPtr_t pMediaObserver) override;

        private:
            void Init_();

            void OnOpen_();

            void OnMessageVariant_(rtc::message_variant message);

            void OnBinaryMessage_(rtc::binary message);

            void OnStringMessage_(rtc::string message);

            void OnClosed_();

        private:
            std::shared_ptr<rtc::Track> m_pTrack;
            std::list<MediaServer::MediaObserverSharedPtr_t> m_mediaObservers;
        };
    }
}