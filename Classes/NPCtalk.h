#ifndef NPCTALK_H  
#define NPCTALK_H  

#include "cocos2d.h"  
#include "Inventory.h"  
#include "NPCreate.h"  
#include "NPCdata.h"  
#include "DialogPresets.h"  

class NPCtalk : public cocos2d::Layer {
public:
    // 类的构造和初始化函数  
    virtual bool init ( Inventory* inventory , NPC* npc_name );

    // 创建函数，返回 NPCtalk 对象的实例  
    static NPCtalk* create ( Inventory* inventory , NPC* npc_name );

    // 背景创建函数  
    void backgroundcreate ();

private:
    Inventory* _inventory;  // 指向 Inventory 实例的指针  
    NPC* _npc;              // 指向 NPC 实例的指针  
    cocos2d::Label* _dialogLabel;  // 显示对话信息的标签  
    cocos2d::Vector<cocos2d::Sprite*> _DialogPresets; // 存储对话信息  
    int _selectedReturn;    // 当前选中的回答  
};

#endif // NPCTALK_H