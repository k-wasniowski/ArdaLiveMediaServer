#pragma once

#include <MediaServer/GenericRtpClient/IGenericRtpClient.hpp>

#include <MediaServer/GenericRtpClient/GenericRtpClient.hpp>

#include <Gondor/Execution/ExecutionContext.hpp>

#include <memory>

namespace MediaServer
{
    class GenericRtpClientProxy;
    using GenericRtpClientProxySharedPtr_t = std::shared_ptr<GenericRtpClientProxy>;

    class GenericRtpClientProxy : public MediaServer::Rtp::IGenericRtpClientProxy
    {
    public:
        static GenericRtpClientProxySharedPtr_t Create(Gondor::Execution::ExecutionContextWeakPtr pExecutionContext,
                                                       MediaServer::Rtp::GenericRtpClientSharedPtr_t pGenericRtpClient);

        GenericRtpClientProxy(Gondor::Execution::ExecutionContextWeakPtr pExecutionContext,
                              MediaServer::Rtp::GenericRtpClientSharedPtr_t pGenericRtpClient);
        ~GenericRtpClientProxy();

        bool InitiateNewSession(std::string ip, uint16_t port, std::string sessionDescription);

        MediaServer::Rtp::GenericRtpStreamAwaiter Initiate(std::string ip, uint16_t port, std::string sessionDescription) override;

    private:
        Gondor::Execution::ExecutionContextWeakPtr m_pExecutionContext;
        MediaServer::Rtp::GenericRtpClientSharedPtr_t m_pGenericRtpClient;
    };
}