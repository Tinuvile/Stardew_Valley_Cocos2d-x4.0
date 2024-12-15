#include "NpcRelationship.h"  
#include <iostream>  

// ���캯��  
NpcRelationship::NpcRelationship() {}

// ��������  
NpcRelationship::~NpcRelationship() {}

// ��� NPC  
void NpcRelationship::add_npc(const std::string& npcName) {
    if (relationships.find(npcName) == relationships.end()) {
        relationships[npcName] = std::unordered_map<std::string, int>();
    }
}

// �Ƴ� NPC  
void NpcRelationship::remove_npc(const std::string& npcName) {
    relationships.erase(npcName);
    for (auto& pair : relationships) {
        pair.second.erase(npcName);
    }
}

// ���� NPC ֮��Ĺ�ϵ  
void NpcRelationship::setRelationship(const std::string& npcA, const std::string& npcB, int value) {
    add_npc(npcA);
    add_npc(npcB);
    relationships[npcA][npcB] = value;
    relationships[npcB][npcA] = value; // ��ϵ��˫���  
}

// ���� NPC ֮��Ĺ�ϵ  
void NpcRelationship::increaseRelationship(const std::string& npcA, const std::string& npcB, int amount) {
    int newValue = getRelationship(npcA, npcB) + amount;
    setRelationship(npcA, npcB, newValue);
}

// ���� NPC ֮��Ĺ�ϵ  
void NpcRelationship::decreaseRelationship(const std::string& npcA, const std::string& npcB, int amount) {
    int newValue = getRelationship(npcA, npcB) - amount;
    setRelationship(npcA, npcB, newValue);
}

// ��ȡ NPC ֮��Ĺ�ϵ  
int NpcRelationship::getRelationship(const std::string& npcA, const std::string& npcB) const {
    auto itA = relationships.find(npcA);
    if (itA != relationships.end()) {
        auto itB = itA->second.find(npcB);
        if (itB != itA->second.end()) {
            return itB->second;
        }
    }
    return 0; // Ĭ�Ϲ�ϵֵ  
}

// ��ȡ��ϵ�㼶  
std::string NpcRelationship::getRelationshipLevel(const std::string& npcA, const std::string& npcB) const {
    int value = getRelationship(npcA, npcB);
    if (value < -50) {
        return "�ǳ���";
    }
    else if (value < 0) {
        return "һ��";
    }
    else if (value < 50) {
        return "�Ѻ�";
    }
    else {
        return "����";
    }
}

// ��ӡ���� NPC ֮��Ĺ�ϵ  
void NpcRelationship::printRelationships() const {
    for (const auto& npcA : relationships) {
        for (const auto& npcB : npcA.second) {
            std::cout << npcA.first << " <-> " << npcB.first << ": " << npcB.second << std::endl;
        }
    }
}