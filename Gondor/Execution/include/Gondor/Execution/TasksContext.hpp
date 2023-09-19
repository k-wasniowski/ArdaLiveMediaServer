// Copyright 2023 The Arda Project Authors. All rights reserved.
//
// Copying, utilizing or revealing any part or entirety of this file
// and its contents without proper authorization is not allowed.

#pragma once

#include <memory>

namespace Gondor
{
    namespace Execution
    {
        class TasksContext;
        using TasksContextSharedPtr_t = std::shared_ptr<TasksContext>;

        class TasksContext
        {
        public:
            static TasksContextSharedPtr_t Create();

            TasksContext();
            ~TasksContext();

            void Service();

        private:
            class Impl;
            std::unique_ptr<Impl> m_pImpl;
        };
    }
}