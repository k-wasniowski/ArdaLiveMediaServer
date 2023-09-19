// Copyright 2023 The Arda Project Authors. All rights reserved.
//
// Copying, utilizing or revealing any part or entirety of this file
// and its contents without proper authorization is not allowed.

#pragma once

#include <Resources/IPeerConnection.hpp>
#include <Resources/ISignalingHandler.hpp>

#include <rtc/rtc.hpp>

#include <memory>

namespace Http
{
    namespace WebRTC
    {
        class PeerConnection;
        using PeerConnectionSharedPtr_t = std::shared_ptr<PeerConnection>;

        class PeerConnection
            : public IPeerConnection
            , public std::enable_shared_from_this<PeerConnection>
        {
        public:
            static PeerConnectionSharedPtr_t Create(std::shared_ptr<rtc::PeerConnection> pRTCPeerConnection,
                                                    std::function<void(std::shared_ptr<rtc::Track>)> onTrackCallback);

            explicit PeerConnection(std::shared_ptr<rtc::PeerConnection> pPeerConnection,
                                    std::function<void(std::shared_ptr<rtc::Track>)> onTrackCallback);

            void InitiateSignaling(ISignalingHandlerUniquePtr_t pSignalingHandler, std::string message) override;

            ~PeerConnection() override;

        protected:
            void Init_();

            void OnDataChannel_(std::shared_ptr<rtc::DataChannel> pRTCDataChannel);

            void OnSignalingStateChange_(rtc::PeerConnection::SignalingState signalingState);

            void OnStateChange_(rtc::PeerConnection::State state);

            void OnGatheringStateChange_(rtc::PeerConnection::GatheringState gatheringState);

            void OnTrack_(std::shared_ptr<rtc::Track> pTrack);

        private:
            std::shared_ptr<rtc::PeerConnection> m_pPeerConnection;
            std::function<void(std::shared_ptr<rtc::Track>)> m_onTrackCallback;
        };
    }
}
