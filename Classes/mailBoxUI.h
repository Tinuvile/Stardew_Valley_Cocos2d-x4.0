// mailBoxUI.h - 邮箱界面（使用建造者模式重构）
#pragma once
#include "cocos2d.h"
#include "TaskManagement.h"
#include "AppDelegate.h"

class mailBoxUI : public cocos2d::Layer {
public:
    virtual bool init();
    static mailBoxUI* create();

private:
    // UI设置方法 - 使用建造者模式重构
    void backgroundcreate();
    void close();
    void taskDisplay(TaskManagement& taskManager);

};
