#pragma once
// intimacyUI.h - 亲密度界面（使用建造者模式重构）
#include "cocos2d.h"
#include "NpcRelationship.h"
#include "AppDelegate.h"
#include "NPC.h"
#include "UI/ClosableUI.h"

class intimacyUI : public ClosableUI {
public:
    virtual bool init(std::string sceneName);
    static intimacyUI* create(std::string sceneName);

private:
    void setupUI();
    void setupCharacterDisplay();
    void displayCharacter(const std::string& name, const std::string& status,
                         const cocos2d::Vec2& photoPos, const cocos2d::Vec2& intimacyPos);
    void displayIntimacyHearts(const std::string& name, const cocos2d::Vec2& position);
    void setupHoverListener(cocos2d::Sprite* oneframe, int characterIndex);

    std::string m_sceneName;
    NpcRelationship* m_npcRelationship;
};
