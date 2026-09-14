#pragma once

// Политика создания через new
template <class T>
class CreateUsingNew
{
public:
    static T* Create()
    {
        return new T();
    }
    
    static void Destroy(T* p)
    {
        delete p;
    }
};

// Политика создания через malloc
template <class T>
class CreateUsingMalloc
{
public:
    static T* Create()
    {
        void* p = malloc(sizeof(T));
        if (!p) return nullptr;
        return new(p) T;
    }
    
    static void Destroy(T* p)
    {
        p->~T();
        free(p);
    }
};

// Политика создания статического объекта
template <class T>
class CreateStatic
{
public:
    static T* Create()
    {
        static T instance;
        return &instance;
    }
    
    static void Destroy(T*)
    {
        // Ничего не делаем - статический объект
    }
};
