// Copyright 2023 The Arda Project Authors. All rights reserved.
//
// Copying, utilizing or revealing any part or entirety of this file
// and its contents without proper authorization is not allowed.

#pragma once

#include <MediaServer/MediaManager/IMediaTrack.hpp>

#include <string>
#include <memory>
#include <vector>

namespace MediaServer
{
    class MediaResource;
    using MediaResourceSharedPtr_t = std::shared_ptr<MediaResource>;

    class MediaResource
    {
    public:
        static MediaResourceSharedPtr_t Create(std::string resourceName);

        explicit MediaResource(std::string resourceName);
        ~MediaResource();

        [[nodiscard]] inline std::string ResourceName() const { return m_resourceName; }

        void AddTrack(std::shared_ptr<IMediaTrack> pMediaTrack);

        [[nodiscard]] std::shared_ptr<IMediaTrack> GetTrack(std::string trackName) { return m_mediaTracks[0]; }

    private:
        std::string m_resourceName;
        std::vector<std::shared_ptr<IMediaTrack>> m_mediaTracks;
    };
}
