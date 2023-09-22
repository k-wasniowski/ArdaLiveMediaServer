// Copyright 2023 The Arda Project Authors. All rights reserved.
//
// Copying, utilizing or revealing any part or entirety of this file
// and its contents without proper authorization is not allowed.

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


