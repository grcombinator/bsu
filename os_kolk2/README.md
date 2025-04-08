# Modern C++ Singleton Implementation

Реализация шаблона проектирования Singleton с ортогональными стратегиями в стиле библиотеки Loki, как описано в книге Андрея Александреску "Modern C++ Design".

## Особенности

- **Гибкая архитектура** на основе политик (policy-based design)
- **Три ортогональные стратегии**:
  - Способ создания объекта (CreationPolicy)
  - Управление временем жизни (LifetimePolicy)
  - Потокобезопасность (ThreadingModel)
- **Готовые реализации стратегий** в составе библиотеки
- **Поддержка C++17** и современных стандартов

## Быстрый старт

```cpp
#include "Singleton.h"

class MyService {
public:
    void DoWork() { /* ... */ }
};

int main() {
    // Использование с политиками по умолчанию
    Singleton<MyService>::Instance().DoWork();
    
    // Кастомизированный Singleton
    using CustomSingleton = Singleton<
        MyService,
        CreateStatic,       // Создание как статический объект
        PhoenixSingleton,   // Возрождающийся Singleton
        ClassLevelLockable  // Потокобезопасная версия
    >;
    
    CustomSingleton::Instance().DoWork();
    return 0;
}
```

## Доступные стратегии

### Политики создания (CreationPolicy)
- `CreateUsingNew` - создание через оператор new (по умолчанию)
- `CreateUsingMalloc` - создание через malloc + placement new
- `CreateStatic` - создание как статический объект

### Политики времени жизни (LifetimePolicy)
- `DefaultLifetime` - уничтожение при exit() (по умолчанию)
- `PhoenixSingleton` - позволяет воссоздание после уничтожения
- `NoDestroy` - никогда не уничтожается автоматически

### Модели потоков (ThreadingModel)
- `SingleThreaded` - для однопоточного использования (по умолчанию)
- `ClassLevelLockable` - потокобезопасная версия с мьютексом

## Сборка и тестирование

```bash
# Клонирование репозитория
git clone https://github.com/yourusername/modern-singleton.git
cd modern-singleton

# Создание build-директории
mkdir build && cd build

# Генерация проекта
cmake ..

# Сборка
cmake --build .

# Запуск тестов
ctest
```

## Требования

- Компилятор с поддержкой C++17 (GCC 7+, Clang 5+, MSVC 2017+)
- CMake 3.10+
- Google Test (для тестов, опционально)

## Лицензия

Проект распространяется под лицензией MIT. См. файл LICENSE.
