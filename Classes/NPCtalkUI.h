//NPCtalkUI.h
#pragma once
#include "cocos2d.h"  
#include "AppDelegate.h"
#include "NPC.h"
#include "NpcRelationship.h"

class NPCtalkUI : public cocos2d::Layer {
public:
    virtual bool init ( NPC* npc_name ,std::string sceneName);

    static NPCtalkUI* create ( NPC* npc_name , std::string sceneName );

    void backgroundcreate ();

    void close ();

    void SelectedBox ();

    void updateCoordinate ( float& x , float& y );
private:

    NPC* npc;
    std::string SceneName;
    NpcRelationship* NPC_RELATIONSHIP;
};
