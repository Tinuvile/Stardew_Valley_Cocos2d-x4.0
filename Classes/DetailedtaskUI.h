// DetailedtaskUI.h - 详细任务界面（使用建造者模式重构）
#pragma once
#include "cocos2d.h"
#include "AppDelegate.h"
#include "TaskManagement.h"
#include "UI/ClosableUI.h"

class DetailedtaskUI : public ClosableUI {
public:

    virtual bool init(TaskManagement::Task task);
    static DetailedtaskUI* create(TaskManagement::Task task);

private:
    void setupUI(TaskManagement::Task task);
    void createBackground();
    void displayTask(TaskManagement::Task task);
    void createCloseButton();
    void createAcceptButton(TaskManagement::Task task);
    void setupEventListeners();

    // 事件处理
    void onMouseMove(cocos2d::EventMouse* event);
    void onMouseDown(cocos2d::EventMouse* event);
    void onCloseClicked();
    void onAcceptClicked(TaskManagement::Task task);

private:
    std::string m_sceneName;

    // UI组件
    cocos2d::Sprite* m_background;
    cocos2d::Label* m_taskInfoLabel;
    cocos2d::Sprite* m_closeButton;
    cocos2d::ui::Button* m_acceptButton;

    // 位置和尺寸信息
    cocos2d::Vec2 m_adjustedPosition;
    cocos2d::Size m_visibleSize;
};