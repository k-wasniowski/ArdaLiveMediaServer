#pragma once

#include <memory>

namespace MediaServer
{
    namespace Rtp
    {
        class GenericRtpClient;
        using GenericRtpClientSharedPtr_t = std::shared_ptr<GenericRtpClient>;

        class GenericRtpClient
        {
        public:
            static GenericRtpClientSharedPtr_t Create();

            explicit GenericRtpClient();

            virtual ~GenericRtpClient();

        private:
        };
    }
}


