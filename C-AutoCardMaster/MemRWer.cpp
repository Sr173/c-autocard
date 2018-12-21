#include "stdafx.h"
#include "MemRWer.h"
#include "initializer_list"



MemRWer::MemRWer(HANDLE hProcess) :mHProcess(hProcess) {}
MemRWer::~MemRWer() {
	//CloseHandle(mHProcess);
	//gMrw = NULL;
}

HANDLE MemRWer::getHandle() {
	return mHProcess;
}

INT8 MemRWer::readInt8(size_t baseAddress) {
	VM_START;
	INT8 ret = -1;
	ReadProcessMemory(mHProcess, (LPVOID)baseAddress, &ret, 1, nullptr);
	VM_END;
	return ret;
}


INT16 MemRWer::readInt16(size_t baseAddress) {
	VM_START;
	INT16 ret = -1;
	ReadProcessMemory(mHProcess, (LPVOID)baseAddress, &ret, 2, nullptr);
	VM_END;
	return ret;
}

INT32 MemRWer::readInt32(INT32 baseAddress,std::initializer_list<INT32> il) {

	INT32 ret = -1;
	if (!ReadProcessMemory(mHProcess, (LPVOID)baseAddress, &ret, 4, nullptr)) {
		return ret;
	}
	for (auto i : il) {
		ReadProcessMemory(mHProcess, (LPVOID)(ret + i), &ret, 4, nullptr);
	}
	return ret;
}

INT32 MemRWer::readInt32(size_t baseAddress, INT32 count, ...) {
	VM_START;
	va_list arg_ptr;
	va_start(arg_ptr, count);
	INT32 ret = -1;
	if (!ReadProcessMemory(mHProcess, (LPVOID)baseAddress, &ret, 4, nullptr)) {
		//WCHAR text[40];
		//swprintf_s(text, L"ReadProcessMemory error %d", GetLastError());
		//MessageBox(nullptr, text, L"", 0);
		return ret;
	}
	for (int i = 0; i < count; i++) {
		ReadProcessMemory(mHProcess, (LPVOID)(ret + va_arg(arg_ptr, size_t)), &ret, 4, nullptr);
	}
	va_end(arg_ptr);
	VM_END;
	return ret;
}

INT32 MemRWer::readInt32(size_t baseAddress) {
	return readInt32(baseAddress, 0);
}

INT64 MemRWer::readInt64(size_t baseAddress) {
	VM_START;
	INT64 ret = -1;
	ReadProcessMemory(mHProcess, (LPVOID)baseAddress, &ret, 8, nullptr);
	VM_END;
	return ret;
}

float MemRWer::readFloat(size_t baseAddress) {
	VM_START;
	float ret = -1;
	ReadProcessMemory(mHProcess, (LPVOID)baseAddress, &ret, 4, nullptr);
	VM_END;
	return ret;
}

void MemRWer::readData(size_t baseAddress, LPBYTE out, INT32 length) {
	VM_START;
	ReadProcessMemory(mHProcess, (LPVOID)baseAddress, out, length, nullptr);
	VM_END;
}

BOOL MemRWer::writeData(size_t lpBaseAddress, LPVOID datain, INT32 length) {
	VM_START;
	BOOL b = WriteProcessMemory(mHProcess, (LPVOID)lpBaseAddress, (LPBYTE)datain, length, nullptr);
	VM_END;
	return b;
}

BOOL MemRWer::writeInt8(size_t lpBaseAddress, INT8 value) {
	VM_START;
	BOOL b = WriteProcessMemory(mHProcess, (LPVOID)lpBaseAddress, &value, 1, nullptr);
	VM_END;
	return b;
}

BOOL MemRWer::writeInt16(size_t lpBaseAddress, INT16 value) {
	VM_START;
	BOOL b = WriteProcessMemory(mHProcess, (LPVOID)lpBaseAddress, &value, 2, nullptr);
	VM_END;
	return b;
}

BOOL MemRWer::writeInt32(size_t lpBaseAddress, INT32 value) {
	VM_START;
	BOOL b = WriteProcessMemory(mHProcess, (LPVOID)lpBaseAddress, &value, 4, nullptr);
	VM_END;
	return b;
}

BOOL MemRWer::writeInt64(size_t lpBaseAddress, INT64 value) {
	VM_START;
	BOOL b = WriteProcessMemory(mHProcess, (LPVOID)lpBaseAddress, &value, 8, nullptr);
	VM_END;
	return b;
}


BOOL MemRWer::writeDnfTypeAddr(size_t lpBaseAddress, INT32 addr, INT32 types) {
	VM_START;
	BYTE data[12];
	*((int*)data) = addr;
	*((int*)(data + 0x04)) = addr + types;
	*((int*)(data + 0x08)) = addr + types;
	BOOL b = WriteProcessMemory(mHProcess, (LPVOID)lpBaseAddress, &data, 12, nullptr);
	VM_END;
	return b;
}

BOOL MemRWer::writeFloat(size_t lpBaseAddress, float value) {
	VM_START;
	BOOL b = WriteProcessMemory(mHProcess, (LPVOID)lpBaseAddress, &value, 4, nullptr);
	VM_END;
	return b;
}

