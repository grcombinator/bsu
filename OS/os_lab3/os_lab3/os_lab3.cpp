#include <Windows.h> 
#include <iostream>
#include <vector>
#include <string>
using namespace std;
struct Thread {
	vector <string> v;
	char A, B;
};
vector <string> workresult;
int MultElementResult = 1;

CRITICAL_SECTION cs; 

DWORD WINAPI work(Thread& thread) {
	HANDLE hevent1 = OpenEventA(SYNCHRONIZE, FALSE, "event1");
	if (hevent1 == nullptr) {
		std::cout << GetLastError();
		return 1;
	}
	EnterCriticalSection(&cs);
	WaitForSingleObject(hevent1, INFINITE);
	//////SetEvent(hevent1);  
 
	cout << "work is start" << endl;    
	int time;
	cout << "Enter sleep time "<<endl;
	cin >> time;
 
	for (int i = 0; i < thread.v.size(); i++) {
		int count = 0;
		for (int j = 0; j < thread.v[i].size();j++) {
			if (thread.v[i][j] < thread.A || thread.v[i][j]>thread.B)
				break;
			else
				count++;
		}
		if (count == thread.v[i].size()) {
			workresult.push_back(thread.v[i]);
			Sleep(time);
		}
	} 
	LeaveCriticalSection(&cs);
	CloseHandle(hevent1);
	cout << "work is end" << endl;
	return 0;
}

DWORD WINAPI MultElement(Thread& thread) {
	HANDLE hevent1 = OpenEventA(SYNCHRONIZE, FALSE, "event1"); 
	if (hevent1 == nullptr) { 
		std::cout << GetLastError(); 
		return 1;
	}
	WaitForSingleObject(hevent1, INFINITE);
	////SetEvent(hevent1, INFINITE);
	cout << "MultElement is start" << endl;
	for (int i = 0; i < thread.v.size(); i++) {
		MultElementResult *= thread.v[i].size();
	}
	CloseHandle(hevent1);

	HANDLE hevent2 = OpenEventA(EVENT_ALL_ACCESS, FALSE, "event2"); 
	SetEvent(hevent2);
	cout << "MultElement is end" << endl;
	return 0;
}
int main() {
	InitializeCriticalSection(&cs); 
	HANDLE hevent1 = CreateEventA(nullptr, TRUE, FALSE, "event1");
	HANDLE hevent2 = CreateEventA(nullptr, FALSE, FALSE, "event2");

	Thread thread;
	int size;
	cout << "Enter size of massive ";
	cin >> size;
	cout << endl<<"Enter "<<size<<" strings"<<endl;
	string s;
	for (int i = 0; i < size; i++) {
		cin >> s;
		thread.v.push_back(s); 
	}

	HANDLE hWork = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)work, &thread, 0, nullptr);
	HANDLE hMultElement = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MultElement, &thread, 0, nullptr);

	char A, B;
	cout << "Enter 2 symbols"<<endl;
	cin >> A >> B;
	thread.A = A;
	thread.B = B; 
	SetEvent(hevent1); 
	 
	EnterCriticalSection(&cs);
	for (const string& res : workresult) {
		cout << res << endl;
	}
	LeaveCriticalSection(&cs);

	WaitForSingleObject(hevent2, INFINITE);
	cout << MultElementResult << endl;;
	WaitForSingleObject(hWork, INFINITE);
	CloseHandle(hWork);
	WaitForSingleObject(hMultElement, INFINITE);
	CloseHandle(hMultElement);
	DeleteCriticalSection(&cs);
	CloseHandle(hevent1);
	CloseHandle(hevent2);
	return 0;
}