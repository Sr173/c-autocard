#include "stdafx.h"
#include "game.h"
#include "MemRWer.h"
#include "resource.h"
#include "CallTools.h"
#include "thread"

const int CARD_NULL = 0x492F4455;
const int CARD_RED = 0x2E646572;
const int CARD_YELLOW = 0x646C6F67;
const int CARD_BLUE = 0x65756C62;

bool IsBeginFlag = false;
HANDLE t_main = NULL;


struct card_data {
	int key;
	int color;
	bool flag = false;
};

card_data keys[4] = {
	{'E', CARD_RED,false},
	{'W', CARD_YELLOW,false},
	{'B', CARD_BLUE , false},
	{'R', CARD_YELLOW,false}
	
};

bool key_flag[100];

bool MyGetKeyState(int keys) {
	return ((GetKeyState(keys) & 0x8000) != 0) ? true : false;
}

void press_w() {
	keybd_event('W', MapVirtualKey('W', 0), 2, 0);
	Sleep(1);
	keybd_event('W', MapVirtualKey('W', 0), 0, 0);
	Sleep(1);
	keybd_event('W', MapVirtualKey('W', 0), 2, 0);
}

INT32 GetSkillState() {
	return gMrw->readInt8(gMrw->readInt32(base_baseAddr, 2 ,0x8, 0x8) + 0xF4);
}

void GetCard(INT32 data,INT32 key) {
	bool Isbegin = false;
	if (gMrw->readInt32(base_IsCheat, { 0x7C }) == 1 || GetSkillState() != 0 || Isbegin || gMrw->readInt32(base_baseAddr, 5, 0x8, 0x8, 0x24, 0x4, 0x1F) != CARD_NULL)
		return;
	if (key != 'W')
		press_w();
	Isbegin = true;
	INT32 time = 0;

	//gMrw->readInt32(base_baseAddr, { 1,2,3 });

	while (gMrw->readInt32(base_baseAddr, 5 ,0x8, 0x8, 0x24,0x4,0x1F) != data) {
		Sleep(1);
		if (time++ >= 5000) {
			Isbegin = false;
			return;
		}
	}

	press_w();
	Sleep(1000);
	Isbegin = false;

	if (data == CARD_RED) {
		int current = GetDlgItemInt(gMainHwnd, IDC_STATIC_red, 0, 0);
		SetDlgItemInt(gMainHwnd, IDC_STATIC_red, current + 1, 0);
	}else 	if (data == CARD_BLUE) {
		int current = GetDlgItemInt(gMainHwnd, IDC_STATIC_blue, 0, 0);
		SetDlgItemInt(gMainHwnd, IDC_STATIC_blue, current + 1, 0);
	}
	else if (data == CARD_YELLOW) {
		int current = GetDlgItemInt(gMainHwnd, IDC_STATIC_yellow, 0, 0);
		SetDlgItemInt(gMainHwnd, IDC_STATIC_yellow, current + 1, 0);
	}
}

DWORD WINAPI walk_attack(LPVOID) {
	//return 0;
	INT32 lastAttackTime = 0;
	INT32 currentSleleteObj = CallTools::getLastChooseObj();
	while (1) {

		if (MyGetKeyState(VK_SPACE)) {
			if (IsDlgButtonChecked(gMainHwnd, IDC_CHECK3) == BST_CHECKED) {
				CallTools::attack(CallTools::getLastChooseObj());
			}
			else {
				INT32 bestObj = CallTools::getBestAttackObj(0x18);
				if (bestObj != 0) {
					{
						if (GetTickCount() > (lastAttackTime + (INT32)(1000.0 / CallTools::getMyHeroAttackSpeed()) + 10)) {
							CallTools::attack(bestObj);
							lastAttackTime = GetTickCount();
						}
						else if (GetTickCount() > (lastAttackTime + (INT32)((1000.0 / CallTools::getMyHeroAttackSpeed()) * 0.25)) + 10) {
							CallTools::move();
						}
					}
				}
			}
			////if (currentSleleteObj == 0) continue;
			//if (GetTickCount() > (lastAttackTime + (INT32)(1000.0 / CallTools::getMyHeroAttackSpeed()) + 10)) {
			//	CallTools::attack(CallTools::getLastChooseObj());
			//	lastAttackTime = GetTickCount();
			//}
			//else if (GetTickCount() > (lastAttackTime + (INT32)((1000.0 / CallTools::getMyHeroAttackSpeed()) * 0.25)) + 10) CallTools::move();
		}
		if (MyGetKeyState('A')) {
			INT32 bestObj = CallTools::getBestAttackObj(0xC01);

			if (bestObj != 0 && CallTools::getObjHp(bestObj) <= CallTools::getMyHeroAttack()) {
				if (GetTickCount() > (lastAttackTime + (INT32)(1000.0 / CallTools::getMyHeroAttackSpeed()) + 10)) {
					CallTools::attack(bestObj);
					lastAttackTime = GetTickCount();
				}
			}
		}

		if (MyGetKeyState(VK_PRIOR) && !key_flag[0])
		{
			key_flag[0] = true;
			float data = gMrw->readFloat(gMrw->readInt32(base_game, 1, 0x10C) + 0x258);
			data -= 100;
			gMrw->writeFloat(gMrw->readInt32(base_game, 1, 0x10C) + 0x258, data);
		}
		if (MyGetKeyState(VK_NEXT) && !key_flag[1]) {
			key_flag[1] = true;
			float data = gMrw->readFloat(gMrw->readInt32(base_game, 1, 0x10C) + 0x258);
			data += 100;
			gMrw->writeFloat(gMrw->readInt32(base_game, 1, 0x10C) + 0x258, data);
		}

		if (!MyGetKeyState(VK_PRIOR))
			key_flag[0] = false;
		if (!MyGetKeyState(VK_NEXT))
			key_flag[1] = false;

		//if (!MyGetKeyState(VK_SPACE))lastAttackTime = 0;
		//if (!MyGetKeyState('A'))lastAttackTime = 0;

		Sleep(1);
	}
	return 0;
}

DWORD WINAPI main_thread(LPVOID) {

	keys[0].color = CARD_RED;
	keys[1].color = CARD_YELLOW;
	keys[2].color = CARD_BLUE;


	int twice = 3;

	while (1) {
		for (int i = 0; i < twice; i++) {
			if (MyGetKeyState(keys[i].key) && !keys[i].flag && !MyGetKeyState((int)VK_CONTROL)) {
				GetCard(keys[i].color, keys[i].key);
			}
		}
		for (int i = 0; i < twice; i++) {
			if (!MyGetKeyState(keys[i].key))
				keys[i].flag = false;
		}

		if (MyGetKeyState(VK_HOME) && !key_flag[2]) {
			key_flag[2] = true;

			float f = CallTools::getObjInstance(CallTools::getLastChooseObj(), gMrw->readInt32(base_MyHero));
			WCHAR temp[100];
		}

		if (!MyGetKeyState(VK_PRIOR))
			key_flag[0] = false;
		if (!MyGetKeyState(VK_NEXT))
			key_flag[1] = false;
		if (!MyGetKeyState(VK_HOME))
			key_flag[2] = false;
		Sleep(1);
	}
}

void begin() {


	lHwnd = FindWindow(L"RiotWindowClass", L"League of Legends (TM) Client");
	DWORD pid;
	GetWindowThreadProcessId(lHwnd, &pid);
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, pid);

	gMrw = new MemRWer(hProcess);
	CallTools::Init();
	

	WCHAR temp[10];

	HWND hEdit = GetDlgItem(gMainHwnd, IDC_EDIT1);
	Edit_SetReadOnly(hEdit, true);
	Edit_GetText(hEdit, temp, 10);
	keys[0].key = temp[0];

	hEdit = GetDlgItem(gMainHwnd, IDC_EDIT2);
	Edit_SetReadOnly(hEdit, true);
	Edit_GetText(hEdit, temp, 10);
	keys[1].key = temp[0];

	hEdit = GetDlgItem(gMainHwnd, IDC_EDIT3);
	Edit_SetReadOnly(hEdit, true);
	Edit_GetText(hEdit, temp, 10);
	keys[2].key = temp[0];

	SetDlgItemInt(gMainHwnd, IDC_STATIC_yellow, 0, 0);
	SetDlgItemInt(gMainHwnd, IDC_STATIC_red, 0, 0);
	SetDlgItemInt(gMainHwnd, IDC_STATIC_blue, 0, 0);

	SetDlgItemText(gMainHwnd, IDC_STATIC_s, L"已经开始");

	if (IsDlgButtonChecked(gMainHwnd, IDC_CHECK3) == BST_CHECKED)
		hCard = CreateThread(0, 0, main_thread , 0, 0, 0);
	
	hAttack = CreateThread(0, 0, walk_attack, 0, 0, 0);;

}

void end() {

	HWND hEdit = GetDlgItem(gMainHwnd, IDC_EDIT1);
	Edit_SetReadOnly(hEdit, false);

	hEdit = GetDlgItem(gMainHwnd, IDC_EDIT2);
	Edit_SetReadOnly(hEdit, false);

	hEdit = GetDlgItem(gMainHwnd, IDC_EDIT3);
	Edit_SetReadOnly(hEdit, false);

	TerminateThread(hCard, 0);
	CloseHandle(t_main);
	TerminateThread(hAttack, 0);
	CloseHandle(t_main);

	SetDlgItemText(gMainHwnd, IDC_STATIC_s, L"未开始");

	delete gMrw;
	CallTools::end();
}

VOID CALLBACK sj(HWND, UINT, UINT_PTR, DWORD) {
	if (IsDlgButtonChecked(gMainHwnd, IDC_CHECK2) == BST_CHECKED)
		if (gMrw->readInt8(gMrw->readInt32(base_mouse, 1, 0x34) + 0x54) == 0)
			gMrw->writeInt8(gMrw->readInt32(base_mouse, 1, 0x34) + 0x54, 1);
}

VOID CALLBACK mainTimer(HWND, UINT, UINT_PTR, DWORD) {
	if (IsBeginFlag == false && FindWindow(L"RiotWindowClass", L"League of Legends (TM) Client")) {
		IsBeginFlag = true;
		begin();
		SetTimer(gMainHwnd, 0x1001, 1000, sj);
	}
	if (IsBeginFlag == true && !FindWindow(L"RiotWindowClass", L"League of Legends (TM) Client")) {
		IsBeginFlag = false;
		end();
		KillTimer(gMainHwnd, 0x1001);
	}
}

