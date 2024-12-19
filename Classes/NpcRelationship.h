#pragma once

#include <unordered_map>
#include <string>
// #include "AppDelegate.h"

class AppDelegate;
extern int day;

using namespace std;

class NpcRelationship {
public:
	// ���캯������������
	NpcRelationship();
	~NpcRelationship();

	// ��� / �Ƴ�NPC
	void add_npc(const string& npcName);
	void remove_npc(const string& npcName);

	// ����npc֮��Ĺ�ϵ
	void setRelationship(const string& npcA, const string& npcB, double value);

	// ����/���ٹ�ϵ  
	void increaseRelationship(const std::string& npcA, const std::string& npcB, double amount);
	void decreaseRelationship(const std::string& npcA, const std::string& npcB, double amount);

	// ��ȡ��ϵ�㼶  
	std::string getRelationshipLevel(const std::string& npcA, const std::string& npcB) const;

	// ��ȡnpc֮��Ĺ�ϵ
	double getRelationship(const string& npcA, const string& npcB) const;

	// ��ӡ����npc֮��Ĺ�ϵ(���ڵ���)
	void printRelationships() const;

	// ����
	void AddGiftTime ( const std::string& npc );

	int NpcGiftTIme ( const std::string& npc );

	void NpcRelationship::updateGiftTime ();

private:
	unordered_map<string, unordered_map<string, double>> relationships;

	unordered_map<string , int> GiftTime;

	int lastUpdateDay = 0;

	// ��ϵֵ������  
	static const int MIN_RELATIONSHIP = -100;
	static const int MAX_RELATIONSHIP = 100;
};