#pragma once
#include "AssemblyTools.h"

#ifndef CallTools_H
#define CallTools_H

class CallTools
{
public:
	static void Init();
	static void end();

	static INT32 getLastChooseObj();
	static INT32 getObjPosPoint(INT32 obj);
	static void move();
	static void test();
	static void attack(INT32 obj);
	static float getMyHeroAttackSpeed();
	static float getMyHeroAttack();
	static float getObjHp(INT32 obj);
	static float getObjCamp(INT32 obj);
	static float getObjType(INT32 obj);
	static float getAttackArea(INT32 obj);
	static float getObjInstance(INT32 obj1,INT32 obj2);
	static INT32 getBestAttackObj(INT32 objType);

	struct POSITION {
		float x;
		float y;
		float z;
	};

	//static AssemblyTools* at;

private:

};
#endif

