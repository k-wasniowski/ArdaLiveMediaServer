#pragma once

#include <vector>
#include <memory>
#include <string>

namespace MediaServer
{
    class IMediaObserver
    {
    public:
        virtual ~IMediaObserver() = default;

        virtual void OnFrame(std::vector<std::byte> frame) = 0;
    };

    using MediaObserverSharedPtr_t = std::shared_ptr<IMediaObserver>;

    class IMediaTrack
    {
    public:
        virtual ~IMediaTrack() = default;

        virtual std::string Name() const = 0;

        virtual void Attach(MediaObserverSharedPtr_t pMediaObserver) = 0;
    };

    using IMediaTrackSharedPtr_t = std::shared_ptr<IMediaTrack>;
}