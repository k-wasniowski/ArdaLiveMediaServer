#include <Media/Core/VideoFrame.hpp>

namespace Media
{
    namespace Core
    {
        VideoFrameSharedPtr_t VideoFrame::Create(MediaBufferSharedPtr_t pMediaBuffer)
        {
            return std::make_shared<VideoFrame>(std::move(pMediaBuffer));
        }

        VideoFrame::VideoFrame(MediaBufferSharedPtr_t pMediaBuffer)
            : Frame(std::move(pMediaBuffer))
        {}
    }
}