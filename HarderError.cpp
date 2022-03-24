/*++

    Copyright (c) 2022 @daylimbic

    File Name: 
        
        HarderError.cpp
    
    Abstract:

        Creates a more interesting NtRaiseHardError with display tinkering 

    Linker flags: 
        
        lgdi32 

--*/

#include <Windows.h>
#include <winternl.h>
#include <math.h> 

#define PI 3.1415926535
#define ITERATIONS 150
#define ITERATIONSM 40
#define DISTANCE 4
#define SIZE 10 

using namespace std;

#define RAISE_HARD_ERROR_FAIL -1

#pragma comment(lib, "ntdll.lib")

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


DWORD 
InvokeBsod
    (NTSTATUS err)
{

    BOOLEAN bl;
    unsigned long response;
    RtlAdjustPrivilege(19, true, false, &bl);
    NtRaiseHardError(STATUS_ASSERTION_FAILURE, 
        0, 0, 0, 6, &response);

    /* System should be unresponsive by now */

    return RAISE_HARD_ERROR_FAIL;
}

void* 
DrawSys32Icon
    (void) 
{
    BITMAP bm;

    int x = GetSystemMetrics(SM_CXSCREEN);
    int y = GetSystemMetrics(SM_CYSCREEN);

    HBITMAP bi = (HBITMAP) LoadImage(0, 
        "C:\\Windows\\System32\\BluetoothPairingSystemToastIcon.contrast-high.png", /* not always present! change accordingly */
        IMAGE_BITMAP, x, y, LR_LOADFROMFILE);
    HDC whdc = GetDC(NULL);
    HDC hdcMem = CreateCompatibleDC(whdc);
    SelectObject(hdcMem, bi);
    GetObject( (HGDIOBJ) bi, sizeof(bm), &bm);
    BitBlt(whdc, 10, 10, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);
    DeleteDC(hdcMem);
    DeleteObject(di);

    return nullptr;
}

void* 
DrawDumbCircle
    (void) 
{
    HDC whdc = GetDC(NULL);
 
	const int scrx = GetSystemMetrics(SM_XVIRTUALSCREEN);
	const int scry = GetSystemMetrics(SM_YVIRTUALSCREEN);
	const int scrw = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	const int scrh = GetSystemMetrics(SM_CYVIRTUALSCREEN);
 
	HDC ssdc = CreateCompatibleDC(whdc);
	HBITMAP ssbmp = CreateCompatibleBitmap(whdc, scrw, scrh);
	SelectObject(ssdc, ssbmp);
    
    int counter = 0;

	while (counter > 1000) {
		BitBlt(ssdc, scrx, scry, scrw, scrh, whdc, 0, 0, SRCCOPY);
 
		POINT curpos;
		GetCursorPos(&curpos);
		curpos.x += scrx;
		curpos.y += scry;
 
		for (float angle = 0; angle < 2*PI; angle += PI/ITERATIONS*2) {
			float normX = sinf(angle);
			float normY = cosf(angle);
 
			for (int d = 0; d < ITERATIONSM*DISTANCE; d+=DISTANCE) {
				float dfac = 1-d / ((float)(ITERATIONSM*DISTANCE));
				int srcX = normX * (d-1) + curpos.x;
				int srcY = normY * (d-1) + curpos.y;
 
				int targetX = normX * d + curpos.x;
				int targetY = normY * d + curpos.y;
				
				BitBlt(ssdc, targetX, targetY, SIZE, SIZE, ssdc, srcX, srcY, SRCCOPY);
			}
		}
		BitBlt(whdc, 0, 0, scrw, scrh, ssdc, scrx, scry, SRCCOPY);
		Sleep(50);
       		counter++;
	} 
	
     return nullptr;
}


NTSTATUS 
__stdcall 
NtRaiseHarderError
    () 
{
    
    DrawSys32Icon();
    DrawDumbCircle();

    NTSTATUS stackOverflow = ((DWORD)0xC00000FDL);
    
    if (InvokeBsod(stackOverflow)) 
        return RAISE_HARD_ERROR_FAIL;

}
