//#pragma once
//#define base_baseAddr 0x25C814C//6A 01 85 C9 74 0A
//#define base_IsCheat 0x322C1B4//83 3D ?? ?? ?? ?? 01 57
//
//#define base_IsFours 0x33A8FC4
//#define base_game 0x321F56C//6A 44 FF 35 ?? ?? ?? ?? E8 ?? ?? ?? ?? 83 C4 08 C7 05 ?? ?? ?? ?? 00 00 00 00 C3
//
//#define base_mouse 0x1985E18//74 15 83 E8 01 75 10
//#define call_attack 0x005C8B80//6A 10 E8 ?? ?? ?? ?? B0 01 5F 5E 5D 5B
//
//#define base_MyHero 0x321EAA4//0F 84 63 02 00 00 53 55 56
//#define base_tabel 0x1974F8C//8B C8 2B CE C1 F9 02 83 F9 1E
//
//#define offset_Hp 0x678//当前Hp
//#define offset_HpMax 0x688//最大Hp
//#define offset_AttackArea 0xA7C
//#define offset_HeroName 0x780
//
//#define offset_type 0x18 //0x2401是建筑物 0xc01是小兵
//#define offset_camp 0x14 //unit类型 0x12c是中立 值0x64天灾方 0xC8近卫方

#define base_baseAddr 0x273CD00//6A 01 85 C9 74 0A
#define base_IsCheat 0x1AED9C0//83 3D ?? ?? ?? ?? 01 57

#define base_IsFours 0x33A8FC4
#define base_game 0x32CE25C//6A 44 FF 35 ?? ?? ?? ?? E8 ?? ?? ?? ?? 83 C4 08 C7 05 ?? ?? ?? ?? 00 00 00 00 C3

#define base_mouse 0x1AF0270//74 15 83 E8 01 75 10

//0087DE67    6A 01           push 0x1
//0087DE69    6A 00           push 0x0
//0087DE6B    6A 00           push 0x0
//0087DE6D    6A 00           push 0x0
//0087DE6F    8D81 E0010000   lea eax, dword ptr ds : [ecx + 0x1E0]
//0087DE75    50              push eax
//0087DE76    6A 0A           push 0xA
//0087DE78    E8 3337D4FF     call 005C15B0
#define call_attack 0x005C15B0//6A 01 6A 00 6A 00 6A 00 8D 81 E0 01 00 00 50 6A 0A



#define base_MyHero 0x338F7D4//0F 84 63 02 00 00 53 55 56
#define base_tabel 0x1AF057C//8B C8 2B CE C1 F9 02 83 F9 1E

#define offset_Hp 0xDD4//当前Hp
#define offset_HpMax 0xDE4//最大Hp
#define offset_AttackArea 0x1888
#define offset_HeroName 0x780

#define offset_type 0x70 //0x2401是建筑物 0xc01是小兵
#define offset_camp 0x44 //unit类型 0x12c是中立 值0x64天灾方 0xC8近卫方

//4.23
//#pragma once
//#define base_baseAddr 0x25D6BEC//6A 01 85 C9 74 0A
//#define base_IsCheat 0x323D28C
//#define base_IsFours 0x33A8FC4
//#define base_game 0x322DFC4
//
//#define base_mouse 0x1989A94
//#define call_attack 0x005C8360//6A 10 E8 ?? ?? ?? ?? B0 01 5F 5E 5D 5B
//
//#define base_MyHero 0x3231A7C
//#define base_tabel 0x1989E1C
//
//#define offset_Hp 0x678//当前Hp
//#define offset_HpMax 0x688//最大Hp
//#define offset_AttackArea 0xAA8
//
//
//#define offset_type 0x18 //0x2401是建筑物 0xc01是小兵
//#define offset_camp 0x14 //unit类型 0x12c是中立 值0x64天灾方 0xC8近卫方

