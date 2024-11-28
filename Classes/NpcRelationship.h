#ifndef NPC_RELATIONSHIP_H  
#define NPC_RELATIONSHIP_H  

#include <unordered_map>
#include <string>

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
	void setRelationship(const string& npcA, const string& npcB, int value);

	// ����/���ٹ�ϵ  
	void increaseRelationship(const std::string& npcA, const std::string& npcB, int amount);
	void decreaseRelationship(const std::string& npcA, const std::string& npcB, int amount);

	// ��ȡ��ϵ�㼶  
	std::string getRelationshipLevel(const std::string& npcA, const std::string& npcB) const;

	// ��ȡnpc֮��Ĺ�ϵ
	int getRelationship(const string& npcA, const string& npcB) const;

	// ��ӡ����npc֮��Ĺ�ϵ(���ڵ���)
	void printRelationships() const;

private:
	unordered_map<string, unordered_map<string, int>>relationships;

	// ��ϵֵ������  
	static const int MIN_RELATIONSHIP = -100;
	static const int MAX_RELATIONSHIP = 100;
};

#endif  // NPC_RELATIONSHIP_H