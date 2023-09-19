// Copyright 2023 The Arda Project Authors. All rights reserved.
//
// Copying, utilizing or revealing any part or entirety of this file
// and its contents without proper authorization is not allowed.

#include <Gondor/Execution/TasksContext.hpp>
#include <Gondor/Execution/TasksExecutor.hpp>

#include <iostream>
#include <thread>

namespace Gondor
{
    namespace Execution
    {
        class TasksContext::Impl
        {
        public:
            static std::unique_ptr<Impl> Create(TasksExecutorSharedPtr_t pTasksExecutor)
            {
                return std::make_unique<Impl>(std::move(pTasksExecutor));
            }

            explicit Impl(TasksExecutorSharedPtr_t pTasksExecutor)
                : m_pThread{nullptr}
                , m_pTasksExecutor{std::move(pTasksExecutor)}
            {
                std::cout << "TasksExecutor::Impl::Impl()" << std::endl;
            }

            ~Impl()
            {
                std::cout << "TasksExecutor::Impl::~Impl()" << std::endl;
            }

            void Service()
            {
                std::cout << "TasksExecutor::Impl::Service()" << std::endl;

                m_pThread = std::make_unique<std::jthread>(&Impl::ServiceImpl_, this);
            }

        private:
            void ServiceImpl_()
            {
                std::cout << "TasksExecutor::Impl::ServiceImpl_()" << std::endl;
            }

        private:
            std::unique_ptr<std::jthread> m_pThread;
            TasksExecutorSharedPtr_t m_pTasksExecutor;
        };

        TasksContextSharedPtr_t TasksContext::Create()
        {
            return std::make_shared<TasksContext>();
        }

        TasksContext::TasksContext()
            : m_pImpl{Impl::Create(TasksExecutor::Create())}
        {
            std::cout << "TasksExecutor::TasksExecutor()" << std::endl;
        }

        TasksContext::~TasksContext()
        {
            std::cout << "TasksExecutor::~TasksExecutor()" << std::endl;
        }

        void TasksContext::Service()
        {
            std::cout << "TasksExecutor::Service()" << std::endl;
            if (!m_pImpl)
            {
                std::cout << "TasksExecutor::Service() - m_pImpl is nullptr" << std::endl;
            }

            m_pImpl->Service();
        }
    }
}