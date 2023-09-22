// Copyright 2023 The Arda Project Authors. All rights reserved.
//
// Copying, utilizing or revealing any part or entirety of this file
// and its contents without proper authorization is not allowed.

#include <MediaServer/GenericRtpClient/GenericRtpClient.hpp>

namespace MediaServer
{
    namespace Rtp
    {
        GenericRtpClientSharedPtr_t GenericRtpClient::Create()
        {
            return std::make_shared<GenericRtpClient>();
        }

        GenericRtpClient::GenericRtpClient()
        {}

        GenericRtpClient::~GenericRtpClient()
        {}
    }
}
