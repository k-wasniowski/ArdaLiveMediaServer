#pragma once

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
            static GenericRtpControllerSharedPtr_t Create();

            GenericRtpController();
            ~GenericRtpController() override;

            METHOD_LIST_BEGIN
            ADD_METHOD_TO(GenericRtpController::PostResource, "/api/v1/resources/generic-rtp/{resource}", drogon::Post);
            METHOD_LIST_END

            void PostResource(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback, std::string&& resource);

        private:
        };
    }
}
