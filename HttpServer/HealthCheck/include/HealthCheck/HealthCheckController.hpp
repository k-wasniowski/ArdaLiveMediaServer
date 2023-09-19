// Copyright 2023 The Arda Project Authors. All rights reserved.
//
// Copying, utilizing or revealing any part or entirety of this file
// and its contents without proper authorization is not allowed.

#pragma once

#include <drogon/HttpController.h>

#include <memory>

namespace Http
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
