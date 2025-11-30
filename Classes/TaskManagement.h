#pragma once
#include "cocos2d.h" 
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
		std::vector<Item> requiredItems; // ��Ҫ����Ʒ����ѡ��
		int rewardCoins;                // ������ң�SYSTEM_TASK �� NPC_TASK ʹ�ã�
		std::vector<Item> specialRewards; // ������������ռ���Ʒ��FESTIVAL_TASK ʹ�ã�  
		float relationshipPoints;       // ��Ӧ�ĺøжȣ�NPC_TASK �� FESTIVAL_TASK ʹ�ã�  
		std::string description;        // ������ϸ˵��  
		std::string startSeason;          // �����ʼ����  
		std::string endSeason;            // �����������  

		Task ( const std::string& name , TaskType type , const std::string& desc , const std::string& start , const std::string& end )
			: name ( name ) , type ( type ) , rewardCoins ( 0 ) , relationshipPoints ( 0.0f ) , description ( desc ) , startSeason ( start ) , endSeason ( end ) {
		}
	};

	TaskManagement ();

	// ��������  
	void createTask ( const Task& task );

	// ��ȡ�Ѿ�����������
	std::vector<Task> returnTasks () { return tasks; }

	// ��ȡ�Ѿ����ܵ�����
	std::vector<Task> returnAcceptTasks () { return acceptTasks; }

	// �����ѽ��ܵ�����
	void AddAcceptTask ( const Task& task );

	// ������񲢴�������  
	void completeTask ( const std::string& task_name );

	//������ܺ�ӷ���������ɾ��
	void DeleteAcceptTask ( const Task& task );

	// ������Ʒ��Ӧ������
	std::string findTaskByRequiredItems ( const std::string& itemName );

protected:

	std::vector<Task> tasks;              // �洢���������

	std::vector<Task> acceptTasks;        // �����ѽ������������

};