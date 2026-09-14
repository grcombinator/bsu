#include <iostream>
#include "Singleton.h"

class MyClass
{
public:
    void DoSomething()
    {
        std::cout << "Doing something..." << std::endl;
    }
    
    ~MyClass()
    {
        std::cout << "MyClass destroyed" << std::endl;
    }
};

int main()
{
    // Используем Singleton с политиками по умолчанию
    Singleton<MyClass>::Instance().DoSomething();
    
    // Кастомный Singleton с разными политиками
    using MySingleton = Singleton<
        MyClass,
        CreateUsingNew,
        PhoenixSingleton,
        ClassLevelLockable>;
    
    MySingleton::Instance().DoSomething();
    
    return 0;
}
