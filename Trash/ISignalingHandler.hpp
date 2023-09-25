#pragma once

#include "rtc/rtc.hpp"

#include <string>
#include <memory>

namespace Http
{
    namespace WebRTC
    {
        class ISignalingHandler
        {
        public:
            virtual ~ISignalingHandler() = default;

            virtual void InitiateSignaling(std::shared_ptr<rtc::PeerConnection> pRTCPeerConnection, std::string message) = 0;
        };

        using ISignalingHandlerUniquePtr_t = std::unique_ptr<ISignalingHandler>;
    }
}