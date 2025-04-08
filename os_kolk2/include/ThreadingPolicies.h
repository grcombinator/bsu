#pragma once
#include <mutex>

// Для однопоточного использования
template <class T>
class SingleThreaded
{
public:
    class Lock
    {
    public:
        Lock() {}
        ~Lock() {}
    };
    
    using VolatileType = T;
};

// Для многопоточного использования
template <class T>
class ClassLevelLockable
{
public:
    class Lock
    {
    public:
        Lock()
        {
            m_mutex.lock();
        }
        
        ~Lock()
        {
            m_mutex.unlock();
        }
        
    private:
        static std::mutex m_mutex;
    };
    
    using VolatileType = volatile T;
};

template <class T>
std::mutex ClassLevelLockable<T>::Lock::m_mutex;
