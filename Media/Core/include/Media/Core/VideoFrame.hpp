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