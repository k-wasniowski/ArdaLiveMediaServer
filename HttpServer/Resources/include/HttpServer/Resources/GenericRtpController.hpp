#pragma once

#include <MediaServer/Server.hpp>

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
            static GenericRtpControllerSharedPtr_t Create(MediaServer::ServerSharedPtr_t pMediaServer);

            GenericRtpController(MediaServer::ServerSharedPtr_t pMediaServer);
            ~GenericRtpController() override;

            METHOD_LIST_BEGIN
            ADD_METHOD_TO(GenericRtpController::PostResource, "/api/v1/resources/generic-rtp/{resource}", drogon::Post);
            ADD_METHOD_TO(GenericRtpController::PostResourceAsync, "/api/v2/resources/generic-rtp/{res}", drogon::Post);
            METHOD_LIST_END

            void PostResource(const drogon::HttpRequestPtr& req,
                              std::function<void(const drogon::HttpResponsePtr&)>&& callback,
                              std::string&& resource);

            drogon::Task<drogon::HttpResponsePtr> PostResourceAsync(const drogon::HttpRequestPtr req);

        private:
            void SendHttpSuccessResponse_(std::function<void(const drogon::HttpResponsePtr&)>&& callback);

        private:
            MediaServer::ServerSharedPtr_t m_pMediaServer;
        };
    }
}
