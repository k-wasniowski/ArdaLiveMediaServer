// Copyright 2023 The Arda Project Authors. All rights reserved.
//
// Copying, utilizing or revealing any part or entirety of this file
// and its contents without proper authorization is not allowed.

#pragma once

#include <Media/Core/MediaBuffer.hpp>

#include <memory>
#include <vector>

namespace Media
{
    namespace Core
    {
        class Frame;
        using FrameSharedPtr_t = std::shared_ptr<Frame>;

        class Frame
        {
        public:
            static FrameSharedPtr_t Create(MediaBufferSharedPtr_t pMediaBuffer);

            explicit Frame(MediaBufferSharedPtr_t pMediaBuffer);
            virtual ~Frame() = default;

        protected:
            MediaBufferSharedPtr_t m_pMediaBuffer;
        };
    }
}