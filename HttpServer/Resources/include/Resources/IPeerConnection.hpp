#pragma once

#include <Resources/ISignalingHandler.hpp>

namespace Http
{
    namespace WebRTC
    {
        class IPeerConnection
        {
        public:
            virtual ~IPeerConnection() = default;

            virtual void InitiateSignaling(ISignalingHandlerUniquePtr_t pSignalingHandler, std::string message) = 0;
        };
    }
}