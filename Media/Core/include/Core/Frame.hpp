// Copyright 2023 The Arda Project Authors. All rights reserved.
//
// Copying, utilizing or revealing any part or entirety of this file
// and its contents without proper authorization is not allowed.

#pragma once

#include <vector>
#include <memory>

namespace Media
{
    namespace Core
    {
        class Frame;
        using FrameSharedPtr_t = std::shared_ptr<Frame>;

        class Frame
        {
        public:
            static FrameSharedPtr_t Create(std::vector<std::byte> data);

            explicit Frame(std::vector<std::byte> data);
            virtual ~Frame() = default;


        protected:
            std::vector<std::byte> m_data;
        };
    }
}