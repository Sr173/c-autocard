#pragma once
class MemRWer {
public:
	MemRWer(HANDLE hProcess);
	~MemRWer();
private:
	HANDLE mHProcess;
public:
	HANDLE getHandle();

	INT8 readInt8(size_t baseAddress);
	INT16 readInt16(size_t baseAddress);
	INT32 readInt32(INT32 baseAddress, std::initializer_list<INT32> il);
	INT32 readInt32(size_t baseAddress, INT32 count, ...);
	INT32 readInt32(size_t baseAddress);
	INT64 readInt64(size_t baseAddress);
	float readFloat(size_t baseAddress);
	void readData(size_t baseAddress, LPBYTE out, INT32 length);

	BOOL writeData(size_t lpBaseAddress, LPVOID datain, INT32 length);
	BOOL writeInt8(size_t lpBaseAddress, INT8 value);
	BOOL writeInt16(size_t lpBaseAddress, INT16 value);
	BOOL writeInt32(size_t lpBaseAddress, INT32 value);
	BOOL writeInt64(size_t lpBaseAddress, INT64 value);
	BOOL writeFloat(size_t lpBaseAddress, float value);
	BOOL writeDnfTypeAddr(size_t lpBaseAddress, INT32 addr, INT32 types);
};

