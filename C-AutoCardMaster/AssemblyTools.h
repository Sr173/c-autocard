#pragma once


class AssemblyTools
{
private:
	INT32 virtualAddr = 0;
	std::vector<byte> code;
public:
	
	AssemblyTools();
	~AssemblyTools();
	virtual inline void clear() { code.clear(); }
	virtual inline void writeInt8(byte data) { code.push_back(data); }
	virtual inline void writeInt16(INT16 data) { 
		byte* pb = (byte*)&data;
		for (int i = 0; i < 2; i++) {
			code.push_back(pb[i]);
		}
	}
	virtual inline void writeInt32(INT32 data) {
		byte* pb = (byte*)&data;
		for (int i = 0; i < 4; i++) {
			code.push_back(pb[i]);
		}
	}
	void retn();
	virtual inline void pushad() { writeInt8(0x60); }
	virtual inline void pushfd() { writeInt8(0x9C); }
	virtual inline void popfd() { writeInt8(0x9D); }
	virtual inline void popad() { writeInt8(0x61); }
	virtual inline void mov_ecx(INT32 data) {writeInt8(0xB9);writeInt32(data);}
	virtual inline void mov_eax(INT32 data) { writeInt8(0xB8); writeInt32(data); }
	virtual inline void push(INT32 data) {writeInt8(0x68);writeInt32(data);}
	virtual inline void call_eax() {writeInt8(0xFF);writeInt8(0xD0);}
	virtual inline void call_addr(INT32 addr) {writeInt8(0xFF);writeInt8(0x15);writeInt32(addr);}
	virtual inline void mov_virtualaddr_c3() { writeInt8(0xC7);writeInt8(0x05);writeInt32(virtualAddr + 0x990);writeInt32(virtualAddr + 0x9A0);}
	void RunRemoteThread(bool IsMainThread = true) const;
	void setTimer();

};

