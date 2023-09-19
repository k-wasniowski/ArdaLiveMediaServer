// Copyright 2023 The Arda Project Authors. All rights reserved.
//
// Copying, utilizing or revealing any part or entirety of this file
// and its contents without proper authorization is not allowed.

#include <Gondor/Execution/TasksExecutor.hpp>

#include <iostream>

namespace Gondor
{
    namespace Execution
    {
        TasksExecutorSharedPtr_t TasksExecutor::Create()
        {
            return std::make_shared<TasksExecutor>();
        }

        TasksExecutor::TasksExecutor() {}

        TasksExecutor::~TasksExecutor() {}

        void TasksExecutor::Service() {}
    }
}
