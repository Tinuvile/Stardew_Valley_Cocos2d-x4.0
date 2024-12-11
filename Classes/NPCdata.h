#ifndef NPCDATA_H  
#define NPCDATA_H  

#include <vector>  
#include <string>  
#include "cocos2d.h"  

using namespace cocos2d;

// ��ȡ NPC ����֡��Ϣ�ĺ���  
std::vector<std::vector<std::string>> getAbigailAnimations () {
    return {
        {"npc/Abigail/Abigail-8.png", "npc/Abigail/Abigail-9.png", "npc/Abigail/Abigail-10.png", "npc/Abigail/Abigail-11.png"},
        {"npc/Abigail/Abigail-0.png", "npc/Abigail/Abigail-1.png", "npc/Abigail/Abigail-2.png", "npc/Abigail/Abigail-3.png"},
        {"npc/Abigail/Abigail-14.png", "npc/Abigail/Abigail-13.png", "npc/Abigail/Abigail-14.png", "npc/Abigail/Abigail-15.png"},
        {"npc/Abigail/Abigail-4.png", "npc/Abigail/Abigail-5.png", "npc/Abigail/Abigail-6.png", "npc/Abigail/Abigail-7.png"}
    };
}

#endif // NPCDATA_H