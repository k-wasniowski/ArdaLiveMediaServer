#include <Resources/VideoEndpointTx.hpp>

#include <iostream>

namespace Http
{
    namespace WebRTC
    {
        VideoEndpointTxSharedPtr_t VideoEndpointTx::Create(std::shared_ptr<rtc::Track> pTrack)
        {
            auto pVideoTrack = std::make_shared<VideoEndpointTx>(std::move(pTrack));
            pVideoTrack->Init_();
            return pVideoTrack;
        }

        VideoEndpointTx::VideoEndpointTx(std::shared_ptr<rtc::Track> pTrack)
            : m_pTrack{std::move(pTrack)}
        {
            std::cout << "VideoTrack Created" << std::endl;
        }

        void VideoEndpointTx::Init_()
        {
            m_pTrack->onOpen(std::bind(&VideoEndpointTx::OnOpen_, shared_from_this()));
            m_pTrack->onMessage(std::bind(&VideoEndpointTx::OnMessageVariant_, shared_from_this(), std::placeholders::_1));
            m_pTrack->onMessage(std::bind(&VideoEndpointTx::OnBinaryMessage_, shared_from_this(), std::placeholders::_1),
                                std::bind(&VideoEndpointTx::OnStringMessage_, shared_from_this(), std::placeholders::_1));
            m_pTrack->onClosed(std::bind(&VideoEndpointTx::OnClosed_, shared_from_this()));
        }

        VideoEndpointTx::~VideoEndpointTx()
        {
            std::cout << "VideoTrack Terminated" << std::endl;
        }

        void VideoEndpointTx::OnOpen_()
        {
            std::cout << "VideoEndpointTx - VideoTrack::OnOpen" << std::endl;
            auto trackDescription = m_pTrack->description();
        }

        void VideoEndpointTx::OnMessageVariant_(rtc::message_variant message)
        {
            std::cout << "VideoEndpointTx - VideoTrack::OnMessageVariant" << std::endl;
        }

        void VideoEndpointTx::OnBinaryMessage_(rtc::binary message)
        {
            std::cout << "VideoEndpointTx - VideoTrack::OnBinaryMessage" << std::endl;
        }

        void VideoEndpointTx::OnStringMessage_(rtc::string message)
        {
            std::cout << "VideoEndpointTx - VideoTrack::OnStringMessage" << std::endl;
        }

        void VideoEndpointTx::OnClosed_()
        {
            std::cout << "VideoEndpointTx - VideoTrack::OnClosed" << std::endl;
        }

        void VideoEndpointTx::OnFrame(rtc::binary frame)
        {
            if (!m_pTrack)
            {
                std::cout << "Track is not initialized" << std::endl;
                return;
            }

            if (!m_pTrack->isOpen())
            {
                std::cout << "Track is not open" << std::endl;
                return;
            }

            //const rtc::SSRC targetSSRC = 42;
            //auto rtp = reinterpret_cast<rtc::RtpHeader *>(frame.data());
            //rtp->setSsrc(targetSSRC);

            //std::cout << "Sending frame with payload type: " << static_cast<int>(rtp->payloadType()) << std::endl;
            m_pTrack->send(frame);
        }
    }
}