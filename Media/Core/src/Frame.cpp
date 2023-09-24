#include <Media/Core/Frame.hpp>

namespace Media
{
    namespace Core
    {
        FrameSharedPtr_t Frame::Create(MediaBufferSharedPtr_t pMediaBuffer)
        {
            return std::make_shared<Frame>(std::move(pMediaBuffer));
        }

        Frame::Frame(MediaBufferSharedPtr_t pMediaBuffer)
            : m_pMediaBuffer{std::move(pMediaBuffer)}
        {}
    }
}