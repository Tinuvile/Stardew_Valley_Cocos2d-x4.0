#include "TaskManagement.h"

TaskManagement::TaskManagement () {}

// ��������
void TaskManagement::createTask ( const Task& task ) {
	tasks.push_back ( task );
}

// ����Ѿ����ܵ�����
void TaskManagement::AddAcceptTask ( const Task& task ) {
    acceptTasks.push_back ( task );
}

// ������񲢻�ý���
void TaskManagement::completeTask ( const std::string& task_name ) {
    // �����ѽ��ܵ�����
    auto it = std::find_if ( acceptTasks.begin () , acceptTasks.end () ,
                            [&task_name]( const Task& task ) {
                                return task.name == task_name;
                            } );

    // ����ҵ�������
    if (it != acceptTasks.end ()) {
        const Task& task = *it;

        // ���������������ӽ�Һ�/����Ʒ
        if (task.type == NPC_TASK || task.type == SYSTEM_TASK) {
            GoldAmount += 400; // ����GoldAmount����ĳ�Ա����
            // inventory->RemoveItem(); // ����inventory����ĳ�Ա��������Ҫ�Ƴ���Ʒ
        }

        // �����NPC�������Ӷ�ӦNPC�ĺøж�
        if (task.type == NPC_TASK) {
            npc_relationship->increaseRelationship ( "player" , task.npcName , task.relationshipPoints );
        }
        // ����ǽ���������������NPC�ĺøжȣ����������⽱��
        else if (task.type == FESTIVAL_TASK) {
            for (const Item& item : task.specialRewards) {
                inventory->AddItem ( item ); // ����inventory����ĳ�Ա��������Ҫ�����Ʒ
            }
            npc_relationship->increaseRelationship ( "player" , "Alex" , task.relationshipPoints );
            npc_relationship->increaseRelationship ( "player" , "Abigail" , task.relationshipPoints );
            npc_relationship->increaseRelationship ( "player" , "Caroline" , task.relationshipPoints );
            npc_relationship->increaseRelationship ( "player" , "Elliott" , task.relationshipPoints );
            npc_relationship->increaseRelationship ( "player" , "Emily" , task.relationshipPoints );
        }

        // ���ѽ��ܵ������б����Ƴ�����
        acceptTasks.erase ( it );
    }
    else {
        // ���û���ҵ������׳��쳣
        // throw std::runtime_error ( "Task not found in accepted tasks." );
    }
}


//������ܺ�ӷ���������ɾ��
void TaskManagement::DeleteAcceptTask ( const Task& task ) {
    // �� Tasks ��ɾ������
    tasks.erase ( std::remove_if ( tasks.begin () , tasks.end () ,
        [&task]( const Task& t ) {
            return t.name == task.name && t.npcName == task.npcName && t.type == task.type;  // ���ݶ����������ƥ��
        } ) ,
        tasks.end () );
}

// ������Ʒ��Ӧ������
std::string TaskManagement::findTaskByRequiredItems ( const Item& item ) {
    // ����acceptTasksѰ�Ұ���ָ����Ʒ������
    for (const auto& task : acceptTasks) {
        // ʹ��std::find�����requiredItems���Ƿ����item
        if (std::find ( task.requiredItems.begin () , task.requiredItems.end () , item ) != task.requiredItems.end ()) {
            // ����ҵ��ˣ����ظ�����
            return task.name;
        }
    }

    // ���û���ҵ����׳��쳣
    // throw std::runtime_error ( "No task found with the required item." );
    return "";
}