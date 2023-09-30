#include <Gondor/Execution/ExecutionContext.hpp>

#include <condition_variable>
#include <mutex>

#include <gtest/gtest.h>

TEST(ExecutionContextTests, Creation)
{
    auto pExecutionContext = Gondor::Execution::ExecutionContext::Create();
    ASSERT_TRUE(pExecutionContext != nullptr);
}

TEST(ExecutionContextTests, EmptyTask)
{
    auto pExecutionContext = Gondor::Execution::ExecutionContext::Create();
    ASSERT_TRUE(pExecutionContext != nullptr);

    auto result = pExecutionContext->PostTask(nullptr);

    ASSERT_FALSE(result);

    pExecutionContext->Terminate();
}

TEST(ExecutionContextTests, SampleTask)
{
    auto pExecutionContext = Gondor::Execution::ExecutionContext::Create();
    ASSERT_TRUE(pExecutionContext != nullptr);

    pExecutionContext->Run();

    bool triggered = false;
    std::mutex m;
    std::condition_variable cv;

    auto result = pExecutionContext->PostTask([&triggered, &cv]() {
        triggered = true;
        cv.notify_one();
    });

    ASSERT_TRUE(result);

    std::unique_lock lk(m);
    cv.wait(lk, [&triggered] { return triggered; });
    ASSERT_TRUE(triggered);

    pExecutionContext->Terminate();
}