#pragma once
#include "cocos2d.h" 
 #include "AppDelegate.h"


class TaskManagement {
public:
	/* 初始信息
	*  任务种类：NPC发布、系统发布、节日庆典发布
	*  NPC发布则传递NPC名字
	*  任务内容：NPC发布与系统发布均提供需要的物品，节日庆典单独提供
	*  奖励：NPC发布加金币或物品以及对应好感度，系统发布加金币，节日庆典发布加与所有人的好感度以及特殊收集物品奖励
	*/
	enum TaskType {
		NPC_TASK,
		SYSTEM_TASK,
		FESTIVAL_TASK
	};

	struct Task {
		std::string name;               // 任务名称  
		TaskType type;                  // 任务类型  
		std::string npcName;            // 发布任务的 NPC 名字（NPC_TASK 使用）  
		std::vector<Item> requiredItems; // 需要的物品（可选）  
		int rewardCoins;                // 奖励金币（SYSTEM_TASK 和 NPC_TASK 使用）  
		std::vector<Item> specialRewards; // 节日庆典特殊收集物品（FESTIVAL_TASK 使用）  
		float relationshipPoints;       // 对应的好感度（NPC_TASK 和 FESTIVAL_TASK 使用）  
		std::string description;        // 任务详细说明  
		std::string startSeason;          // 任务初始日期  
		std::string endSeason;            // 任务截至日期  

		Task ( const std::string& name , TaskType type , const std::string& desc , const std::string& start , const std::string& end )
			: name ( name ) , type ( type ) , rewardCoins ( 0 ) , relationshipPoints ( 0.0f ) , description ( desc ) , startSeason ( start ) , endSeason ( end ) {
		}
	};

	TaskManagement ();

	// 创建任务  
	void createTask ( const Task& task );

	// 获取已经创建的任务
	std::vector<Task> returnTasks () { return tasks; }

	// 获取已经接受的任务
	std::vector<Task> returnAcceptTasks () { return acceptTasks; }

	// 添加已接受的任务
	void AddAcceptTask ( const Task& task );

	// 完成任务并处理奖励  
	void completeTask ( const std::string& task_name );

	//任务接受后从发布任务中删除
	void DeleteAcceptTask ( const Task& task );

	// 返回物品对应的任务
	std::string findTaskByRequiredItems ( const std::string& itemName );

protected:

	std::vector<Task> tasks;              // 存储任务的容器

	std::vector<Task> acceptTasks;        // 储存已接受任务的容器

};