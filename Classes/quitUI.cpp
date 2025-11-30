// quitUI.cpp - 退出界面实现（使用建造者模式重构）
#include "quitUI.h"
#include "ui/CocosGUI.h"
#include "UI/Core/UITheme.h"
#include "UI/Core/UIConfig.h"
#include "UI/Builders/SpriteBuilder.h"
#include "UI/Components/DarkOverlay.h"
#include "UI/Components/TabSwitcher.h"

USING_NS_CC;

quitUI* quitUI::create(std::string sceneName) {
    quitUI* ret = new quitUI();
    if (ret && ret->init(sceneName)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool quitUI::init(std::string sceneName) {
    if (!ClosableUI::init()) {
        return false;
    }

    m_sceneName = sceneName;

    // 设置UI
    setupUI();
    setupQuitButton();
    setupEscCloseListener();  // 使用基类的ESC关闭功能

    return true;
}

void quitUI::setupUI() {
    auto theme = UITheme::getInstance();
    auto config = UIConfig::getInstance();

    // 获取玩家位置并调整坐标
    Vec2 playerPos = player1->getPosition();
    Vec2 adjustedPos = config->adjustCoordinate(m_sceneName, playerPos);

    // 1. 创建半透明遮罩 - 使用可复用组件，替代原来30行代码
    auto darkOverlay = DarkOverlay::create(m_sceneName);
    this->addChild(darkOverlay, 0);

    // 2. 创建背景面板 - 使用SpriteBuilder
    auto background = SpriteBuilder()
        .setTexture(UIConfig::UIResources::SKILL_BACKGROUND)
        .setAutoScale(1.5f)  // 替代原来的 scale/1.5
        .setPosition(adjustedPos)
        .setZOrder(1)
        .addToParent(this)
        .build();

    // 3. 创建标签切换器 - 使用可复用组件，替代原来60行代码
    auto tabSwitcher = TabSwitcher::create(m_sceneName, TabSwitcher::TabType::QUIT);
    this->addChild(tabSwitcher, 2);
}

void quitUI::setupQuitButton() {
    auto theme = UITheme::getInstance();
    auto config = UIConfig::getInstance();

    // 获取调整后的位置
    Vec2 playerPos = player1->getPosition();
    Vec2 adjustedPos = config->adjustCoordinate(m_sceneName, playerPos);

    // 创建退出按钮 - 使用SpriteBuilder和悬停效果，替代原来40行代码
    auto quitButton = SpriteBuilder()
        .setTexture(UIConfig::UIResources::QUIT_IMAGE)
        .setAdaptiveScale(0.18f, 0.18f)  // 自适应缩放替代 scale/5.5
        .setPosition(adjustedPos)
        .setZOrder(1)
        .setHoverEffect(1.2f)  // 自动悬停效果
        .setClickCallback([](Sprite*) {
            // 点击退出
            Director::getInstance()->end();
        })
        .addToParent(this)
        .build();
}

