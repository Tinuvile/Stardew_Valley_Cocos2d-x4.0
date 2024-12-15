//intimacyUI.h
//人物亲密度界面
#pragma once
#include "cocos2d.h"  
#include "NpcRelationship.h"  
#include "AppDelegate.h"
#include "InventoryUI.h"
#include <NPC.h>
#include "SkillTreeUI.h"

class intimacyUI : public cocos2d::Layer {
public:
    virtual bool init ();

    static intimacyUI* create ();

    void backgroundcreate ();

    void Buttons_switching ();

    void close ();

    void updateCoordinate ( float& x , float& y );

    void characterInfo ( const string& name , const string& status , Vec2 Pos_photo);
private:  

};
                            