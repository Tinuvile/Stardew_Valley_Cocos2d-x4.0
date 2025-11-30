// NPCtalkUI.h - NPC对话界面（使用建造者模式重构）
#pragma once
#include "cocos2d.h"
#include "AppDelegate.h"
#include "NPC.h"
#include "NpcRelationship.h"
#include "UI/ClosableUI.h"

class NPCtalkUI : public ClosableUI {
public:
    virtual bool init(NPC* npc_name, std::string sceneName);
    static NPCtalkUI* create(NPC* npc_name, std::string sceneName);

private:
    void setupUI();
    void createDialogBox();
    void createCharacterPhoto();
    void createCharacterName();
    void createSelectionBoxes();
    void createCloseButton();
    void setupEventListeners();

    // 事件处理
    void onMouseMove(cocos2d::EventMouse* event);
    void onMouseDown(cocos2d::EventMouse* event);
    void onCloseClicked();
    void onSelectionClicked(int selectionIndex);

private:
    NPC* m_npc;
    std::string m_sceneName;
    NpcRelationship* m_npcRelationship;

    // UI组件
    cocos2d::Sprite* m_dialogBox;
    cocos2d::Sprite* m_characterPhoto;
    cocos2d::Sprite* m_closeButton;
    std::vector<cocos2d::Sprite*> m_selectionBoxes;
    std::vector<cocos2d::Label*> m_dialogLabels;

    // 当前对话数据
    std::vector<std::string> m_currentDialog;
    cocos2d::Vec2 m_adjustedPosition;
    cocos2d::Size m_visibleSize;
};