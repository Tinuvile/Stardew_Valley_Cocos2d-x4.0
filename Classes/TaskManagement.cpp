#include "TaskManagement.h"

TaskManagement::TaskManagement () {}

// ��������
void TaskManagement::createTask ( const Task& task ) {
	tasks.push_back ( task );
}

// �����Ѿ����ܵ�����
void TaskManagement::AddAcceptTask ( const Task& task ) {
    acceptTasks.push_back ( task );
}

// ������񲢻�ý���
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
        // ���������������⽱��  
        for (const Item& item : it->specialRewards) {
            inventory->AddItem ( item );
        }
        npc_relationship->increaseRelationship ( "player" , "Alex" , it->relationshipPoints);
        npc_relationship->increaseRelationship ( "player" , "Abigail" , it->relationshipPoints );
        npc_relationship->increaseRelationship ( "player" , "Caroline" , it->relationshipPoints );
        npc_relationship->increaseRelationship ( "player" , "Elliott" , it->relationshipPoints );
        npc_relationship->increaseRelationship ( "player" , "Emily" , it->relationshipPoints );
    }

    // �������б����Ƴ�����  
    tasks.erase ( it );
    acceptTasks.erase ( it );
}