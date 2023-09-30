#pragma once

#include <Gondor/Execution/ExecutionContext.hpp>

// #include <MediaServer/
#include <coroutine>
#include <memory>
#include <optional>
#include <string>

template <typename T = void>
struct CallbackAwaiter
{
    bool await_ready() noexcept
    {
        return false;
    }

    const T& await_resume() const noexcept(false)
    {
        if (exception_)
            std::rethrow_exception(exception_);
        return result_.value();
    }

private:
    std::optional<T> result_;
    std::exception_ptr exception_{nullptr};

protected:
    void setException(const std::exception_ptr& e)
    {
        exception_ = e;
    }

    void setValue(const T& v)
    {
        result_.emplace(v);
    }

    void setValue(T&& v)
    {
        result_.emplace(std::move(v));
    }
};

namespace MediaServer
{
    namespace Rtp
    {
        class IGenericRtpClient
        {
        public:
            virtual ~IGenericRtpClient() = default;

            virtual bool
            InitiateNewSession(std::string ip, uint16_t port, std::string sessionDescription, std::function<void()> callback) = 0;
        };

        using IGenericRtpClientSharedPtr_t = std::shared_ptr<IGenericRtpClient>;

        class GenericRtpStreamAwaiter : public CallbackAwaiter<bool>
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
            {}

            void await_suspend(std::coroutine_handle<> handle)
            {
                auto pExecutionContext = m_pExecutionContext.lock();
                if (!pExecutionContext)
                {
                    setValue(false);
                    handle.resume();
                }

                auto task = std::bind(&MediaServer::Rtp::IGenericRtpClient::InitiateNewSession,
                                      m_pGenericRtpClient,
                                      m_ip,
                                      m_port,
                                      m_sessionDescription,
                                      [this, handle]() {
                                          setValue(true);
                                          handle.resume();
                                      });

                auto result = pExecutionContext->PostTask(task);
                if(!result)
                {
                    setValue(false);
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