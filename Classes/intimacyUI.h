//intimacyUI.h
//人物亲密度界面
#pragma once
#include "cocos2d.h"  
#include "NpcRelationship.h"  
#include "AppDelegate.h"
#include "InventoryUI.h"

class intimacyUI : public cocos2d::Layer {
public:
    virtual bool init ();
    static intimacyUI* create ();
    void backgroundcreate ();
    void Buttons_switching ();

private:  

    void onItemSlotClicked ( cocos2d::Ref* sender ); // 物品槽的点击事件处理  
};
                            