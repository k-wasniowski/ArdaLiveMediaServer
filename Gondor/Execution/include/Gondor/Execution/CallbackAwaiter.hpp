#pragma once

#include <memory>
#include <optional>

namespace Gondor
{
    namespace Execution
    {
        template <typename T = void>
        class CallbackAwaiter
        {
        public:
            bool await_ready() noexcept
            {
                return false;
            }

            const T& await_resume() const noexcept(false)
            {
                if (exception_)
                    std::rethrow_exception(exception_);
                return result_.value();
            }

            virtual ~CallbackAwaiter() = default;

        protected:
            void SetException(const std::exception_ptr& e)
            {
                exception_ = e;
            }

            void SetValue(const T& v)
            {
                result_.emplace(v);
            }

            void SetValue(T&& v)
            {
                result_.emplace(std::move(v));
            }

        private:
            std::optional<T> result_;
            std::exception_ptr exception_{nullptr};
        };
    }
}