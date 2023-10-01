#include <HttpServer/Resources/GenericRtpController.hpp>

#include <nlohmann/json.hpp>

#include <iostream>

namespace HttpServer
{
    namespace Resources
    {
        GenericRtpControllerSharedPtr_t GenericRtpController::Create(MediaServer::ServerSharedPtr_t pMediaServer)
        {
            return std::make_shared<GenericRtpController>(pMediaServer);
        }

        GenericRtpController::GenericRtpController(MediaServer::ServerSharedPtr_t pMediaServer)
            : m_pMediaServer{std::move(pMediaServer)}
        {
            std::cout << "Creating GenericRtpController" << std::endl;
        }

        GenericRtpController::~GenericRtpController()
        {
            std::cout << "Terminating GenericRtpController" << std::endl;
        }

        drogon::Task<drogon::HttpResponsePtr> GenericRtpController::PostResource(const drogon::HttpRequestPtr pHttpRequest)
        {
            auto pHttpResponse = drogon::HttpResponse::newHttpResponse();

            auto pGenericRtpClient = m_pMediaServer->MakeGenericRtpClient();
            if (!pGenericRtpClient)
            {
                auto pResponse = drogon::HttpResponse::newHttpResponse();
                pResponse->setStatusCode(drogon::HttpStatusCode::k500InternalServerError);
                co_return pResponse;
            }

            auto requestBody = pHttpRequest->body();

            nlohmann::json request = nlohmann::json::parse(requestBody);

            std::string address = request["address"];
            uint16_t port = request["port"];
            std::string sdp = request["sdp"];

            auto pMediaTrack = co_await pGenericRtpClient->Initiate(address, port, sdp);
            if (!pMediaTrack)
            {
                std::cout << "Failure" << std::endl;
                pHttpResponse->setStatusCode(drogon::HttpStatusCode::k500InternalServerError);

                co_return pHttpResponse;
            }

            std::cout << "Success" << std::endl;
            pHttpResponse->setStatusCode(drogon::HttpStatusCode::k200OK);

            co_return pHttpResponse;
        }

        void GenericRtpController::SendHttpSuccessResponse_(std::function<void(const drogon::HttpResponsePtr&)>&& callback)
        {
            auto pHttpResponse = drogon::HttpResponse::newHttpResponse();
            pHttpResponse->setStatusCode(drogon::HttpStatusCode::k200OK);

            callback(pHttpResponse);
        }
    }
}