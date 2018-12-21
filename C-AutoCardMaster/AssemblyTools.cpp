#include "stdafx.h"
#include "AssemblyTools.h"


AssemblyTools::AssemblyTools() 
{
	HANDLE hProcess = gMrw->getHandle();
	virtualAddr = (INT32)VirtualAllocEx(hProcess, 0, 0x1000, 0x103000, 0x40);
	this->setTimer();
}


AssemblyTools::~AssemblyTools()
{
	
}

void AssemblyTools::retn()
{
	writeInt8(0xC3);
}

void AssemblyTools::RunRemoteThread(bool IsMainThread) const
{
	if (!IsMainThread) {
		while (gMrw->readInt32(virtualAddr) != 0) Sleep(0);
		INT32 m = 0;
		for (size_t i = 0; i < code.size(); i++) {
			gMrw->writeInt8((virtualAddr + m++), code[i]);
		}
		HANDLE hThread = CreateRemoteThread(gMrw->getHandle(), 0, 0, (LPTHREAD_START_ROUTINE)CallWindowProcW, (LPVOID)virtualAddr, 0, 0);
		if (hThread == 0)
		{
			MessageBox(0, L"CreateRemoteThread Failed", 0, 0);
		}
		WaitForSingleObject(hThread, 0xFFFFFFFF);
		CloseHandle(hThread);
		for (size_t i = 0; i < code.size(); i++) {
			gMrw->writeInt8((virtualAddr + code[i]), 0);
		}
		return;
	}

	while (gMrw->readInt32(virtualAddr + 0x990) == virtualAddr) Sleep(0);
	for (size_t i = 0; i < code.size(); i++)
		gMrw->writeInt8((virtualAddr + i), code[i]);
	gMrw->writeInt32(virtualAddr + 0x990, virtualAddr);

	while (gMrw->readInt32(virtualAddr + 0x990) == virtualAddr)
		Sleep(0);
	for (size_t i = 0; i < code.size(); i++)
		gMrw->writeInt8((virtualAddr + i), 0);
}

void AssemblyTools::setTimer()
{
	gMrw->writeInt32(virtualAddr + 0x990, virtualAddr + 0x9A0);
	gMrw->writeInt8(virtualAddr + (INT32)0x9A0, 0xC3);
	
	HWND h = FindWindow(L"RiotWindowClass", L"League of Legends (TM) Client");

	INT32 procAddr = virtualAddr + 0xF00;

	clear();
	//mov_addr_XXX(virtualAddr,virtualAddr + 0x1900);
	call_addr(virtualAddr + 0x990);
	writeInt8(0xC3);

	for (size_t i = 0; i < code.size(); i++)
		gMrw->writeInt8((procAddr + i), code[i]);

	clear();
	pushad();
	push(0x1000);
	push((INT32)h);
	mov_eax((INT32)KillTimer);
	call_eax();

	push(procAddr);
	push(0x1);
	push(0x1000);
	push((INT32)h);
	mov_eax((INT32)SetTimer);
	call_eax();
	popad();
	retn();
	RunRemoteThread(false);

}
