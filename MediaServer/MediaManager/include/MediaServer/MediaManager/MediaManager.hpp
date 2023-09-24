#pragma once

#include <MediaServer/MediaManager/MediaResource.hpp>

#include <list>
#include <memory>

namespace MediaServer
{
    class MediaManager;
    using MediaManagerSharedPtr_t = std::shared_ptr<MediaManager>;

    class MediaManager
    {
    public:
        static MediaManagerSharedPtr_t Create();

        MediaManager();
        ~MediaManager();

        void AddMediaResource(MediaResourceSharedPtr_t pMediaResource);
        MediaResourceSharedPtr_t GetMediaResource(std::string resource);
        void RemoveMediaResource(MediaResourceSharedPtr_t pMediaResource);

    private:
        std::list<MediaResourceSharedPtr_t> m_mediaResources;
    };
}
