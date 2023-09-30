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

        void GenericRtpController::PostResource(const drogon::HttpRequestPtr& pHttpRequest,
                                                std::function<void(const drogon::HttpResponsePtr&)>&& callback,
                                                std::string&& resource)
        {
            //            std::cout << "GenericRtpController::PostResource - " << resource << std::endl;
            //
            //            if (!pHttpRequest)
            //            {
            //                auto pHttpResponse = drogon::HttpResponse::newHttpResponse();
            //                pHttpResponse->setStatusCode(drogon::HttpStatusCode::k500InternalServerError);
            //
            //                callback(pHttpResponse);
            //
            //                return;
            //            }
            //
            //            auto requestBody = pHttpRequest->body();
            //            if (requestBody.empty())
            //            {
            //                auto pHttpResponse = drogon::HttpResponse::newHttpResponse();
            //                pHttpResponse->setStatusCode(drogon::HttpStatusCode::k400BadRequest);
            //
            //                callback(pHttpResponse);
            //
            //                return;
            //            }
            //
            //            try
            //            {
            //                nlohmann::json request = nlohmann::json::parse(requestBody);
            //
            //                std::string address = request["address"];
            //                uint16_t port = request["port"];
            //                std::string sdp = request["sdp"];
            //
            //                auto pGenericRtpClient = m_pMediaServer->MakeGenericRtpClient();
            //                if (!pGenericRtpClient)
            //                {
            //                    auto pHttpResponse = drogon::HttpResponse::newHttpResponse();
            //                    pHttpResponse->setStatusCode(drogon::HttpStatusCode::k500InternalServerError);
            //
            //                    callback(pHttpResponse);
            //
            //                    return;
            //                }
            //
            //                pGenericRtpClient->InitiateNewSession(address, port, sdp);
            //
            //                SendHttpSuccessResponse_(std::move(callback));
            //            }
            //            catch (const std::exception& e)
            //            {
            //                auto pHttpResponse = drogon::HttpResponse::newHttpResponse();
            //                pHttpResponse->setStatusCode(drogon::HttpStatusCode::k400BadRequest);
            //
            //                callback(pHttpResponse);
            //            }
        }

        void GenericRtpController::SendHttpSuccessResponse_(std::function<void(const drogon::HttpResponsePtr&)>&& callback)
        {
            auto pHttpResponse = drogon::HttpResponse::newHttpResponse();
            pHttpResponse->setStatusCode(drogon::HttpStatusCode::k200OK);

            callback(pHttpResponse);
        }

        drogon::Task<drogon::HttpResponsePtr> GenericRtpController::PostResourceAsync(const drogon::HttpRequestPtr pHttpRequest)
        {
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

            bool worked = co_await pGenericRtpClient->Initiate(address, port, sdp);
            if (worked)
            {
                std::cout << "Success" << std::endl;
            }
            else
            {
                std::cout << "Failure" << std::endl;
            }

            co_return drogon::HttpResponse::newHttpResponse();
        }

        //        drogon::AsyncTask GenericRtpController::PostResourceAsync(const drogon::HttpRequestPtr& req, std::function<void(const
        //        drogon::HttpResponsePtr&)>&& callback, std::string res)
        //        {
        //            auto pResponsed = drogon::HttpResponse::newHttpResponse();
        //            callback(pResponsed);
        //        }
    }
}