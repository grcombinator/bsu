#include <windows.h>
#include <iostream>
#include <string>
#include <vector>

int main() {
    int size;
    std::cout << "Enter massive size: ";
    std::cin >> size;

    std::vector<int> arr(size);
    std::cout << "Enter elements: ";
    for (int i = 0; i < size; i++) {
        std::cin >> arr[i];
    }

    std::string commandLine = "Child.exe " + std::to_string(size);
    for (int num : arr) {
        commandLine += " " + std::to_string(num);
    }

    std::wstring commandLineW(commandLine.begin(), commandLine.end());

    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);

    
    si.dwFlags = STARTF_USEPOSITION | STARTF_USESIZE; 
    si.dwX = 5; 
    si.dwY = 5; 
    si.dwXSize = 600; 
    si.dwYSize = 600; 

    ZeroMemory(&pi, sizeof(pi));

    if (CreateProcessW(NULL, const_cast<wchar_t*>(commandLineW.c_str()), NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    else {
        std::cerr << "Ошибка создания процесса" << std::endl;
    }

    return 0;
}