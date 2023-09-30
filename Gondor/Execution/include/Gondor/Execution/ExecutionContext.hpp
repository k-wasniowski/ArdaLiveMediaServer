#include <Gondor/Execution/ITasksExecutor.hpp>

#include <memory>

namespace Gondor
{
    namespace Execution
    {
        class ExecutionContext : public ITasksExecutor
        {
        public:
            ExecutionContext(uint32_t threadsCount = 1);
            ~ExecutionContext() override;

        private:
            class Impl;
            std::unique_ptr<Impl> m_pImpl;
        };
    }
}
