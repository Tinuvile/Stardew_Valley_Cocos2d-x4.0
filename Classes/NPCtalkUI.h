//NPCtalkUI.h
#pragma once
#include "cocos2d.h"  
#include "AppDelegate.h"
#include "NPC.h"

class NPCtalkUI : public cocos2d::Layer {
public:
    virtual bool init ( NPC* npc_name );

    static NPCtalkUI* create ( NPC* npc_name );

    void backgroundcreate ();

    void close ();
private:


};
