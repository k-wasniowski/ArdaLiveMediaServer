#include "VideoEndpointRx.hpp"

#include "Media/Core/Frame.hpp"

#include <iostream>

namespace Http
{
    namespace WebRTC
    {
        VideoEndpointRxSharedPtr_t VideoEndpointRx::Create(std::shared_ptr<rtc::Track> pTrack)
        {
            auto pVideoTrack = std::make_shared<VideoEndpointRx>(std::move(pTrack));
            pVideoTrack->Init_();
            return pVideoTrack;
        }

        VideoEndpointRx::VideoEndpointRx(std::shared_ptr<rtc::Track> pTrack)
            : m_pTrack{std::move(pTrack)}
        {
            std::cout << "VideoTrack Created" << std::endl;
        }

        void VideoEndpointRx::Init_()
        {
            m_pTrack->onOpen(std::bind(&VideoEndpointRx::OnOpen_, shared_from_this()));
            m_pTrack->onMessage(std::bind(&VideoEndpointRx::OnMessageVariant_, shared_from_this(), std::placeholders::_1));
            m_pTrack->onMessage(std::bind(&VideoEndpointRx::OnBinaryMessage_, shared_from_this(), std::placeholders::_1),
                                std::bind(&VideoEndpointRx::OnStringMessage_, shared_from_this(), std::placeholders::_1));
            m_pTrack->onClosed(std::bind(&VideoEndpointRx::OnClosed_, shared_from_this()));
        }

        VideoEndpointRx::~VideoEndpointRx()
        {
            std::cout << "VideoTrack Terminated" << std::endl;
        }

        void VideoEndpointRx::OnOpen_()
        {
            std::cout << "VideoTrack::OnOpen" << std::endl;
            auto trackDescription = m_pTrack->description();

            std::cout << "DESC: " << trackDescription.description() << std::endl;
            std::cout << "Payloads: " << std::endl;
            for (auto& payload : trackDescription.payloadTypes())
            {
                std::cout << "Payload: " << payload << std::endl;
            }
            std::cout << "TYPE: " << trackDescription.type() << std::endl;
        }

        void VideoEndpointRx::OnMessageVariant_(rtc::message_variant message)
        {
            std::cout << "VideoTrack::OnMessageVariant" << std::endl;
        }

        void VideoEndpointRx::OnBinaryMessage_(rtc::binary message)
        {
            auto rtp = reinterpret_cast<rtc::RtpHeader*>(message.data());
            std::cout << "Received SSRC: " << rtp->ssrc() << std::endl;

            for (auto& pMediaObserver : m_mediaObservers)
            {
                pMediaObserver->OnFrame(message);
            }
        }

        void VideoEndpointRx::OnStringMessage_(rtc::string message)
        {
            std::cout << "VideoTrack::OnStringMessage" << std::endl;
        }

        void VideoEndpointRx::OnClosed_()
        {
            std::cout << "VideoTrack::OnClosed" << std::endl;
        }

        void VideoEndpointRx::Attach(MediaServer::MediaObserverSharedPtr_t pMediaObserver)
        {
            m_mediaObservers.push_back(pMediaObserver);

            m_pTrack->requestKeyframe();
        }
    }
}