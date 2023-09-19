// Copyright 2023 The Arda Project Authors. All rights reserved.
//
// Copying, utilizing or revealing any part or entirety of this file
// and its contents without proper authorization is not allowed.

#include <Core/VideoFrame.hpp>

namespace Media
{
    namespace Core
    {
        VideoFrameSharedPtr_t VideoFrame::Create(std::vector<std::byte> data)
        {
            return std::make_shared<VideoFrame>(std::move(data));
        }

        VideoFrame::VideoFrame(std::vector<std::byte> data)
            : Frame(std::move(data))
        {}
    }
}