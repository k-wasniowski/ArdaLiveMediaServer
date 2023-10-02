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

        drogon::Task<drogon::HttpResponsePtr> GenericRtpController::PostResource(const drogon::HttpRequestPtr pHttpRequest,
                                                                                 std::string resourceName)
        {
            auto pHttpResponse = drogon::HttpResponse::newHttpResponse();

            auto pGenericRtpClient = m_pMediaServer->MakeGenericRtpClient();
            if (!pGenericRtpClient)
            {
                std::cout << "Failure - Generic RTP Client is nullptr" << std::endl;

                auto pResponse = drogon::HttpResponse::newHttpResponse();
                pResponse->setStatusCode(drogon::HttpStatusCode::k500InternalServerError);
                co_return pResponse;
            }

            auto pMediaManager = m_pMediaServer->MakeMediaManager();
            if (!pMediaManager)
            {
                std::cout << "Failure - Media Manager is nullptr" << std::endl;
                pHttpResponse->setStatusCode(drogon::HttpStatusCode::k500InternalServerError);

                co_return pHttpResponse;
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

            auto pMediaResource = co_await pMediaManager->GetMediaResource(resourceName);
            if(pMediaResource)
            {
                auto pMediaResourceLock = pMediaResource->Lock();

                pMediaResourceLock->AddTrack(pMediaTrack);
            }
            else
            {
                auto pNewMediaResource = MediaServer::MediaResource::Create(resourceName);
                {
                    auto pLockedNewMediaResource = pNewMediaResource->Lock();
                    pLockedNewMediaResource->AddTrack(pMediaTrack);
                }

                co_await pMediaManager->AddMediaResource(pNewMediaResource);
            }
//            if (!pMediaResource)
//            {
//
//                pNewMediaResource->AddTrack(pMediaTrack);
//
//                co_await pMediaManager->AddMediaResource(pNewMediaResource);
//            }
//            else
//            {
//                pMediaResource->AddTrack(pMediaTrack);
//            }

            std::cout << "Success" << std::endl;
            pHttpResponse->setStatusCode(drogon::HttpStatusCode::k200OK);

            co_return pHttpResponse;
        }

        drogon::Task<drogon::HttpResponsePtr> GenericRtpController::GetResources(const drogon::HttpRequestPtr pHttpRequest)
        {
            auto pHttpResponse = drogon::HttpResponse::newHttpResponse();

            auto pMediaManager = m_pMediaServer->MakeMediaManager();
            if (!pMediaManager)
            {
                std::cout << "Failure - Media Manager is nullptr" << std::endl;
                pHttpResponse->setStatusCode(drogon::HttpStatusCode::k500InternalServerError);

                co_return pHttpResponse;
            }

            auto mediaResources = co_await pMediaManager->GetMediaResources();
            if(mediaResources.empty())
            {
                pHttpResponse->setStatusCode(drogon::HttpStatusCode::k204NoContent);

                co_return pHttpResponse;
            }

            std::cout << "Success" << std::endl;
            pHttpResponse->setStatusCode(drogon::HttpStatusCode::k200OK);

            co_return pHttpResponse;
        }
    }
}