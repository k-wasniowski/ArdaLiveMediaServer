#include <HttpServer/Resources/ResourcesController.hpp>

namespace HttpServer
{
    namespace Resources
    {
        ResourcesControllerSharedPtr_t ResourcesController::Create(MediaServer::MediaManagerProxySharedPtr_t pMediaManagerProxy)
        {
            return std::make_shared<ResourcesController>(pMediaManagerProxy);
        }

        ResourcesController::ResourcesController(MediaServer::MediaManagerProxySharedPtr_t pMediaManagerProxy)
            : m_pMediaManagerProxy{pMediaManagerProxy}
        {}

        ResourcesController::~ResourcesController() {}

        drogon::Task<drogon::HttpResponsePtr> ResourcesController::GetResources(const drogon::HttpRequestPtr pHttpRequest)
        {
            co_return drogon::HttpResponse::newHttpResponse();
        }
    }
}