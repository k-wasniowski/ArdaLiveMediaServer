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
                : m_pool{threadsCount}
                , m_executor{m_pool.executor()}
            {
                std::cout << "Creating ExecutionContext!" << std::endl;
            }

            ~Impl() {}

            void Run()
            {
                std::cout << "Running ExecutionContext!" << std::endl;
            }

            void Terminate()
            {
                std::cout << "Terminating ExecutionContext!" << std::endl;

                m_pool.join();
            }

            bool PostTask(std::function<void()> task)
            {
                if (!task)
                {
                    return false;
                }

                boost::asio::post(m_executor, task);

                return true;
            }

        private:
            boost::asio::thread_pool m_pool;
            boost::asio::executor m_executor;
        };

        ExecutionContextSharedPtr ExecutionContext::Create(uint32_t threadsCount)
        {
            return std::make_shared<ExecutionContext>(threadsCount);
        }

        ExecutionContext::ExecutionContext(uint32_t threadsCount)
            : m_pImpl{Impl::Create(threadsCount)}
        {}

        ExecutionContext::~ExecutionContext() {}

        void ExecutionContext::Run()
        {
            if (!m_pImpl)
            {
                return;
            }

            m_pImpl->Run();
        }

        void ExecutionContext::Terminate()
        {
            if (!m_pImpl)
            {
                return;
            }

            m_pImpl->Terminate();
        }

        bool ExecutionContext::PostTask(std::function<void()> task)
        {
            if (!m_pImpl)
            {
                return false;
            }

            return m_pImpl->PostTask(task);
        }
    }
}
