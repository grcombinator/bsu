#pragma once

// Стандартное управление временем жизни
template <class T>
class DefaultLifetime
{
public:
    static void ScheduleDestruction(void (*func)())
    {
        std::atexit(func);
    }
    
    static void OnDeadReference()
    {
        throw std::runtime_error("Dead Reference Detected");
    }
};

// Управление временем жизни через phoenix singleton
template <class T>
class PhoenixSingleton
{
public:
    static void ScheduleDestruction(void (*func)())
    {
        std::atexit(func);
    }
    
    static void OnDeadReference()
    {
        // Разрешаем повторное создание после уничтожения
    }
};

// Долгоживущий singleton (не уничтожается автоматически)
template <class T>
class NoDestroy
{
public:
    static void ScheduleDestruction(void (*func)())
    {
        // Ничего не делаем
    }
    
    static void OnDeadReference()
    {
        throw std::runtime_error("Dead Reference Detected");
    }
};
