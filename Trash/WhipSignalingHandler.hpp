#pragma once

#include "ISignalingHandler.hpp"

#include "drogon/drogon.h"
#include "rtc/rtc.hpp"

#include <functional>
#include <string>

namespace Http
{
    namespace WebRTC
    {
        class WhipSignalingHandler;
        using WhipSignalingHandlerUniquePtr_t = std::unique_ptr<WhipSignalingHandler>;

        class WhipSignalingHandler : public ISignalingHandler
        {
        public:
            static WhipSignalingHandlerUniquePtr_t Create(std::function<void(const drogon::HttpResponsePtr&)>&& callback);

            explicit WhipSignalingHandler(std::function<void(const drogon::HttpResponsePtr&)>&& callback);
            ~WhipSignalingHandler() override;

            void InitiateSignaling(std::shared_ptr<rtc::PeerConnection> pRTCPeerConnection, std::string message) override;

        private:
            void ReportError_();

        private:
            std::function<void(const drogon::HttpResponsePtr&)> m_callback;
        };
    }
}