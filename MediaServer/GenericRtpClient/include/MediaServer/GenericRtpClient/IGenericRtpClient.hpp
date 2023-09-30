#pragma once

#include <memory>
#include <string>

namespace MediaServer
{
    namespace Rtp
    {
        class IGenericRtpClient
        {
        public:
            virtual ~IGenericRtpClient() = default;

            virtual bool InitiateNewSession(std::string ip, uint16_t port, std::string sessionDescription) = 0;
        };

        using IGenericRtpClientSharedPtr_t = std::shared_ptr<IGenericRtpClient>;
    }
}