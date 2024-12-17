#pragma once
#include "cocos2d.h"  
#include "Inventory.h"  
#include "AppDelegate.h"

class TaskManagement {
public:
	/* ��ʼ��Ϣ
	*  �������ࣺNPC������ϵͳ������������䷢��
	*  NPC�����򴫵�NPC����
	*  �������ݣ�NPC������ϵͳ�������ṩ��Ҫ����Ʒ��������䵥���ṩ
	*  ������NPC�����ӽ�һ���Ʒ�Լ���Ӧ�øжȣ�ϵͳ�����ӽ�ң�������䷢�����������˵ĺøж��Լ������ռ���Ʒ����
	*/
	enum TaskType {
		NPC_TASK,
		SYSTEM_TASK,
		FESTIVAL_TASK
	};

	struct Task {
		std::string name;               // ��������  
		TaskType type;                  // ��������  
		std::string npcName;            // ��������� NPC ���֣�NPC_TASK ʹ�ã�  
		std::vector<Item> requiredItems;// ��Ҫ����Ʒ����ѡ��  
		int rewardCoins;                // ������ң�SYSTEM_TASK �� NPC_TASK ʹ�ã�  
		std::vector<Item> specialRewards; // ������������ռ���Ʒ��FESTIVAL_TASK ʹ�ã�  
		float relationshipPoints;       // ��Ӧ�ĺøжȣ�NPC_TASK �� FESTIVAL_TASK ʹ�ã�  

		Task ( const std::string& name , TaskType type )
			: name ( name ) , type ( type ) , rewardCoins ( 0 ) , relationshipPoints ( 0.0f ) {
		}
	};

	TaskManagement() {}

	// ��������  
	void createTask ( const Task& task );

	// ������񲢴�����  
	void completeTask ( const Task& task );

protected:

	std::vector<Task> tasks;              // �洢���������  
	NPC* npc;

};