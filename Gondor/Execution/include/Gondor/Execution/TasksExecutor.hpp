// Copyright 2023 The Arda Project Authors. All rights reserved.
//
// Copying, utilizing or revealing any part or entirety of this file
// and its contents without proper authorization is not allowed.

#pragma once

#include <memory>

#include <boost/asio.hpp>

namespace Gondor
{
    namespace Execution
    {
        class TasksExecutor;
        using TasksExecutorSharedPtr_t = std::shared_ptr<TasksExecutor>;

        class TasksExecutor
        {
        public:
            static TasksExecutorSharedPtr_t Create();

            TasksExecutor();
            ~TasksExecutor();

            void Service();

        private:
            boost::asio::io_context m_ioContext;
        };
    }
}