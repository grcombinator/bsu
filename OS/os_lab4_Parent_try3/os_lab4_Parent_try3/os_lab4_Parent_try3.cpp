#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <sstream>

int main() {
    
    int M, N;
    std::cout << "Enter number of Child processes: ";
    std::cin >> M;
    std::cout << "Enter number of messages per Child: ";
    std::cin >> N;

    
    HANDLE hMutex = CreateMutexW(nullptr, FALSE, L"Global\\MsgMutex");
    HANDLE hSemaphore = CreateSemaphoreW(nullptr, 0, M, L"Global\\CompletionSemaphore");
    HANDLE hEventA = CreateEventW(nullptr, FALSE, FALSE, L"Global\\MessageA");
    HANDLE hEventB = CreateEventW(nullptr, FALSE, FALSE, L"Global\\MessageB");

    if (!hMutex || !hSemaphore || !hEventA || !hEventB) {
        std::cerr << "Error creating sync objects\n";
        return 1;
    }

    
    for (int i = 0; i < M; i++) {
        STARTUPINFOW si = { sizeof(si) };
        PROCESS_INFORMATION pi;

        std::wostringstream cmdStream;
        cmdStream << L"Child.exe " << N;
        std::wstring cmd = cmdStream.str();

        if (!CreateProcessW(nullptr, &cmd[0], nullptr, nullptr,
            FALSE, CREATE_NEW_CONSOLE, nullptr, nullptr, &si, &pi)) {
            std::cerr << "Error creating process\n";
            continue;
        }
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }

 
    HANDLE msgEvents[] = { hEventA, hEventB };
    int completed = 0;

    while (completed < M) {
        DWORD result = WaitForMultipleObjects(2, msgEvents, FALSE, INFINITE);

        if (result == WAIT_OBJECT_0) {
            std::cout << "Received message A\n";
        }
        else if (result == WAIT_OBJECT_0 + 1) {
            std::cout << "Received message B\n";
        }

        
        while (WaitForSingleObject(hSemaphore, 0) == WAIT_OBJECT_0) {
            completed++;
            std::cout << "Child completed (" << completed << "/" << M << ")\n";
        }
    }

    
    CloseHandle(hMutex);
    CloseHandle(hSemaphore);
    CloseHandle(hEventA);
    CloseHandle(hEventB);

    std::cout << "All children completed. Parent exiting.\n";
    return 0;
}