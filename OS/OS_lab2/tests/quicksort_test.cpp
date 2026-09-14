#include <sstream>

// Функция для тестирования парсинга аргументов
std::vector<int> parseArguments(int argc, char* argv[]) {
    if (argc < 2) return {};
    int size = std::atoi(argv[1]);
    std::vector<int> arr(size);
    for (int i = 0; i < size && (i + 2) < argc; ++i) {
        arr[i] = std::atoi(argv[i + 2]);
    }
    return arr;
}

TEST(ArgumentParsingTest, ValidArguments) {
    char* args[] = { "Child.exe", "3", "10", "5", "7" };
    std::vector<int> result = parseArguments(4, args);
    std::vector<int> expected = { 10, 5, 7 };
    EXPECT_EQ(result, expected);
}

TEST(ArgumentParsingTest, NotEnoughArguments) {
    char* args[] = { "Child.exe" };
    std::vector<int> result = parseArguments(1, args);
    EXPECT_TRUE(result.empty());
}