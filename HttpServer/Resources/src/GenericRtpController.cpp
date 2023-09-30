#include <HttpServer/Resources/GenericRtpController.hpp>

#include <iostream>

namespace HttpServer
{
    namespace Resources
    {
        GenericRtpControllerSharedPtr_t GenericRtpController::Create(MediaServer::MediaManagerSharedPtr_t pMediaManager)
        {
            return std::make_shared<GenericRtpController>(pMediaManager);
        }

        GenericRtpController::GenericRtpController(MediaServer::MediaManagerSharedPtr_t pMediaManager)
            : m_pMediaManager{std::move(pMediaManager)}
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
            std::cout << "GenericRtpController::PostResource - " << resource << std::endl;

            auto pMediaResource = m_pMediaManager->GetMediaResource(resource);
            if (!pMediaResource)
            {
                pMediaResource = MediaServer::MediaResource::Create(std::move(resource));
                m_pMediaManager->AddMediaResource(pMediaResource);
            }

            SendHttpSuccessResponse_(std::move(callback));
        }

        void GenericRtpController::SendHttpSuccessResponse_(std::function<void(const drogon::HttpResponsePtr&)>&& callback)
        {
            auto pHttpResponse = drogon::HttpResponse::newHttpResponse();
            pHttpResponse->setStatusCode(drogon::HttpStatusCode::k200OK);

            callback(pHttpResponse);
        }
    }
}