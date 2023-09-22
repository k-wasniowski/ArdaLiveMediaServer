// Copyright 2023 The Arda Project Authors. All rights reserved.
//
// Copying, utilizing or revealing any part or entirety of this file
// and its contents without proper authorization is not allowed.

#include <Media/Core/MediaBuffer.hpp>

namespace Media
{
    namespace Core
    {
        MediaBufferSharedPtr_t MediaBuffer::Create(std::vector<std::byte> data)
        {
            return std::make_shared<MediaBuffer>(std::move(data));
        }

        MediaBuffer::MediaBuffer(std::vector<std::byte> data)
            : m_data{std::move(data)}
        {}
    }
}