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
        class ITask
        {
        public:
            virtual ~ITask() = default;

            virtual void Service() = 0;
        };

        using ITaskSharedPtr_t = std::shared_ptr<ITask>;
    }
}