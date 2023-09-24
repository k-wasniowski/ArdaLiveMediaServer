#pragma once

#include <Resources/ISignalingHandler.hpp>

#include <drogon/drogon.h>
#include <rtc/rtc.hpp>

#include <functional>
#include <string>

namespace Http
{
    namespace WebRTC
    {
        class WhepSignalingHandler;
        using WhepSignalingHandlerUniquePtr_t = std::unique_ptr<WhepSignalingHandler>;

        class WhepSignalingHandler : public ISignalingHandler
        {
        public:
            static WhepSignalingHandlerUniquePtr_t Create(std::function<void(const drogon::HttpResponsePtr&)>&& callback);

            explicit WhepSignalingHandler(std::function<void(const drogon::HttpResponsePtr&)>&& callback);
            ~WhepSignalingHandler() override;

            void InitiateSignaling(std::shared_ptr<rtc::PeerConnection> pRTCPeerConnection, std::string message) override;

        private:
            void ReportError_();

        private:
            std::function<void(const drogon::HttpResponsePtr&)> m_callback;
        };
    }
}