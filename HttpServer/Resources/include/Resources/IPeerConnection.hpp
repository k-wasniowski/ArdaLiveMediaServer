// Copyright 2023 The Arda Project Authors. All rights reserved.
//
// Copying, utilizing or revealing any part or entirety of this file
// and its contents without proper authorization is not allowed.

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