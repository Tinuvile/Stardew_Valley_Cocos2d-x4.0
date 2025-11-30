// SkilltreeUI.cpp - 技能树界面实现（使用建造者模式重构）
#include "SkillTreeUI.h"
#include "ui/CocosGUI.h"
#include "UI/Core/UITheme.h"
#include "UI/Core/UIConfig.h"
#include "UI/Builders/SpriteBuilder.h"
#include "UI/Components/DarkOverlay.h"
#include "UI/Components/TabSwitcher.h"
#include "quitUI.h"

const int characternum = 5;

USING_NS_CC;

SkillTreeUI* SkillTreeUI::create(std::string sceneName) {
    SkillTreeUI* ret = new SkillTreeUI();
    if (ret && ret->init(sceneName)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool SkillTreeUI::init(std::string sceneName) {
    if (!ClosableUI::init()) {
        return false;
    }

    m_sceneName = sceneName;

    setupUI();
    setupSkillDisplay();
    setupEscCloseListener();  // 使用基类的ESC关闭功能

    return true;
}

void SkillTreeUI::setupUI() {
    auto theme = UITheme::getInstance();
    auto config = UIConfig::getInstance();

    // 获取玩家位置并调整坐标
    Vec2 playerPos = player1->getPosition();
    Vec2 adjustedPos = config->adjustCoordinate(m_sceneName, playerPos);

    // 1. 创建半透明遮罩 - 使用可复用组件
    auto darkOverlay = DarkOverlay::create(m_sceneName);
    this->addChild(darkOverlay, 0);

    // 2. 创建背景面板 - 使用SpriteBuilder
    auto background = SpriteBuilder()
        .setTexture(UIConfig::UIResources::SKILL_BACKGROUND1)
        .setAutoScale(1.5f)  // 替代原来的 scale/1.5
        .setPosition(adjustedPos)
        .setZOrder(1)
        .setTag(101)
        .addToParent(this)
        .build();

    // 3. 创建标签切换器 - 使用可复用组件
    auto tabSwitcher = TabSwitcher::create(m_sceneName, TabSwitcher::TabType::SKILL_TREE);
    this->addChild(tabSwitcher, 2);
}

void SkillTreeUI::setupSkillDisplay() {
    auto theme = UITheme::getInstance();
    auto config = UIConfig::getInstance();
    Size visibleSize = theme->getVisibleSize();

    // 获取调整后的位置
    Vec2 playerPos = player1->getPosition();
    Vec2 adjustedPos = config->adjustCoordinate(m_sceneName, playerPos);

    // 显示5行技能（farming, mining, foraging, fishing, combat）
    displaySkillRow(0, Vec2(adjustedPos.x - visibleSize.width * 0.18f,
                            adjustedPos.y + visibleSize.height * 0.18f), 60);
    displaySkillRow(1, Vec2(adjustedPos.x - visibleSize.width * 0.18f,
                            adjustedPos.y + visibleSize.height * 0.09f), 60);
    displaySkillRow(2, Vec2(adjustedPos.x - visibleSize.width * 0.18f,
                            adjustedPos.y + visibleSize.height * 0.00f), 60);
    displaySkillRow(3, Vec2(adjustedPos.x - visibleSize.width * 0.18f,
                            adjustedPos.y - visibleSize.height * 0.09f), 60);
    displaySkillRow(4, Vec2(adjustedPos.x - visibleSize.width * 0.18f,
                            adjustedPos.y - visibleSize.height * 0.18f), 60);
}

void SkillTreeUI::displaySkillRow(int whichSkill, const Vec2& position, float gap) {
    int fullSkillNum = (*skill_tree)(whichSkill);
    int emptySkillNum = 10 - fullSkillNum;

    float currentGap = gap;

    // 显示10个技能图标
    for (int i = 0; i < 10; i++) {
        // 在第5和第10个位置增加额外间距
        if (i == 4 || i == 9 || i == 5) {
            currentGap += 85.0f;
        } else {
            currentGap += 60.0f;
        }

        // 确定使用哪种纹理
        bool isSpecialIcon = (i == 4 || i == 9);

        if (fullSkillNum > 0) {
            // 显示满技能图标
            const char* texture = isSpecialIcon ?
                UIConfig::UIResources::FULL_SKILL2 :
                UIConfig::UIResources::FULL_SKILL1;

            SpriteBuilder()
                .setTexture(texture)
                .setScale(1.5f)
                .setPosition(position.x + currentGap, position.y)
                .setZOrder(3)
                .addToParent(this)
                .build();

            fullSkillNum--;
        } else if (emptySkillNum > 0) {
            // 显示空技能图标
            const char* texture = isSpecialIcon ?
                UIConfig::UIResources::EMPTY_SKILL2 :
                UIConfig::UIResources::EMPTY_SKILL1;

            SpriteBuilder()
                .setTexture(texture)
                .setScale(1.5f)
                .setPosition(position.x + currentGap, position.y)
                .setZOrder(3)
                .addToParent(this)
                .build();

            emptySkillNum--;
        }
    }
}

