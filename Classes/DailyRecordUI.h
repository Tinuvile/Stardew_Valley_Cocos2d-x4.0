// DailyRecordUI.h - 每日记录界面（使用建造者模式重构）
#pragma once
#include "cocos2d.h"
#include "AppDelegate.h"
#include "TaskManagement.h"
#include "UI/ClosableUI.h"

class DailyRecordUI : public ClosableUI {
public:
    virtual bool init(std::string sceneName);
    static DailyRecordUI* create(std::string sceneName);

private:
    void setupUI();
    void createBackground();
    void createTaskScrollView();
    void createCloseButton();
    void setupEventListeners();

    // 任务显示相关
    void createTaskItem(const TaskManagement::Task& task, float& offsetY);
    void setupTaskItemInteraction(cocos2d::Sprite* taskFrame, const TaskManagement::Task& task);

    // 事件处理
    void onMouseMove(cocos2d::EventMouse* event);
    void onMouseDown(cocos2d::EventMouse* event);
    void onCloseClicked();
    void onTaskItemClicked(const TaskManagement::Task& task);

private:
    std::string m_sceneName;
    TaskManagement* m_taskManager;

    // UI组件
    cocos2d::Sprite* m_background;
    cocos2d::ui::ScrollView* m_scrollView;
    cocos2d::Sprite* m_closeButton;

    // 位置和尺寸信息
    cocos2d::Vec2 m_adjustedPosition;
    cocos2d::Size m_visibleSize;
    std::vector<cocos2d::Sprite*> m_taskFrames;
};