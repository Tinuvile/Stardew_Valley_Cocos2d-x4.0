#pragma once
// SkillTreeUI.h - 技能树界面（使用建造者模式重构）
#include "cocos2d.h"
#include "AppDelegate.h"
#include "SkillTree.h"
#include "UI/ClosableUI.h"

class SkillTreeUI : public ClosableUI {
public:
    virtual bool init(std::string sceneName);
    static SkillTreeUI* create(std::string sceneName);

private:
    void setupUI();
    void setupSkillDisplay();
    void displaySkillRow(int whichSkill, const cocos2d::Vec2& position, float gap);

    std::string m_sceneName;
    NpcRelationship* m_npcRelationship;
};
