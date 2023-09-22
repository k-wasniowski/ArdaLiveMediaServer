// Copyright 2023 The Arda Project Authors. All rights reserved.
//
// Copying, utilizing or revealing any part or entirety of this file
// and its contents without proper authorization is not allowed.

#pragma once

#include <memory>
#include <vector>

namespace Media
{
    namespace Core
    {
        class MediaBuffer;
        using MediaBufferSharedPtr_t = std::shared_ptr<MediaBuffer>;

        class MediaBuffer
        {
        public:
            static MediaBufferSharedPtr_t Create(std::vector<std::byte> data);

            explicit MediaBuffer(std::vector<std::byte> data);
            virtual ~MediaBuffer() = default;

        private:
            std::vector<std::byte> m_data;
        };
    }
}