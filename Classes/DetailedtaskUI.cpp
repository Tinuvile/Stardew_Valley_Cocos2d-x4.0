// DetailedtaskUI.cpp - 详细任务界面实现
#include "DetailedtaskUI.h"
#include "mailBoxUI.h"
#include "ui/CocosGUI.h"
#include "UI/Core/UITheme.h"
#include "UI/Core/UIConfig.h"
#include "UI/Builders/SpriteBuilder.h"
#include "UI/Builders/LabelBuilder.h"
#include "UI/Builders/ButtonBuilder.h"
#include "UI/Components/DarkOverlay.h"

extern Player* player1;
extern TaskManagement* taskManager;

USING_NS_CC;

static void problemLoading(const char* filename) {
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames\n");
}

DetailedtaskUI* DetailedtaskUI::create(TaskManagement::Task task) {
    DetailedtaskUI* ret = new DetailedtaskUI();
    if (ret && ret->init(task)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool DetailedtaskUI::init(TaskManagement::Task task) {
    if (!ClosableUI::init()) {
        return false;
    }

    // 初始化屏幕和位置信息
    auto theme = UITheme::getInstance();
    auto config = UIConfig::getInstance();
    m_visibleSize = theme->getVisibleSize();

    Vec2 playerPos = player1->getPosition();
    // 设置场景名称，可以根据任务类型调整
    m_sceneName = "farm"; // 默认场景，可以根据需要修改
    m_adjustedPosition = config->adjustCoordinate(m_sceneName, playerPos);

    setupUI(task);

    return true;
}

void DetailedtaskUI::setupUI(TaskManagement::Task task) {
    // 1. 创建半透明遮罩
    auto darkOverlay = DarkOverlay::create(m_sceneName);
    this->addChild(darkOverlay, 0);

    // 2. 创建主要UI组件
    createBackground();
    displayTask(task);
    createAcceptButton(task);
    createCloseButton();

    // 3. 设置事件监听器
    setupEventListeners();
}

void DetailedtaskUI::createBackground() {
    m_background = SpriteBuilder()
        .setTexture("UIresource/xinxiang/renwu2.png")
        .setAutoScale(1.0f)  // 使用原始大小，适配屏幕
        .setPosition(m_adjustedPosition)
        .setZOrder(1)
        .setTag(101)
        .addToParent(this)
        .build();

    if (!m_background) {
        problemLoading("'renwu2.png'");
    }
}

void DetailedtaskUI::displayTask(TaskManagement::Task task) {
    // 构建任务信息字符串
    std::string taskInfo = "------------------------\n";
    taskInfo += "Task Name: " + task.name + "\n";
    taskInfo += "Task Type: " + std::to_string(task.type) + "\n";

    // 如果是NPC任务，显示NPC名称
    if (task.type == TaskManagement::NPC_TASK) {
        taskInfo += "Release NPC: " + task.npcName + "\n";
    }

    taskInfo += "Reward coins: " + std::to_string(task.rewardCoins) + "\n";
    taskInfo += "Enhance favorability: " + std::to_string(task.relationshipPoints) + "\n";
    taskInfo += "------------------------";

    // 创建任务信息标签
    m_taskInfoLabel = LabelBuilder()
        .setText(taskInfo)
        .setFont("fonts/Comic Sans MS.ttf", 80)
        .setColor(Color3B::BLACK)
        .setPosition(m_adjustedPosition)
        .setZOrder(2)
        .setTag(102)
        .addToParent(this)
        .build();
}

void DetailedtaskUI::createAcceptButton(TaskManagement::Task task) {
    // 使用ButtonBuilder创建接受任务按钮
    m_acceptButton = ButtonBuilder()
        .setNormalTexture(UIConfig::UIResources::OK_BUTTON_NORMAL)
        .setPressedTexture(UIConfig::UIResources::OK_BUTTON_PRESSED)
        .setAutoScale(8.0f)
        .setPosition(m_adjustedPosition.x + m_visibleSize.width * 0.4f,
                    m_adjustedPosition.y - m_visibleSize.height * 0.23f)
        .setZOrder(2)
        .setTag(104)
        .setClickCallback([this, task](Ref* sender) {
            onAcceptClicked(task);
        })
        .setHoverEffect(1.2f)
        .addToParent(this)
        .build();
}

void DetailedtaskUI::createCloseButton() {
    m_closeButton = SpriteBuilder()
        .setTexture("npc/bacha.png")
        .setAutoScale(20.5f)
        .setPosition(m_adjustedPosition.x + m_visibleSize.width * 0.45f,
                    m_adjustedPosition.y + m_visibleSize.height * 0.4f)
        .setZOrder(1)
        .setTag(103)
        .addToParent(this)
        .build();

    if (!m_closeButton) {
        problemLoading("'npc/bacha.png'");
    }
}

void DetailedtaskUI::setupEventListeners() {
    // 鼠标事件监听器
    auto mouseListener = EventListenerMouse::create();

    mouseListener->onMouseMove = CC_CALLBACK_1(DetailedtaskUI::onMouseMove, this);
    mouseListener->onMouseDown = CC_CALLBACK_1(DetailedtaskUI::onMouseDown, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    // 使用基类的ESC关闭功能
    setupEscCloseListener();
}

void DetailedtaskUI::onMouseMove(EventMouse* event) {
    Vec2 mousePosition = Vec2(event->getCursorX(), event->getCursorY());
    mousePosition = this->convertToNodeSpace(mousePosition);

    // 检查关闭按钮悬停效果
    if (m_closeButton && m_closeButton->getBoundingBox().containsPoint(mousePosition)) {
        auto theme = UITheme::getInstance();
        float scale = theme->getVisibleSize().width / m_closeButton->getContentSize().width / 20.5f;
        m_closeButton->setScale(scale * 1.2f);  // 放大效果
    } else if (m_closeButton) {
        auto theme = UITheme::getInstance();
        float scale = theme->getVisibleSize().width / m_closeButton->getContentSize().width / 20.5f;
        m_closeButton->setScale(scale);  // 恢复原始大小
    }

    // 注意：ButtonBuilder已经处理了接受按钮的悬停效果，这里不需要额外处理
}

void DetailedtaskUI::onMouseDown(EventMouse* event) {
    Vec2 mousePosition = Vec2(event->getCursorX(), event->getCursorY());
    mousePosition = this->convertToNodeSpace(mousePosition);

    // 检查关闭按钮点击
    if (m_closeButton && m_closeButton->getBoundingBox().containsPoint(mousePosition)) {
        onCloseClicked();
        return;
    }

    // 注意：ButtonBuilder已经处理了接受按钮的点击事件，这里不需要额外处理
}

void DetailedtaskUI::onCloseClicked() {
    this->removeFromParent();

    // 打开邮件箱界面
    auto currentScene = Director::getInstance()->getRunningScene();
    if (currentScene) {
        auto mailBox = mailBoxUI::create();
        if (mailBox) {
            currentScene->addChild(mailBox, 20);
        }
    }
}

void DetailedtaskUI::onAcceptClicked(TaskManagement::Task task) {
    // 添加任务到接受列表
    if (taskManager) {
        taskManager->AddAcceptTask(task);
        taskManager->DeleteAcceptTask(task);
    }

    this->removeFromParent();

    // 打开邮件箱界面
    auto currentScene = Director::getInstance()->getRunningScene();
    if (currentScene) {
        auto mailBox = mailBoxUI::create();
        if (mailBox) {
            currentScene->addChild(mailBox, 20);
        }
    }
}