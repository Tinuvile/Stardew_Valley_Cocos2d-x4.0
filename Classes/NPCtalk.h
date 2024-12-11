#ifndef NPCTALK_H  
#define NPCTALK_H  

#include "cocos2d.h"  
#include "Inventory.h"  
#include "NPCreate.h"  
#include "NPCdata.h"  
#include "DialogPresets.h"  

class NPCtalk : public cocos2d::Layer {
public:
    // ��Ĺ���ͳ�ʼ������  
    virtual bool init ( Inventory* inventory , NPC* npc_name );

    // �������������� NPCtalk �����ʵ��  
    static NPCtalk* create ( Inventory* inventory , NPC* npc_name );

    // ������������  
    void backgroundcreate ();

private:
    Inventory* _inventory;  // ָ�� Inventory ʵ����ָ��  
    NPC* _npc;              // ָ�� NPC ʵ����ָ��  
    cocos2d::Label* _dialogLabel;  // ��ʾ�Ի���Ϣ�ı�ǩ  
    cocos2d::Vector<cocos2d::Sprite*> _DialogPresets; // �洢�Ի���Ϣ  
    int _selectedReturn;    // ��ǰѡ�еĻش�  
};

#endif // NPCTALK_H