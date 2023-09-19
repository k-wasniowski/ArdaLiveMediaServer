// Copyright 2023 The Arda Project Authors. All rights reserved.
//
// Copying, utilizing or revealing any part or entirety of this file
// and its contents without proper authorization is not allowed.

#include <Resources/PeerConnection.hpp>
#include <Resources/WebRtcController.hpp>
#include <Resources/WhepSignalingHandler.hpp>
#include <Resources/WhipSignalingHandler.hpp>

#include <Resources/VideoEndpointRx.hpp>
#include <Resources/VideoEndpointTx.hpp>

#include <MediaServer/MediaManager/MediaResource.hpp>

#include <rtc/rtc.hpp>

#include <memory>

namespace Http
{
    WebRtcControllerSharedPtr_t WebRtcController::Create(MediaServer::MediaManagerSharedPtr_t pMediaManager)
    {
        //rtc::InitLogger(rtc::LogLevel::Verbose);

        return std::make_shared<WebRtcController>(pMediaManager);
    }

    WebRtcController::WebRtcController(MediaServer::MediaManagerSharedPtr_t pMediaManager)
        : m_pMediaManager{std::move(pMediaManager)}
    {
        std::cout << "Creating WebRtcController" << std::endl;
    }

    void WebRtcController::PostResource(const drogon::HttpRequestPtr& req,
                                        std::function<void(const drogon::HttpResponsePtr&)>&& callback,
                                        std::string&& resource)
    {
        std::cout << "WebRtcController::PostResource" << std::endl;

        std::string body{req->body()};

        rtc::Configuration config;
        config.iceServers.emplace_back("stun:stun.l.google.com:19302");
        config.iceServers.emplace_back("stun:stun1.l.google.com:19302");
        config.iceServers.emplace_back("stun:stun2.l.google.com:19302");
        config.iceServers.emplace_back("stun:stun3.l.google.com:19302");
        config.iceServers.emplace_back("stun:stun4.l.google.com:19302");

        auto pMediaResource = MediaServer::MediaResource::Create(std::move(resource));
        m_pMediaManager->AddMediaResource(pMediaResource);

        auto onTrackCallback = [pMediaResource](std::shared_ptr<rtc::Track> pTrack) {
            std::cout << "onTrackCallback - " << pTrack->direction() << std::endl;

            auto pVideoTrack = WebRTC::VideoEndpointRx::Create(std::move(pTrack));
            pMediaResource->AddTrack(pVideoTrack);
        };

        auto pRTCPeerConnection = std::make_shared<rtc::PeerConnection>();
        auto pPeerConnection = WebRTC::PeerConnection::Create(pRTCPeerConnection, onTrackCallback);

        auto pWhepSignalingHandler = WebRTC::WhepSignalingHandler::Create(std::move(callback));
        pPeerConnection->InitiateSignaling(std::move(pWhepSignalingHandler), body);
    }

    void WebRtcController::GetResource(const drogon::HttpRequestPtr& req,
                                       std::function<void(const drogon::HttpResponsePtr&)>&& callback,
                                       std::string&& resource)
    {
        std::cout << "WebRtcController::PostResource" << std::endl;

        std::string body{req->body()};

        rtc::Configuration config;
        config.iceServers.emplace_back("stun:stun.l.google.com:19302");
        config.iceServers.emplace_back("stun:stun1.l.google.com:19302");
        config.iceServers.emplace_back("stun:stun2.l.google.com:19302");
        config.iceServers.emplace_back("stun:stun3.l.google.com:19302");
        config.iceServers.emplace_back("stun:stun4.l.google.com:19302");

        auto pMediaResource = m_pMediaManager->GetMediaResource(resource);

        auto onTrackCallback = [pMediaResource](std::shared_ptr<rtc::Track> pTrack) {
            std::cout << "onTrackCallback - " << pTrack->direction() << std::endl;

            auto pVideoEndpointTx = WebRTC::VideoEndpointTx::Create(std::move(pTrack));

            auto pVideoEndpointRx = pMediaResource->GetTrack("");

            pVideoEndpointRx->Attach(pVideoEndpointTx);
        };

        auto pRTCPeerConnection = std::make_shared<rtc::PeerConnection>();

        auto pPeerConnection = WebRTC::PeerConnection::Create(pRTCPeerConnection, onTrackCallback);

        auto pWhipSignalingHandler = WebRTC::WhipSignalingHandler::Create(std::move(callback));
        pPeerConnection->InitiateSignaling(std::move(pWhipSignalingHandler), body);
    }
}