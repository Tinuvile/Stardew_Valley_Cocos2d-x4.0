// intimacyUI.cpp - 亲密度界面实现（使用建造者模式重构）
#include "intimacyUI.h"
#include "ui/CocosGUI.h"
#include "UI/Core/UITheme.h"
#include "UI/Core/UIConfig.h"
#include "UI/Builders/SpriteBuilder.h"
#include "UI/Builders/LabelBuilder.h"
#include "UI/Components/DarkOverlay.h"
#include "UI/Components/TabSwitcher.h"
#include "quitUI.h"
#include "Marry.h"

const int characternum = 5;

USING_NS_CC;

intimacyUI* intimacyUI::create(std::string sceneName) {
    intimacyUI* ret = new intimacyUI();
    if (ret && ret->init(sceneName)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool intimacyUI::init(std::string sceneName) {
    if (!ClosableUI::init()) {
        return false;
    }

    m_sceneName = sceneName;
    m_npcRelationship = npc_relationship;  // 使用全局变量

    setupUI();
    setupCharacterDisplay();
    setupEscCloseListener();  // 使用基类的ESC关闭功能

    return true;
}

void intimacyUI::setupUI() {
    auto theme = UITheme::getInstance();
    auto config = UIConfig::getInstance();

    // 获取玩家位置并调整坐标
    Vec2 playerPos = player1->getPosition();
    Vec2 adjustedPos = config->adjustCoordinate(m_sceneName, playerPos);
    adjustedPos.y += 13;
    // 1. 创建半透明遮罩
    auto darkOverlay = DarkOverlay::create(m_sceneName);
    this->addChild(darkOverlay, 0);

    // 2. 创建背景面板
    auto background = SpriteBuilder()
        .setTexture("UIresource/qinmidu/intimacyDisplay.png")
        .setAutoScale(1.5f)
        .setPosition(adjustedPos)
        .setZOrder(1)
        .setTag(101)
        .addToParent(this)
        .build();

    // 3. 创建标签切换器
    auto tabSwitcher = TabSwitcher::create(m_sceneName, TabSwitcher::TabType::INTIMACY);
    this->addChild(tabSwitcher, 2);

  }

void intimacyUI::setupCharacterDisplay() {
    auto theme = UITheme::getInstance();
    auto config = UIConfig::getInstance();
    Size visibleSize = theme->getVisibleSize();

    // 获取调整后的位置
    Vec2 playerPos = player1->getPosition();
    Vec2 adjustedPos = config->adjustCoordinate(m_sceneName, playerPos);

    // 定义5个角色的信息
    struct CharacterInfo {
        std::string name;
        std::string status;
        float yOffset;
    };

    CharacterInfo characters[characternum] = {
        {"Abigail", "Normal", 0.2215f},
        {"Alex", "Normal", 0.1165f},
        {"Elliott", "Normal", 0.0115f},
        {"Penny", "Normal", -0.0935f},
        {"Sam", "Normal", -0.1985f}
    };

    // 显示每个角色
    for (int i = 0; i < characternum; i++) {
        Vec2 photoPos = Vec2(
            adjustedPos.x - visibleSize.width * 0.27f,
            adjustedPos.y + visibleSize.height * characters[i].yOffset
        );

        Vec2 intimacyPos = Vec2(
            adjustedPos.x - visibleSize.width * 0.09f,
            adjustedPos.y + visibleSize.height * characters[i].yOffset
        );

        // 创建悬停框
        Vec2 framePos = Vec2(
            adjustedPos.x,
            adjustedPos.y + 280 - i * (120 * 1.0f + 12)
        );

        // 创建悬停框
        auto oneframe = SpriteBuilder()
            .setTexture("UIresource/qinmidu/weixuanzhong.png")
            .setAutoScale(1.56f)
            .setPosition(framePos)
            .setZOrder(2)
            .setTag(i + 1)
            .addToParent(this)
            .build();

        // 添加鼠标悬停事件监听器
        setupHoverListener(oneframe, i);

        // 显示角色信息
        displayCharacter(characters[i].name, characters[i].status, photoPos, intimacyPos);
    }
}

void intimacyUI::displayCharacter(const std::string& name, const std::string& status,
                                  const Vec2& photoPos, const Vec2& intimacyPos) {
    auto theme = UITheme::getInstance();

    // 1. 显示角色头像
    std::string photoPath = "UIresource/qinmidu/" + name + ".png";
    SpriteBuilder()
        .setTexture(photoPath)
        .setScale(1.2f)
        .setPosition(photoPos)
        .setZOrder(2)
        .addToParent(this)
        .build();

    // 2. 显示角色名称
    auto nameLabel = Label::createWithSystemFont(name, "fonts/Comic Sans MS.ttf", 35);
    if (nameLabel) {
        nameLabel->setTextColor(Color4B::BLACK);
        nameLabel->setPosition(Vec2(photoPos.x + 100, photoPos.y));
        this->addChild(nameLabel, 2);
    }

    // 3. 显示亲密度爱心
    displayIntimacyHearts(name, intimacyPos);
}

void intimacyUI::displayIntimacyHearts(const std::string& name, const Vec2& position) {
    auto theme = UITheme::getInstance();
    Size visibleSize = theme->getVisibleSize();

    // 获取当前角色的亲密度等级
    int fullHearts = m_npcRelationship->getRelationship("player", name) / 10;
    int emptyHearts = 10 - fullHearts;

    // 计算爱心显示的起始位置 - 确保所有角色都使用相同的基准线
    float startX = position.x;
    float baseY = position.y;  // 使用传入的基准Y坐标，不再受角色yOffset影响

    // 显示10颗爱心
    for (int i = 0; i < 10; i++) {
        float heartX = startX + (i * 32.0f * 1600.0f / 884.0f / 1.5f);  // 使用备份文件中的精确间距

        if (fullHearts > 0) {
            // 显示满心
            SpriteBuilder()
                .setTexture("UIresource/qinmidu/fullheart.png")
                .setScale(1.2f)
                .setPosition(heartX, baseY)
                .setZOrder(3)
                .addToParent(this)
                .build();
            fullHearts--;
        }
        else if (emptyHearts > 0) {
            // 显示空心
            SpriteBuilder()
                .setTexture("UIresource/qinmidu/emptyheart.png")
                .setScale(1.2f)
                .setPosition(heartX, baseY)
                .setZOrder(3)
                .addToParent(this)
                .build();
            emptyHearts--;
        }
    }

    // 显示是否交谈标记
    if (m_npcRelationship->getRelationship("player", name) != 0) {
        SpriteBuilder()
            .setTexture("UIresource/qinmidu/is.png")
            .setAutoScale(0.026f)
            .setPosition(Vec2(position.x + visibleSize.width * 0.374f, position.y - 27))
            .setZOrder(3)
            .addToParent(this)
            .build();
    }

    // 显示礼物标记
    int GiftTime = 0;
    if (m_npcRelationship->NpcGiftTIme(name) > 0) {
        if (m_npcRelationship->NpcGiftTIme(name) >= 2) {
            GiftTime = 2;
        }
        else {
            GiftTime = 1;
        }
        for (int i = 0; i < GiftTime; i++) {
            SpriteBuilder()
                .setTexture("UIresource/qinmidu/is.png")
                .setAutoScale(0.026f)
                .setPosition(Vec2(position.x + visibleSize.width * 0.271f + i * 50.0f, position.y - 27))
                .setZOrder(3)
                .addToParent(this)
                .build();
        }
    }
}

void intimacyUI::setupHoverListener(cocos2d::Sprite* oneframe, int characterIndex) {
    auto listener = EventListenerMouse::create();
    listener->onMouseMove = [this, oneframe](EventMouse* event) {
        Vec2 mousePos = Vec2(event->getCursorX(), event->getCursorY());
        mousePos = this->convertToNodeSpace(mousePos);
        if (oneframe->getBoundingBox().containsPoint(mousePos))
            oneframe->setTexture("UIresource/qinmidu/xuanzhong.png");
        else
            oneframe->setTexture("UIresource/qinmidu/weixuanzhong.png");
    };

    listener->onMouseDown = [this, oneframe, characterIndex](EventMouse* event) {
        std::vector<std::string> npcsName = {"Abigail", "Alex", "Elliott", "Penny", "Sam"};
        std::string nowName = npcsName[characterIndex];

        Vec2 mousePos = Vec2(event->getCursorX(), event->getCursorY());
        mousePos = this->convertToNodeSpace(mousePos);
        if (oneframe->getBoundingBox().containsPoint(mousePos) &&
            m_npcRelationship->getRelationship("player", nowName) >= 70) {
            std::string nowScene = m_sceneName;
            this->removeFromParent();
            Scene* currentScene = Director::getInstance()->getRunningScene();
            currentScene->addChild(Marry::create(nowScene, nowName), 20);
        }
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, oneframe);
}


