#include <HttpServer/Resources/GenericRtpController.hpp>

#include <iostream>

namespace HttpServer
{
    namespace Resources
    {
        GenericRtpControllerSharedPtr_t GenericRtpController::Create()
        {
            return std::make_shared<GenericRtpController>();
        }

        GenericRtpController::GenericRtpController()
        {
            std::cout << "Creating GenericRtpController" << std::endl;
        }

        GenericRtpController::~GenericRtpController()
        {
            std::cout << "Terminating GenericRtpController" << std::endl;
        }

        void GenericRtpController::PostResource(const drogon::HttpRequestPtr& pHttpRequest,
                                                std::function<void(const drogon::HttpResponsePtr&)>&& callback,
                                                std::string&& resource)
        {
            std::cout << "GenericRtpController::PostResource" << std::endl;



            auto pHttpResponse = drogon::HttpResponse::newHttpResponse();
            pHttpResponse->setStatusCode(drogon::HttpStatusCode::k200OK);

            callback(pHttpResponse);
        }
    }
}