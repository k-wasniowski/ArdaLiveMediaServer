#include "WhipSignalingHandler.hpp"

#include "rtc/rtc.hpp"

#include <iostream>

namespace Http
{
    namespace WebRTC
    {
        WhipSignalingHandlerUniquePtr_t WhipSignalingHandler::Create(std::function<void(const drogon::HttpResponsePtr&)>&& callback)
        {
            return std::make_unique<WhipSignalingHandler>(std::move(callback));
        }

        WhipSignalingHandler::WhipSignalingHandler(std::function<void(const drogon::HttpResponsePtr&)>&& callback)
            : m_callback(std::move(callback))
        {
            std::cout << "WhipSignalingHandler Created" << std::endl;
        }

        WhipSignalingHandler::~WhipSignalingHandler()
        {
            std::cout << "WhipSignalingHandler Terminated" << std::endl;
        }

        void WhipSignalingHandler::InitiateSignaling(std::shared_ptr<rtc::PeerConnection> pRTCPeerConnection, std::string message)
        {
            std::cout << "WhipSignalingHandler::InitiateSignaling" << std::endl;

            rtc::Description sdp{message, "offer"};

            pRTCPeerConnection->setRemoteDescription(sdp);

            rtc::Description::Video media("video", rtc::Description::Direction::RecvOnly);
            media.addVP8Codec(96);

            auto pSession = std::make_shared<rtc::RtcpReceivingSession>();

            auto pVideoTrack = pRTCPeerConnection->addTrack(media);
            pVideoTrack->setMediaHandler(pSession);

            std::cout << "1 - DESC: " << pVideoTrack->description().description() << std::endl;

            auto oLocalDescription = pRTCPeerConnection->localDescription();
            if(!oLocalDescription.has_value())
            {
                ReportError_();
                return;
            }

            auto localDescription = oLocalDescription.value();

            auto pHttpResponse = drogon::HttpResponse::newHttpResponse();
            pHttpResponse->setStatusCode(drogon::HttpStatusCode::k200OK);
            pHttpResponse->setBody(localDescription);

            m_callback(pHttpResponse);
        }

        void WhipSignalingHandler::ReportError_()
        {
            std::cout << "WhipSignalingHandler::ReportError" << std::endl;

            auto pHttpResponse = drogon::HttpResponse::newHttpResponse();
            pHttpResponse->setStatusCode(drogon::HttpStatusCode::k500InternalServerError);

            m_callback(pHttpResponse);
        }
    }
}