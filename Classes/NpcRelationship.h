#ifndef NPC_RELATIONSHIP_H  
#define NPC_RELATIONSHIP_H  

#include <unordered_map>
#include <string>

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
	void setRelationship(const string& npcA, const string& npcB, int value);

	// 增加/减少关系  
	void increaseRelationship(const std::string& npcA, const std::string& npcB, int amount);
	void decreaseRelationship(const std::string& npcA, const std::string& npcB, int amount);

	// 获取关系层级  
	std::string getRelationshipLevel(const std::string& npcA, const std::string& npcB) const;

	// 获取npc之间的关系
	int getRelationship(const string& npcA, const string& npcB) const;

	// 打印所有npc之间的关系(用于调试)
	void printRelationships() const;

private:
	unordered_map<string, unordered_map<string, int>>relationships;

	// 关系值上下限  
	static const int MIN_RELATIONSHIP = -100;
	static const int MAX_RELATIONSHIP = 100;
};

#endif  // NPC_RELATIONSHIP_H