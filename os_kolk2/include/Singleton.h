#pragma once

#include "CreationPolicies.h"
#include "LifetimePolicies.h"
#include "ThreadingPolicies.h"

template
<
    typename T,
    template <class> class CreationPolicy = CreateUsingNew,
    template <class> class LifetimePolicy = DefaultLifetime,
    template <class> class ThreadingModel = SingleThreaded
>
class Singleton
{
public:
    static T& Instance()
    {
        if (!m_instance)
        {
            ThreadingModel<T>::Lock guard;
            if (!m_instance)
            {
                if (m_destroyed)
                {
                    LifetimePolicy<T>::OnDeadReference();
                    m_destroyed = false;
                }
                m_instance = CreationPolicy<T>::Create();
                LifetimePolicy<T>::ScheduleDestruction(&DestroySingleton);
            }
        }
        return *m_instance;
    }

private:
    Singleton() = delete;
    ~Singleton() = delete;
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static void DestroySingleton()
    {
        CreationPolicy<T>::Destroy(m_instance);
        m_instance = nullptr;
        m_destroyed = true;
    }

    static T* m_instance;
    static bool m_destroyed;
};

template <typename T, template <class> class C, template <class> class L, template <class> class M>
T* Singleton<T, C, L, M>::m_instance = nullptr;

template <typename T, template <class> class C, template <class> class L, template <class> class M>
bool Singleton<T, C, L, M>::m_destroyed = false;
