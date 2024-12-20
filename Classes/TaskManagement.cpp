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
void TaskManagement::completeTask ( const std::string& task_name ) {
    // 查找已接受的任务
    auto it = std::find_if ( acceptTasks.begin () , acceptTasks.end () ,
                            [&task_name]( const Task& task ) {
                                return task.name == task_name;
                            } );

    // 如果找到了任务
    if (it != acceptTasks.end ()) {
        const Task& task = *it;

        // 根据任务类型增加金币和/或物品
        if (task.type == NPC_TASK || task.type == SYSTEM_TASK) {
            GoldAmount += 400; // 假设GoldAmount是类的成员变量
            for (const auto& requiredItem : task.requiredItems) {
                inventory->RemoveItem ( requiredItem , 1 ); // 移除物品
            }
        }

        // 如果是NPC任务，增加对应NPC的好感度
        if (task.type == NPC_TASK) {
            npc_relationship->increaseRelationship ( "player" , task.npcName , task.relationshipPoints );
        }
        // 如果是节日任务，增加所有NPC的好感度，并处理特殊奖励
        else if (task.type == FESTIVAL_TASK) {
            for (const Item& item : task.specialRewards) {
                inventory->AddItem ( item ); // 假设inventory是类的成员变量，需要添加物品
            }
            npc_relationship->increaseRelationship ( "player" , "Alex" , task.relationshipPoints );
            npc_relationship->increaseRelationship ( "player" , "Abigail" , task.relationshipPoints );
            npc_relationship->increaseRelationship ( "player" , "Caroline" , task.relationshipPoints );
            npc_relationship->increaseRelationship ( "player" , "Elliott" , task.relationshipPoints );
            npc_relationship->increaseRelationship ( "player" , "Emily" , task.relationshipPoints );
        }

        // 从已接受的任务列表中移除任务
        acceptTasks.erase ( it );
    }
    else {
        // 如果没有找到任务，抛出异常
        // throw std::runtime_error ( "Task not found in accepted tasks." );
    }
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

// 返回物品对应的任务
std::string TaskManagement::findTaskByRequiredItems ( const std::string& itemName ) {
    // 遍历acceptTasks寻找包含指定物品的任务
    for (const auto& task : acceptTasks) {
        for (const auto& item : task.requiredItems) {
            if (item.GetName() == itemName) {
                return task.name; // 找到匹配的任务，返回任务名称
            }
        }
    }

    // 如果没有找到，抛出异常
    // throw std::runtime_error ( "No task found with the required item." );
    return "";
}