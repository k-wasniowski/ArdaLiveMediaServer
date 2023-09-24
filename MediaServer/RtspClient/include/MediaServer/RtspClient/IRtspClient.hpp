#pragma once

#include <memory>
#include <string>

namespace MediaServer
{
    namespace Rtsp
    {
        class IRtspClient
        {
        public:
            virtual ~IRtspClient() = default;

            virtual bool InitiateNewStream(std::string address, uint16_t port) = 0;
        };

        using IRtspClientSharedPtr_t = std::shared_ptr<IRtspClient>;
    }
}