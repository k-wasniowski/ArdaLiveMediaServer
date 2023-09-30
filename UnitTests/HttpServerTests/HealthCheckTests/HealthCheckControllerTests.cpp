#include <HttpServer/HealthCheck/HealthCheckController.hpp>

#include <gtest/gtest.h>

TEST(HealthCheckTests, Creation)
{
    auto pHealthCheckController = HttpServer::HealthCheckController::Create();
    ASSERT_TRUE(pHealthCheckController != nullptr);
}

TEST(HealthCheckTests, NullptrRequest)
{
    auto pHealthCheckController = HttpServer::HealthCheckController::Create();
    ASSERT_TRUE(pHealthCheckController != nullptr);

    bool callbackCalled = false;

    pHealthCheckController->GetHealthCheck(nullptr, [&callbackCalled](const drogon::HttpResponsePtr& pHttpResponse) {
        ASSERT_TRUE(pHttpResponse != nullptr);
        ASSERT_EQ(pHttpResponse->statusCode(), drogon::HttpStatusCode::k500InternalServerError);
        callbackCalled = true;
    });

    ASSERT_TRUE(callbackCalled);
}

TEST(HealthCheckTests, ValidRequest)
{
    auto pHealthCheckController = HttpServer::HealthCheckController::Create();
    ASSERT_TRUE(pHealthCheckController != nullptr);

    bool callbackCalled = false;

    auto pHttpRequest = drogon::HttpRequest::newHttpRequest();

    pHealthCheckController->GetHealthCheck(pHttpRequest, [&callbackCalled](const drogon::HttpResponsePtr& pHttpResponse) {
        ASSERT_TRUE(pHttpResponse != nullptr);
        ASSERT_EQ(pHttpResponse->statusCode(), drogon::HttpStatusCode::k200OK);
        callbackCalled = true;
    });

    ASSERT_TRUE(callbackCalled);
}