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
        class ITasksContextProxy
        {
        public:
            virtual ~ITasksContextProxy() = default;
        };

        using ITasksContextProxySharedPtr_t = std::shared_ptr<ITasksContextProxy>;
    }
}