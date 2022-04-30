
#include <iostream>
#include <windows.h>

HCRYPTPROV prov;
int MRandom
(void)
{
    if (prov == NULL)
        if (!CryptAcquireContext(&prov,
            NULL, NULL, PROV_RSA_FULL,
            CRYPT_SILENT | CRYPT_VERIFYCONTEXT))
            ExitProcess(1);
    int out;
    CryptGenRandom(prov, sizeof(out), (BYTE*)(&out));
    return out & 0x7fffffff;
}

static NTSTATUS(__stdcall* NtDelayExecution)
    (BOOL Alertable, PLARGE_INTEGER DelayInterval) =
         (NTSTATUS(__stdcall*)(BOOL, PLARGE_INTEGER)) GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtDelayExecution");
static NTSTATUS(__stdcall* ZwSetTimerResolution)
    (IN ULONG RequestedResolution, IN BOOLEAN Set, OUT PULONG ActualResolution) =
         (NTSTATUS(__stdcall*)(ULONG, BOOLEAN, PULONG)) GetProcAddress(GetModuleHandleA("ntdll.dll"), "ZwSetTimerResolution");

static void SleepShort(float milliseconds) {
	static bool once = true;
	if (once) {
		ULONG actualResolution;
		ZwSetTimerResolution(1, true, &actualResolution);
		once = false;
	}

	LARGE_INTEGER interval;
	interval.QuadPart = -1 * (int)(milliseconds * 10000.0f);
	NtDelayExecution(false, &interval);
}

int main()
{
    std::cout << "Hello World!\n";
	system("color c2");

	HWND hwnd = GetConsoleWindow();
	MoveWindow(hwnd, 0, 0, 200, 200, false);

	int x = MRandom() % 1920;
	int y = MRandom() % 1080;
	bool dir = true; /* true = ++ */
	while (true) {
		SetWindowPos(hwnd, nullptr, x, y, 1, 1, SWP_NOSIZE | SWP_NOZORDER);
		if (dir == true) {
			x++; x++;
			y++;
		}
		else {
			x--; x--;
			y--;
		}
		SleepShort(0.01);
		if (x > 1920 || y > 1080)
			dir = false;
		if (x < 0 || y < 0)
			dir = true;
	}
}