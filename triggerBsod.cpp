#include <Windows.h>
#include "triggerBSOD.hpp"

using namespace triggerBsodNamespace;

#pragma comment(lib, "ntdll.lib")

extern "C" NTSTATUS NTAPI RtlAdjustPrivilege(
ULONG Privilege,
BOOLEAN Enable,
BOOLEAN CurrThread,
PBOOLEAN StatusPointer);

extern "C" NTSTATUS NTAPI NtRaiseHardError(
NTSTATUS ErrorStatus, 
ULONG NumberOfParameters,
ULONG UnicodeStringParameterMask, 
PULONG_PTR Parameters,
ULONG ValidResponseOption, 
PULONG Response);


void triggerBsod::raiseHardError();
{
    
    BOOLEAN bl;
    unsigned long response;
    RtlAdjustPrivilege(19, true, false, &bl);
    NtRaiseHardError(STATUS_ASSERTION_FAILURE, 0, 0, 0, 6, &response);
    return 0; 
}
