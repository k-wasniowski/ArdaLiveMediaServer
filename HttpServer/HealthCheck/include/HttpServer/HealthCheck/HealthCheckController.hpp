#pragma once

#include <drogon/HttpController.h>

#include <memory>

namespace HttpServer
{
    class HealthCheckController;
    using HealthCheckControllerSharedPtr_t = std::shared_ptr<HealthCheckController>;

    class HealthCheckController : public drogon::HttpController<HealthCheckController, false>
    {
    public:
        static HealthCheckControllerSharedPtr_t Create();

        HealthCheckController();
        ~HealthCheckController() override;

        METHOD_LIST_BEGIN
        ADD_METHOD_TO(HealthCheckController::GetHealthCheck, "/api/v1/HealthCheck", drogon::Get);
        METHOD_LIST_END

        void GetHealthCheck(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback);
    };
}
