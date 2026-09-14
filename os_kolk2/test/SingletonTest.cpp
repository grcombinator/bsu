#include "Singleton.h"
#include <gtest/gtest.h>
#include <thread>
#include <vector>

// Тестовый класс для проверки Singleton
class TestClass {
public:
    void increment() { counter++; }
    int get() const { return counter; }
private:
    int counter = 0;
};

// Тест базового функционала Singleton
TEST(SingletonTest, BasicFunctionality) {
    auto& instance1 = Singleton<TestClass>::Instance();
    auto& instance2 = Singleton<TestClass>::Instance();
    
    EXPECT_EQ(&instance1, &instance2) << "Singleton should return the same instance";
}

// Тест политики времени жизни Phoenix
TEST(SingletonTest, PhoenixSingleton) {
    using PhoenixTest = Singleton<TestClass, CreateUsingNew, PhoenixSingleton>;
    
    auto& instance = PhoenixTest::Instance();
    instance.increment();
    EXPECT_EQ(instance.get(), 1);
    
    // Симулируем разрушение (обычно вызывается при exit)
    Singleton<TestClass, CreateUsingNew, PhoenixSingleton>::DestroySingleton();
    
    // PhoenixSingleton должен разрешить повторное создание
    auto& newInstance = PhoenixTest::Instance();
    newInstance.increment();
    EXPECT_EQ(newInstance.get(), 1) << "Phoenix singleton should create new instance";
}

// Тест многопоточного доступа
TEST(SingletonTest, ThreadSafety) {
    using ThreadSafeSingleton = Singleton<TestClass, CreateUsingNew, DefaultLifetime, ClassLevelLockable>;
    
    constexpr int threadCount = 100;
    std::vector<std::thread> threads;
    
    for (int i = 0; i < threadCount; ++i) {
        threads.emplace_back([]() {
            auto& instance = ThreadSafeSingleton::Instance();
            instance.increment();
        });
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    EXPECT_EQ(ThreadSafeSingleton::Instance().get(), threadCount) 
        << "All increments should be preserved in thread-safe singleton";
}

// Тест политики NoDestroy
TEST(SingletonTest, NoDestroyPolicy) {
    using NoDestroySingleton = Singleton<TestClass, CreateUsingNew, NoDestroy>;
    
    auto& instance = NoDestroySingleton::Instance();
    instance.increment();
    
    // Попытка "уничтожения" не должна иметь эффекта
    NoDestroySingleton::DestroySingleton();
    auto& sameInstance = NoDestroySingleton::Instance();
    EXPECT_EQ(sameInstance.get(), 1) << "NoDestroy policy should preserve instance";
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
