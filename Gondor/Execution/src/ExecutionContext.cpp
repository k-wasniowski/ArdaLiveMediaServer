#include <Gondor/Execution/ExecutionContext.hpp>

#include <boost/asio.hpp>

#include <iostream>

namespace Gondor
{
    namespace Execution
    {
        class ExecutionContext::Impl
        {
        public:
            static std::unique_ptr<Impl> Create(uint32_t threadsCount)
            {
                return std::make_unique<Impl>(threadsCount);
            }

            Impl(uint32_t threadsCount)
                : m_pool{1}
                , m_executor{m_pool.executor()}
            {
                std::cout << "Creating ExecutionContext!" << std::endl;
            }

            ~Impl() {}

        private:
            boost::asio::thread_pool m_pool;
            boost::asio::executor m_executor;
        };

        ExecutionContext::ExecutionContext(uint32_t threadsCount)
            : m_pImpl{Impl::Create(threadsCount)}
        {}

        ExecutionContext::~ExecutionContext() {}
    }
}
