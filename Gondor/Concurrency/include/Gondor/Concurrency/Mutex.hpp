#pragma once

#include <mutex>

namespace Gondor
{
    namespace Concurrency
    {
        template <typename T>
        concept Lockable = requires(T a)
        {
            a.lock();
            a.unlock();
        };

        template <class Object, typename Lockable = std::mutex>
        class Mutex
        {
        private:
            template <class ObjectPtr, template <typename> typename Locker>
            class CommonGuard
            {
            public:
                CommonGuard(const Mutex& mutex)
                    : m_ptr{std::addressof(mutex.m_object)}
                    , m_lock{mutex.m_lockable}
                {}

                ObjectPtr* operator->() const noexcept
                {
                    return m_ptr;
                }
                ObjectPtr* operator*() const noexcept
                {
                    return m_ptr;
                }

            private:
                ObjectPtr* m_ptr;
                Locker<Lockable> m_lock;
            };

        public:
            template <typename... Args, std::enable_if_t<std::is_constructible_v<Object, Args...>, int> = 0>
            Mutex(Args&&... args)
                : m_object(std::forward<Args>(args)...)
            {}

            using LockGuard = CommonGuard<Object, std::lock_guard>;
            using ConstLockGuard = CommonGuard<const Object, std::lock_guard>;

            [[nodiscard]] LockGuard Lock() const
            {
                return LockGuard{*this};
            }

        private:
            mutable Object m_object;
            mutable Lockable m_lockable;
        };
    }
}
