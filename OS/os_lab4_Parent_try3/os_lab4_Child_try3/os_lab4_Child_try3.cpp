#include <windows.h>
#include <iostream>
#include <string>
#include <sstream>

int wmain(int argc, wchar_t* argv[]) {
    if (argc < 2) return 1;
    int messageCount = _wtoi(argv[1]);

    
    HANDLE hMutex = OpenMutexW(MUTEX_ALL_ACCESS, FALSE, L"Global\\MsgMutex");
    HANDLE hSemaphore = OpenSemaphoreW(SEMAPHORE_MODIFY_STATE, FALSE, L"Global\\CompletionSemaphore");
    HANDLE hEventA = OpenEventW(EVENT_MODIFY_STATE, FALSE, L"Global\\MessageA");
    HANDLE hEventB = OpenEventW(EVENT_MODIFY_STATE, FALSE, L"Global\\MessageB");

    if (!hMutex || !hSemaphore || !hEventA || !hEventB) {
        std::cerr << "Error opening sync objects\n";
        return 1;
    }

    
    for (int i = 0; i < messageCount; i++) {
        WaitForSingleObject(hMutex, INFINITE);

        std::ostringstream pidStream;
        pidStream << GetCurrentProcessId();
        std::cout << "Child " << pidStream.str() << ": Active\n";

        std::string input;
        std::cout << "Enter message (A/B): ";
        std::cin >> input;

        if (input == "A") {
            SetEvent(hEventA);
        }
        else if (input == "B") {
            SetEvent(hEventB);
        }

        std::cout << "Child: Inactive\n";
        ReleaseMutex(hMutex);
    }

    
    ReleaseSemaphore(hSemaphore, 1, nullptr);

    CloseHandle(hMutex);
    CloseHandle(hSemaphore);
    CloseHandle(hEventA);
    CloseHandle(hEventB);

    std::cout << "Child process exiting\n";
    return 0;
}