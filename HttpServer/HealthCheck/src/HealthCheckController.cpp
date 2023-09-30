#include <HttpServer/HealthCheck/HealthCheckController.hpp>

#include <iostream>

namespace HttpServer
{
    HealthCheckControllerSharedPtr_t HealthCheckController::Create()
    {
        return std::make_shared<HealthCheckController>();
    }

    HealthCheckController::HealthCheckController()
    {
        std::cout << "HealthCheckController::HealthCheckController" << std::endl;
    }

    HealthCheckController::~HealthCheckController()
    {
        std::cout << "HealthCheckController::~HealthCheckController" << std::endl;
    }

    void HealthCheckController::GetHealthCheck(const drogon::HttpRequestPtr& pHttpRequest,
                                               std::function<void(const drogon::HttpResponsePtr&)>&& callback)
    {
        std::cout << "HealthCheckController::GetHealthCheck" << std::endl;
        if (!pHttpRequest)
        {
            std::cout << "HealthCheckController::GetHealthCheck - pHttpRequest is nullptr" << std::endl;

            auto pHttpResponse = drogon::HttpResponse::newHttpResponse();
            pHttpResponse->setStatusCode(drogon::HttpStatusCode::k500InternalServerError);

            callback(pHttpResponse);
            return;
        }

        auto pHttpResponse = drogon::HttpResponse::newHttpResponse();
        pHttpResponse->setStatusCode(drogon::HttpStatusCode::k200OK);

        callback(pHttpResponse);
    }
}
