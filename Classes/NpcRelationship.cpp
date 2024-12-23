#include "NpcRelationship.h"  
#include <iostream>  

// 构造函数  
NpcRelationship::NpcRelationship() {}

// 析构函数  
NpcRelationship::~NpcRelationship() {}

// 添加 NPC  
void NpcRelationship::add_npc(const std::string& npcName) {
    if (relationships.find(npcName) == relationships.end()) {
        relationships[npcName] = std::unordered_map<std::string, double>();
    }
}

// 移除 NPC  
void NpcRelationship::remove_npc(const std::string& npcName) {
    relationships.erase(npcName);
    for (auto& pair : relationships) {
        pair.second.erase(npcName);
    }
}

// 设置 NPC 之间的关系  
void NpcRelationship::setRelationship(const std::string& npcA, const std::string& npcB, double value) {
    add_npc(npcA);
    add_npc(npcB);
    relationships[npcA][npcB] = value;
    relationships[npcB][npcA] = value; // 关系是双向的  
}

// 增加 NPC 之间的关系  
void NpcRelationship::increaseRelationship(const std::string& npcA, const std::string& npcB, double amount) {
    double newValue = getRelationship(npcA, npcB) + amount;
    setRelationship(npcA, npcB, newValue);
}

// 减少 NPC 之间的关系  
void NpcRelationship::decreaseRelationship(const std::string& npcA, const std::string& npcB, double amount) {
    double newValue = getRelationship(npcA, npcB) - amount;
    setRelationship(npcA, npcB, newValue);
}

// 获取 NPC 之间的关系  
double NpcRelationship::getRelationship(const std::string& npcA, const std::string& npcB) const {
    auto itA = relationships.find(npcA);
    if (itA != relationships.end()) {
        auto itB = itA->second.find(npcB);
        if (itB != itA->second.end()) {
            return itB->second;
        }
    }
    return 0; // 默认关系值  
}

// 获取关系层级  
std::string NpcRelationship::getRelationshipLevel(const std::string& npcA, const std::string& npcB) const {
    int value = getRelationship(npcA, npcB);
    if (value < -50) {
        return "非常差";
    }
    else if (value < 0) {
        return "一般";
    }
    else if (value < 50) {
        return "友好";
    }
    else {
        return "亲密";
    }
}

// 打印所有 NPC 之间的关系  
void NpcRelationship::printRelationships() const {
    for (const auto& npcA : relationships) {
        for (const auto& npcB : npcA.second) {
            std::cout << npcA.first << " <-> " << npcB.first << ": " << npcB.second << std::endl;
        }
    }
}

// 增加礼物接受次数  
void NpcRelationship::AddGiftTime ( const std::string& npc ) {
    add_npc ( npc );
    // 找到该 NPC，并增加接受礼物的次数  
    GiftTime[npc]++;
}

// 获取该 NPC 接受的礼物次数  
int NpcRelationship::NpcGiftTIme ( const std::string& npc ) {
    // 查找并返回礼物次数，未记录则返回 0  
    return GiftTime[npc];
}

void NpcRelationship::updateGiftTime () {
    // 检查是否已经过了七天  
    if ((day - lastUpdateDay) >= 7) {
        // 重置所有NPC的GiftTime  
        for (auto& entry : GiftTime) {
            entry.second = 0; 
        }
        lastUpdateDay = day; // 更新最后一次更新的天数  
    }
}