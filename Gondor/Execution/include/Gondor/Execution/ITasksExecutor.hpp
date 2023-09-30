#pragma once

#include <functional>

namespace Gondor
{
    namespace Execution
    {
        class ITasksExecutor
        {
        public:
            virtual ~ITasksExecutor() = default;

            virtual bool PostTask(std::function<void()> task) = 0;
        };
    }
}
