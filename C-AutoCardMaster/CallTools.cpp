#include "stdafx.h"
#include "CallTools.h"

AssemblyTools* at;


void CallTools::Init()
{
	at = new AssemblyTools();
	//at->setTimer();
}
void CallTools::end()
{
	delete at;
}

INT32 CallTools::getLastChooseObj()
{
	return gMrw->readInt32(base_baseAddr, 3, 0x74, 0x18, 0);
}

INT32 CallTools::getObjPosPoint(INT32 obj)
{
	return obj + 0x1A0;
}

void CallTools::move()
{
	
	at->clear();
	at->pushad();
	at->push(0);
	at->push(0);
	at->push(0);
	at->push(0);
	at->push(gMrw->readInt32(base_mouse, 1, 0x14) + 0x10);
	at->push(2);
	at->mov_ecx(gMrw->readInt32(base_MyHero));
	at->mov_eax(call_attack);
	at->call_eax();
	at->popad();
	at->mov_virtualaddr_c3();
	at->retn();
	at->RunRemoteThread();
}

void CallTools::test()
{
	at->clear();
	at->pushad();
	at->push(0);
	at->push(0);
	at->push(0);
	at->push(0);
	at->mov_eax((int)MessageBoxW);
	at->call_eax();
	at->popad();
	at->mov_virtualaddr_c3();
	at->retn();
	at->RunRemoteThread();
}

void CallTools::attack(INT32 obj)
{
	at->clear();
	at->pushad();
	at->push(0);
	at->push(0);
	at->push(0);
	at->push(obj);
	at->push(CallTools::getObjPosPoint(obj));
	at->push(3);
	at->mov_ecx(gMrw->readInt32(base_MyHero));
	at->mov_eax(call_attack);
	at->call_eax();
	at->popad();
	at->mov_virtualaddr_c3();
	at->retn();
	at->RunRemoteThread();
}

float CallTools::getMyHeroAttackSpeed()
{
	return gMrw->readFloat(gMrw->readInt32(base_baseAddr, 3, 0x80, 0x4, 0x170) + 0x18);
}

float CallTools::getMyHeroAttack()
{
	return gMrw->readFloat(gMrw->readInt32(base_baseAddr, 3, 0x80, 0x4, 0x170) + 0x10);
}

float CallTools::getObjHp(INT32 obj)
{
	return gMrw->readFloat(obj + offset_Hp);
}

float CallTools::getObjCamp(INT32 obj)
{
	return gMrw->readInt32(obj + offset_camp);
}

float CallTools::getObjType(INT32 obj)
{
	return gMrw->readInt32(obj + offset_type );
}


float CallTools::getAttackArea(INT32 obj) {
	return gMrw->readFloat(obj + offset_AttackArea);
}

float CallTools::getObjInstance(INT32 obj1, INT32 obj2)
{
	INT32 p1 = getObjPosPoint(obj1);
	INT32 p2 = getObjPosPoint(obj2);

	POSITION ps1, ps2;
	gMrw->readData(p1, (LPBYTE)&ps1, 12);
	gMrw->readData(p2, (LPBYTE)&ps2, 12);

	return sqrtf((ps1.x - ps2.x) * (ps1.x - ps2.x) + (ps1.y - ps2.y) * (ps1.y - ps2.y) + (ps1.z - ps2.z) * (ps1.z - ps2.z));
}



INT32 CallTools::getBestAttackObj(INT32 objType)
{
	INT32 myObj = gMrw->readInt32(base_MyHero);
	float attackArea = CallTools::getAttackArea(myObj);
	INT32 myCamp = CallTools::getObjCamp(myObj);
	INT32 bestObj = 0;

	for (int i = gMrw->readInt32(base_tabel); i < gMrw->readInt32(base_tabel + 4); i += 4) {
		INT32 obj = gMrw->readInt32(i);
		if (getObjType(obj) != objType)
			continue;
		if (myCamp == getObjCamp(obj))
			continue;
		if (getObjInstance(myObj, obj) > attackArea)
			continue;
		if (getObjHp(obj) <= 0)
			continue;
		if (bestObj == 0) bestObj = obj;
		else {
			if (getObjHp(bestObj) > getObjHp(obj))
				bestObj = obj;
		}
	}
	return bestObj;
}
