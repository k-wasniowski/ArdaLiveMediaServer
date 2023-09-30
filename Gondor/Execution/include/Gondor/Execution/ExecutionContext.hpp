#pragma once

#include <Gondor/Execution/ITasksExecutor.hpp>

#include <memory>

namespace Gondor
{
    namespace Execution
    {
        class ExecutionContext;
        using ExecutionContextSharedPtr = std::shared_ptr<ExecutionContext>;
        using ExecutionContextWeakPtr = std::weak_ptr<ExecutionContext>;

        class ExecutionContext : public ITasksExecutor
        {
        public:
            static ExecutionContextSharedPtr Create(uint32_t threadsCount = 1);

            ExecutionContext(uint32_t threadsCount = 1);
            ~ExecutionContext() override;

            bool PostTask(std::function<void()> task) override;

            void Run();
            void Terminate();

        private:
            class Impl;
            std::unique_ptr<Impl> m_pImpl;
        };
    }
}
