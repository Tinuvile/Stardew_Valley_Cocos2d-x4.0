#include "TaskManagement.h"

TaskManagement::TaskManagement () {}

// 创建任务
void TaskManagement::createTask ( const Task& task ) {
	tasks.push_back ( task );
}

// 添加已经接受的任务
void TaskManagement::AddAcceptTask ( const Task& task ) {
    acceptTasks.push_back ( task );
}

// 完成任务并获得奖励
void TaskManagement::completeTask ( const Task& task ) {
	auto it = std::find_if ( tasks.begin () , tasks.end () , [&task]( const Task& t ) {
		return t.name == task.name;
	} );

	if (it != tasks.end ()) {
		if (it->type == NPC_TASK || it->type == SYSTEM_TASK) {
			GoldAmount += 400;
			// inventory->RemoveItem ();
		}
	}
    if (it->type == NPC_TASK) {
        npc_relationship->increaseRelationship ( "player" , it->npcName , it->relationshipPoints );
    }
    else if (it->type == FESTIVAL_TASK) {
        // 处理节日任务特殊奖励  
        for (const Item& item : it->specialRewards) {
            inventory->AddItem ( item );
        }
        npc_relationship->increaseRelationship ( "player" , "Alex" , it->relationshipPoints);
        npc_relationship->increaseRelationship ( "player" , "Abigail" , it->relationshipPoints );
        npc_relationship->increaseRelationship ( "player" , "Caroline" , it->relationshipPoints );
        npc_relationship->increaseRelationship ( "player" , "Elliott" , it->relationshipPoints );
        npc_relationship->increaseRelationship ( "player" , "Emily" , it->relationshipPoints );
    }

    // 从任务列表中移除任务  
    tasks.erase ( it );
    acceptTasks.erase ( it );
}


//任务接受后从发布任务中删除
void TaskManagement::DeleteAcceptTask ( const Task& task ) {
    // 从 Tasks 中删除任务
    tasks.erase ( std::remove_if ( tasks.begin () , tasks.end () ,
        [&task]( const Task& t ) {
            return t.name == task.name && t.npcName == task.npcName && t.type == task.type;  // 根据多个条件进行匹配
        } ) ,
        tasks.end () );
}

//返回目前发布任务数量
int TaskManagement::returnTaskNUMs () {
    int num = 0;
    for (const auto& task : tasks)
        num++;
    return num;
}

//返回目前接受任务数量
int TaskManagement::returnAcceptTaskNUMs () {
    int num = 0;
    for (const auto& task : acceptTasks)
        num++;
    return num;
}