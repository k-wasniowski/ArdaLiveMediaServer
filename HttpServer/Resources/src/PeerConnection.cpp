#include <Resources/PeerConnection.hpp>
#include <Resources/VideoEndpointRx.hpp>

#include <iostream>

namespace Http
{
    namespace WebRTC
    {
        class DataChannel;
        using DataChannelSharedPtr_t = std::shared_ptr<DataChannel>;

        class DataChannel : public std::enable_shared_from_this<DataChannel>
        {
        public:
            static DataChannelSharedPtr_t Create(std::shared_ptr<rtc::DataChannel> pRTCDataChannel)
            {
                auto pDataChannel = std::make_shared<DataChannel>(std::move(pRTCDataChannel));
                pDataChannel->Init_();
                return pDataChannel;
            }

            DataChannel(std::shared_ptr<rtc::DataChannel> pDataChannel)
                : m_pDataChannel(std::move(pDataChannel))
            {
                std::cout << "DataChannel Created" << std::endl;
            }

            ~DataChannel()
            {
                std::cout << "DataChannel Terminated" << std::endl;
            }

        protected:
            void Init_()
            {
                m_pDataChannel->onMessage([](rtc::message_variant message) { std::cout << "Message from data channel" << std::endl; });
                m_pDataChannel->onMessage([](rtc::binary message) { std::cout << "Binary message from data channel" << std::endl; },
                                          [](rtc::string message) { std::cout << "String message from data channel" << std::endl; });
                m_pDataChannel->onClosed(std::bind(&DataChannel::OnClosed_, shared_from_this()));
            }

            void OnClosed_()
            {
                std::cout << "Data channel closed" << std::endl;
            }

        private:
            std::shared_ptr<rtc::DataChannel> m_pDataChannel;
        };

        PeerConnectionSharedPtr_t PeerConnection::Create(std::shared_ptr<rtc::PeerConnection> pRTCPeerConnection,
                                                         std::function<void(std::shared_ptr<rtc::Track>)> onTrackCallback)
        {
            auto pPeerConnection = std::make_shared<PeerConnection>(std::move(pRTCPeerConnection), std::move(onTrackCallback));
            pPeerConnection->Init_();
            return pPeerConnection;
        }

        PeerConnection::PeerConnection(std::shared_ptr<rtc::PeerConnection> pPeerConnection,
                                       std::function<void(std::shared_ptr<rtc::Track>)> onTrackCallback)
            : m_pPeerConnection(std::move(pPeerConnection))
            , m_onTrackCallback(std::move(onTrackCallback))
        {
            std::cout << "PeerConnection Created" << std::endl;
        }

        void PeerConnection::Init_()
        {
            m_pPeerConnection->onDataChannel(std::bind(&PeerConnection::OnDataChannel_, shared_from_this(), std::placeholders::_1));
            m_pPeerConnection->onStateChange(std::bind(&PeerConnection::OnStateChange_, shared_from_this(), std::placeholders::_1));
            m_pPeerConnection->onSignalingStateChange(
                std::bind(&PeerConnection::OnSignalingStateChange_, shared_from_this(), std::placeholders::_1));
            m_pPeerConnection->onGatheringStateChange(
                std::bind(&PeerConnection::OnGatheringStateChange_, shared_from_this(), std::placeholders::_1));
            m_pPeerConnection->onTrack(std::bind(&PeerConnection::OnTrack_, shared_from_this(), std::placeholders::_1));
        }

        PeerConnection::~PeerConnection()
        {
            std::cout << "PeerConnection Terminated" << std::endl;
        }

        void PeerConnection::OnDataChannel_(std::shared_ptr<rtc::DataChannel> pRTCDataChannel)
        {
            std::cout << "Created data channel" << std::endl;
            DataChannel::Create(std::move(pRTCDataChannel));
        }

        void PeerConnection::OnSignalingStateChange_(rtc::PeerConnection::SignalingState signalingState)
        {
            std::cout << "Signaling state changed: " << signalingState << std::endl;
        }

        void PeerConnection::OnStateChange_(rtc::PeerConnection::State state)
        {
            std::cout << "State changed: " << state << std::endl;
        }

        void PeerConnection::OnGatheringStateChange_(rtc::PeerConnection::GatheringState gatheringState)
        {
            std::cout << "Gathering state changed: " << gatheringState << std::endl;
        }

        void PeerConnection::OnTrack_(std::shared_ptr<rtc::Track> pTrack)
        {
            std::cout << "Track received" << std::endl;
            if (!m_onTrackCallback)
            {
                std::cout << "Invalid on track callback" << std::endl;
                return;
            }

            std::invoke(m_onTrackCallback, std::move(pTrack));
        }

        void PeerConnection::InitiateSignaling(ISignalingHandlerUniquePtr_t pSignalingHandler, std::string message)
        {
            if (!pSignalingHandler)
            {
                std::cout << "Invalid signaling handler" << std::endl;
                return;
            }

            std::cout << "PeerConnection::InitiateSignaling" << std::endl;
            pSignalingHandler->InitiateSignaling(m_pPeerConnection, std::move(message));
        }
    }
}