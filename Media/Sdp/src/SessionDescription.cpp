// Copyright 2023 The Arda Project Authors. All rights reserved.
//
// Copying, utilizing or revealing any part or entirety of this file
// and its contents without proper authorization is not allowed.

#include <Media/Sdp/SessionDescription.hpp>

namespace Media
{
    namespace Sdp
    {
        class SessionDescription::Impl
        {
        public:
            Impl()
            {
            }

            virtual ~Impl()
            {
            }
        };

        SessionDescription::SessionDescription()
            : m_pImpl(std::make_unique<Impl>())
        {
        }

        SessionDescription::~SessionDescription()
        {
        }

        SessionDescriptionSharedPtr_t SessionDescription::Create()
        {
            return std::make_shared<SessionDescription>();
        }
    }
}