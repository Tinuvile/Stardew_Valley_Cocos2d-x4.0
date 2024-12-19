#pragma once
//SkillTreeUI.h
//人物技能树界面
#include "cocos2d.h"  
#include "AppDelegate.h"
#include "SkillTree.h"

class SkillTreeUI : public cocos2d::Layer {
public:
    virtual bool init ( std::string sceneName );

    static SkillTreeUI* create ( std::string sceneName );



private:

    NpcRelationship* NPC_RELATIONSHIP;

    void close ();

    void SkillDisplay ( int whichSkill , Vec2 Pos , float gap );

    void backgroundcreate ();

    void Buttons_switching ();

    void updateCoordinate ( float& x , float& y );

    std::string SceneName;
};
