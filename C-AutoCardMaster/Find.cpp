#include "stdafx.h"
#include "string"

INT32 GetCallAddress(INT32 CallBase) {
	return (*(DWORD*)(CallBase + 0x1) + CallBase + 5);
}

BOOL bCompare(const BYTE* pData, const BYTE* bMask, const char* szMask) {
	try {
		for (; *szMask; ++szMask, ++pData, ++bMask)
			if (*szMask == 'x' && *pData != *bMask)   return 0;
		return (*szMask) == NULL;
	}
	catch (...) {
		WaringGameNotice(0, 0, L"[Hook]Compare Error!");
	}
	return FALSE;
}

DWORD FindPattern(DWORD dwdwAdd, DWORD dwLen, BYTE *bMask, char * szMask) {
	try {
		for (DWORD i = 0; i<dwLen; i++)
			if (bCompare((BYTE*)(dwdwAdd + i), bMask, szMask))  return (DWORD)(dwdwAdd + i);
		return 0;

	}
	catch (...) {
		WaringGameNotice(0, 0, L"[Hook]Find Pattern Error");
	}
	return 0;
}

DWORD SearchSignature(PBYTE code, PCHAR szMask, DWORD dwStartAddress, int ID) {
	DWORD dwResult = 0;
	DWORD lpAddress = dwStartAddress;
	DWORD dwBestResult = 0;
	MEMORY_BASIC_INFORMATION lpBuffer;

	while (VirtualQueryEx((HANDLE)-1, (LPCVOID)lpAddress, &lpBuffer, sizeof(lpBuffer)) != 0) {
		if (lpBuffer.Protect == PAGE_EXECUTE_READ || lpBuffer.Protect == PAGE_EXECUTE_WRITECOPY) {
			dwResult = FindPattern((DWORD)lpBuffer.BaseAddress, lpBuffer.RegionSize, code, szMask);
			if (dwResult > dwBestResult) {
				dwBestResult = dwResult;
				break;
			}
		}
		lpAddress = lpAddress + lpBuffer.RegionSize;
	}
	if (dwBestResult == 0) {
		WaringGameNotice(0, 0, L"[Hook]Search Error id:%d", ID);
		return 0;
	}

	return dwBestResult;
}


 INT32 SearchSignature(std::string code, std::string szMask, int dwStartAddress, int ID)
{

	int dwResult = 0;
	int lpAddress = dwStartAddress;
	int dwBestResult = 0;
	MEMORY_BASIC_INFORMATION lpBuffer;
	Byte[] temp = Process.temp;

	while (VirtualQueryEx(gMrw->getHandle(), (uint)lpAddress, ref lpBuffer, System.Runtime.InteropServices.Marshal.SizeOf(typeof(MEMORY_BASIC_INFORMATION))) != 0)
	{

		if (lpBuffer.Protect != 1)
		{
			readData((uint)lpBuffer.BaseAddress, (uint)lpBuffer.RegionSize, temp);
			IntPtr vBytesAddress = Marshal.UnsafeAddrOfPinnedArrayElement(temp, 0);

			for (int i = 0; i < lpBuffer.RegionSize - szMask.Length; i++)
			{
				IntPtr t = vBytesAddress + i;
				bool flag = true;
				for (int j = 0; j < szMask.Length; j++)
				{
					if (szMask[j] != 'x')
						continue;
					if (Marshal.ReadByte(t + j) != code[j])
					{
						flag = false;
						break;
					}
				}
				if (flag == true)
				{
					return lpAddress + i;
				}
			}

			if (dwResult > dwBestResult)
			{
				dwBestResult = dwResult;
				break;
			}
			lpAddress = lpAddress + lpBuffer.RegionSize;
			if (lpAddress > 0x6000000)
				return 0;
		}
	}
	return dwBestResult;
}
	