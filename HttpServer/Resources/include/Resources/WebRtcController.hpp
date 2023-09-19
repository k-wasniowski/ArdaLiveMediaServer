// Copyright 2023 The Arda Project Authors. All rights reserved.
//
// Copying, utilizing or revealing any part or entirety of this file
// and its contents without proper authorization is not allowed.

#pragma once

#include <MediaServer/MediaManager/MediaManager.hpp>

#include <drogon/HttpController.h>

#include <memory>

namespace Http
{
    class WebRtcController;
    using WebRtcControllerSharedPtr_t = std::shared_ptr<WebRtcController>;

    class WebRtcController : public drogon::HttpController<WebRtcController, false>
    {
    public:
        static WebRtcControllerSharedPtr_t Create(MediaServer::MediaManagerSharedPtr_t pMediaManager);

        explicit WebRtcController(MediaServer::MediaManagerSharedPtr_t pMediaManager);
        ~WebRtcController() override = default;

        METHOD_LIST_BEGIN
        ADD_METHOD_TO(WebRtcController::PostResource, "/api/v1/resources/webrtc/{resource}", drogon::Post);
        ADD_METHOD_TO(WebRtcController::GetResource, "/api/v1/resources/webrtc/{resource}", drogon::Get);
        METHOD_LIST_END

        void PostResource(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback, std::string&& resource);

        void GetResource(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback, std::string&& resource);

    private:
        MediaServer::MediaManagerSharedPtr_t m_pMediaManager;
    };
}
