#pragma once

#include <MediaServer/MediaManager/MediaManager.hpp>

#include <drogon/HttpController.h>

#include <memory>

namespace HttpServer
{
    namespace Resources
    {
        class GenericRtpController;
        using GenericRtpControllerSharedPtr_t = std::shared_ptr<GenericRtpController>;

        class GenericRtpController : public drogon::HttpController<GenericRtpController, false>
        {
        public:
            static GenericRtpControllerSharedPtr_t Create(MediaServer::MediaManagerSharedPtr_t pMediaManager);

            GenericRtpController(MediaServer::MediaManagerSharedPtr_t pMediaManager);
            ~GenericRtpController() override;

            METHOD_LIST_BEGIN
            ADD_METHOD_TO(GenericRtpController::PostResource, "/api/v1/resources/generic-rtp/{resource}", drogon::Post);
            METHOD_LIST_END

            void PostResource(const drogon::HttpRequestPtr& req,
                              std::function<void(const drogon::HttpResponsePtr&)>&& callback,
                              std::string&& resource);

        private:
            void SendHttpSuccessResponse_(std::function<void(const drogon::HttpResponsePtr&)>&& callback);

        private:
            MediaServer::MediaManagerSharedPtr_t m_pMediaManager;
        };
    }
}
