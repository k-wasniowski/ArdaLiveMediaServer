#pragma once

#include <Gondor/Execution/CallbackAwaiter.hpp>
#include <Gondor/Execution/ExecutionContext.hpp>

#include <MediaServer/MediaManager/IMediaTrack.hpp>

#include <coroutine>
#include <iostream>
#include <memory>
#include <optional>
#include <string>

namespace MediaServer
{
    namespace Rtp
    {
        class IGenericRtpClient
        {
        public:
            virtual ~IGenericRtpClient() = default;

            virtual bool InitiateNewSession(std::string ip,
                                            uint16_t port,
                                            std::string sessionDescription,
                                            std::function<void(IMediaTrackSharedPtr_t pMediaTrack)> callback) = 0;
        };

        using IGenericRtpClientSharedPtr_t = std::shared_ptr<IGenericRtpClient>;

        class GenericRtpStreamAwaiter : public Gondor::Execution::CallbackAwaiter<IMediaTrackSharedPtr_t>
        {
        public:
            GenericRtpStreamAwaiter(Gondor::Execution::ExecutionContextWeakPtr pExecutionContext,
                                    IGenericRtpClientSharedPtr_t pGenericRtpClient,
                                    std::string ip,
                                    uint16_t port,
                                    std::string sessionDescription)
                : m_pExecutionContext{pExecutionContext}
                , m_pGenericRtpClient{pGenericRtpClient}
                , m_ip{ip}
                , m_port{port}
                , m_sessionDescription{sessionDescription}
            {
                std::cout << "GenericRtpStreamAwaiter::GenericRtpStreamAwaiter()" << std::endl;
            }

            ~GenericRtpStreamAwaiter() override
            {
                std::cout << "GenericRtpStreamAwaiter::~GenericRtpStreamAwaiter()" << std::endl;
            }

            void await_suspend(std::coroutine_handle<> handle)
            {
                auto pExecutionContext = m_pExecutionContext.lock();
                if (!pExecutionContext)
                {
                    SetValue(nullptr);
                    handle.resume();
                }

                auto task = std::bind(&MediaServer::Rtp::IGenericRtpClient::InitiateNewSession,
                                      m_pGenericRtpClient,
                                      m_ip,
                                      m_port,
                                      m_sessionDescription,
                                      [this, handle](IMediaTrackSharedPtr_t pMediaTrack) -> void {
                                          SetValue(pMediaTrack);
                                          handle.resume();
                                      });

                auto result = pExecutionContext->PostTask(task);
                if (!result)
                {
                    SetValue(nullptr);
                    handle.resume();
                }
            }

        private:
            Gondor::Execution::ExecutionContextWeakPtr m_pExecutionContext;
            IGenericRtpClientSharedPtr_t m_pGenericRtpClient;
            std::string m_ip;
            uint16_t m_port;
            std::string m_sessionDescription;
        };

        class IGenericRtpClientProxy
        {
        public:
            virtual ~IGenericRtpClientProxy() = default;

            virtual GenericRtpStreamAwaiter Initiate(std::string ip, uint16_t port, std::string sessionDescription) = 0;
        };

        using IGenericRtpClientProxySharedPtr_t = std::shared_ptr<IGenericRtpClientProxy>;
    }
}