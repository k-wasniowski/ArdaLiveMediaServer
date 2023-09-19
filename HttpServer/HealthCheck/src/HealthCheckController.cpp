// Copyright 2023 The Arda Project Authors. All rights reserved.
//
// Copying, utilizing or revealing any part or entirety of this file
// and its contents without proper authorization is not allowed.

#include <HealthCheck/HealthCheckController.hpp>

#include <iostream>

namespace Http
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

        auto pHttpResponse = drogon::HttpResponse::newHttpResponse();
        pHttpResponse->setStatusCode(drogon::HttpStatusCode::k200OK);

        callback(pHttpResponse);
    }
}
