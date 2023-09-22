// Copyright 2023 The Arda Project Authors. All rights reserved.
//
// Copying, utilizing or revealing any part or entirety of this file
// and its contents without proper authorization is not allowed.

#pragma once

#include <memory>


namespace Media
{
    namespace Sdp
    {
        class SessionDescription;
        using SessionDescriptionSharedPtr_t = std::shared_ptr<SessionDescription>;

        class SessionDescription
        {
        public:
            static SessionDescriptionSharedPtr_t Create();

            explicit SessionDescription();

            virtual ~SessionDescription();

        private:
            class Impl;
            std::unique_ptr<Impl> m_pImpl;
        };
    }
}
