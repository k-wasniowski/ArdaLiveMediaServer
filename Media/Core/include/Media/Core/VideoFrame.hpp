// Copyright 2023 The Arda Project Authors. All rights reserved.
//
// Copying, utilizing or revealing any part or entirety of this file
// and its contents without proper authorization is not allowed.

#pragma once

#include <Media/Core/Frame.hpp>

namespace Media
{
    namespace Core
    {
        class VideoFrame;
        using VideoFrameSharedPtr_t = std::shared_ptr<VideoFrame>;

        class VideoFrame : public Frame
        {
        public:
            static VideoFrameSharedPtr_t Create(MediaBufferSharedPtr_t pMediaBuffer);

            VideoFrame(MediaBufferSharedPtr_t pMediaBuffer);
            ~VideoFrame() override = default;
        };
    }
}