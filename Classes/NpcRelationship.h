#pragma once

#include <unordered_map>
#include <string>
// #include "AppDelegate.h"

class AppDelegate;
extern int day;

using namespace std;

class NpcRelationship {
public:
	// 构造函数和析构函数
	NpcRelationship();
	~NpcRelationship();

	// 添加 / 移除NPC
	void add_npc(const string& npcName);
	void remove_npc(const string& npcName);

	// 设置npc之间的关系
	void setRelationship(const string& npcA, const string& npcB, double value);

	// 增加/减少关系  
	void increaseRelationship(const std::string& npcA, const std::string& npcB, double amount);
	void decreaseRelationship(const std::string& npcA, const std::string& npcB, double amount);

	// 获取关系层级  
	std::string getRelationshipLevel(const std::string& npcA, const std::string& npcB) const;

	// 获取npc之间的关系
	double getRelationship(const string& npcA, const string& npcB) const;

	// 打印所有npc之间的关系(用于调试)
	void printRelationships() const;

	// 送礼
	void AddGiftTime ( const std::string& npc );

	int NpcGiftTIme ( const std::string& npc );

	void NpcRelationship::updateGiftTime ();

private:
	unordered_map<string, unordered_map<string, double>> relationships;

	unordered_map<string , int> GiftTime;

	int lastUpdateDay = 0;

	// 关系值上下限  
	static const int MIN_RELATIONSHIP = -100;
	static const int MAX_RELATIONSHIP = 100;
};