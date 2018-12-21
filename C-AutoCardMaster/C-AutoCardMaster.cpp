// C-AutoCardMaster.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "C-AutoCardMaster.h"
#include "main.h"
#include "DialogMain.h"

DWORD WINAPI ExeMain(LPVOID lpParameter);

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
	ExeMain(hInstance);
	return 0;
}

void GetFileNameFromPath(PWCHAR path, DWORD pathSize, PWCHAR fileName, DWORD fileNameSize) {
	size_t index = (int)wcslen(path);
	while (index >= 0) {
		if (path[index] == L'\\') {
			break;
		}
		index--;
	}
	if (index < 0) {
		return;
	}
	wcscpy_s(fileName, fileNameSize, path + index + 1);
}
int GetSystemBits() {
	SYSTEM_INFO si;
	GetNativeSystemInfo(&si);
	return (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 || si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64) ? 64 : 32;
}


DWORD WINAPI ExeMain(LPVOID lpParameter) {
	gHandleInstance = (HINSTANCE)lpParameter;
	if (GetSystemBits() != 64) {
		MessageBox(nullptr, L"此应用程序只支持64位Win7、Win8和Win10", L"兼容性", MB_OK | MB_ICONERROR);
		TerminateProcess(GetCurrentProcess(), 0);
		return 0;
	}
	//WCHAR szFilePath[MAX_PATH];
	//GetModuleFileName(NULL, szFilePath, MAX_PATH);
	//GetFileNameFromPath(szFilePath, MAX_PATH, szFilePath, MAX_PATH);
	//if (_wcsicmp(szFilePath, L"crossproxy.exe") != 0) {
	//	MessageBox(nullptr, L"请勿修改文件名！", szFilePath, MB_OK | MB_ICONERROR);
	//	TerminateProcess(GetCurrentProcess(), 0);
	//	return 0;
	//}

	DialogBox(gHandleInstance, MAKEINTRESOURCE(IDD_DIALOG1), nullptr, DialogProc);
	return 0;
}