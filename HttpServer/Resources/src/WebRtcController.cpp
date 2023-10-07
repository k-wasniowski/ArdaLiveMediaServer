#include <HttpServer/Resources/WebRtcController.hpp>

#include <MediaServer/MediaManager/MediaResource.hpp>

#include <rtc/rtc.hpp>

#include <memory>

namespace HttpServer
{
    namespace Resources
    {
        WebRtcControllerSharedPtr_t WebRtcController::Create(MediaServer::MediaManagerSharedPtr_t pMediaManager)
        {
            return std::make_shared<WebRtcController>(pMediaManager);
        }

        WebRtcController::WebRtcController(MediaServer::MediaManagerSharedPtr_t pMediaManager)
            : m_pMediaManager{std::move(pMediaManager)}
        {
            std::cout << "Creating WebRtcController" << std::endl;
        }

        void WebRtcController::PostResource(const drogon::HttpRequestPtr& req,
                                            std::function<void(const drogon::HttpResponsePtr&)>&& callback,
                                            std::string&& resource)
        {
            auto pHttpResponse = drogon::HttpResponse::newHttpResponse();
            pHttpResponse->setStatusCode(drogon::HttpStatusCode::k501NotImplemented);

            rtc::Configuration config;
            config.iceServers.emplace_back("stun:stun.l.google.com:19302");

            //auto pPeerConnection = std::make_shared<rtc::PeerConnection>(config);



            callback(pHttpResponse);
        }

        void WebRtcController::GetResource(const drogon::HttpRequestPtr& req,
                                           std::function<void(const drogon::HttpResponsePtr&)>&& callback,
                                           std::string&& resource)
        {
            auto pHttpResponse = drogon::HttpResponse::newHttpResponse();
            pHttpResponse->setStatusCode(drogon::HttpStatusCode::k501NotImplemented);

            callback(pHttpResponse);
        }
    }

}