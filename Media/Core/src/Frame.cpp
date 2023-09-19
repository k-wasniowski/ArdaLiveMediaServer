// Copyright 2023 The Arda Project Authors. All rights reserved.
//
// Copying, utilizing or revealing any part or entirety of this file
// and its contents without proper authorization is not allowed.

#include <Core/Frame.hpp>

namespace Media
{
    namespace Core
    {
        FrameSharedPtr_t Frame::Create(std::vector<std::byte> data)
        {
            return std::make_shared<Frame>(std::move(data));
        }

        Frame::Frame(std::vector<std::byte> data)
            : m_data{std::move(data)}
        {}
    }
}