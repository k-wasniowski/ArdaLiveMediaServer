#include "WhepSignalingHandler.hpp"

#include "rtc/rtc.hpp"

#include <iostream>

namespace Http
{
    namespace WebRTC
    {
        WhepSignalingHandlerUniquePtr_t WhepSignalingHandler::Create(std::function<void(const drogon::HttpResponsePtr&)>&& callback)
        {
            return std::make_unique<WhepSignalingHandler>(std::move(callback));
        }

        WhepSignalingHandler::WhepSignalingHandler(std::function<void(const drogon::HttpResponsePtr&)>&& callback)
            : m_callback(std::move(callback))
        {
            std::cout << "WhepSignalingHandler Created" << std::endl;
        }

        WhepSignalingHandler::~WhepSignalingHandler()
        {
            std::cout << "WhepSignalingHandler Terminated" << std::endl;
        }

        void WhepSignalingHandler::InitiateSignaling(std::shared_ptr<rtc::PeerConnection> pRTCPeerConnection, std::string message)
        {
            std::cout << "WhepSignalingHandler::InitiateSignaling" << std::endl;

            rtc::Description sdp{message, "offer"};

            pRTCPeerConnection->setRemoteDescription(sdp);

            const rtc::SSRC targetSSRC = 42;
            rtc::Description::Video media("video", rtc::Description::Direction::SendOnly);
            media.addVP8Codec(96);
            media.addSSRC(targetSSRC, "video-send");

            pRTCPeerConnection->addTrack(media);

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

        void WhepSignalingHandler::ReportError_()
        {
            std::cout << "WhepSignalingHandler::ReportError" << std::endl;

            auto pHttpResponse = drogon::HttpResponse::newHttpResponse();
            pHttpResponse->setStatusCode(drogon::HttpStatusCode::k500InternalServerError);

            m_callback(pHttpResponse);
        }
    }
}