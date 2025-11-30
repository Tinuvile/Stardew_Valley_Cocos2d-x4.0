#pragma once
// quitUI.h - 退出界面（使用建造者模式重构）
#include "cocos2d.h"
#include "AppDelegate.h"
#include "UI/ClosableUI.h"

class quitUI : public ClosableUI {
public:
    virtual bool init(std::string sceneName);
    static quitUI* create(std::string sceneName);

private:
    void setupUI();
    void setupQuitButton();

    std::string m_sceneName;
};
