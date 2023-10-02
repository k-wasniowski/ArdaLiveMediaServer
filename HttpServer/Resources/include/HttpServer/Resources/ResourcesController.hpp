#pragma once

#include <MediaServer/Server.hpp>

#include <drogon/HttpController.h>

#include <memory>

namespace HttpServer
{
    namespace Resources
    {
        class ResourcesController;
        using ResourcesControllerSharedPtr_t = std::shared_ptr<ResourcesController>;

        class ResourcesController : public drogon::HttpController<ResourcesController, false>
        {
        public:
            static ResourcesControllerSharedPtr_t Create(MediaServer::MediaManagerProxySharedPtr_t pMediaManagerProxy);

            ResourcesController(MediaServer::MediaManagerProxySharedPtr_t pMediaManagerProxy);
            ~ResourcesController() override;

            METHOD_LIST_BEGIN
            ADD_METHOD_TO(ResourcesController::GetResources, "/api/v1/resources", drogon::Get);
            METHOD_LIST_END

            drogon::Task<drogon::HttpResponsePtr> GetResources(const drogon::HttpRequestPtr pHttpRequest);

        private:
            MediaServer::MediaManagerProxySharedPtr_t m_pMediaManagerProxy;
        };
    }
}
