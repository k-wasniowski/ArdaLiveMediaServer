#include <Media/Core/MediaBuffer.hpp>

#include <gtest/gtest.h>

TEST(MediaBufferTests, Creation)
{
    std::vector<std::byte> data{};
    auto pMediaBuffer = Media::Core::MediaBuffer::Create(data);
    ASSERT_TRUE(pMediaBuffer != nullptr);
}