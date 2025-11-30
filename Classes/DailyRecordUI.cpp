// DailyRecordUI.cpp - 每日记录界面实现（使用建造者模式重构）
#include "DailyRecordUI.h"
#include "DetailedtaskUI.h"
#include "ui/CocosGUI.h"
#include "UI/Core/UITheme.h"
#include "UI/Core/UIConfig.h"
#include "UI/Builders/SpriteBuilder.h"
#include "UI/Builders/LabelBuilder.h"
#include "UI/Components/DarkOverlay.h"

extern Player* player1;
extern TaskManagement* taskManager;

USING_NS_CC;

DailyRecordUI* DailyRecordUI::create(std::string sceneName) {
    DailyRecordUI* ret = new DailyRecordUI();
    if (ret && ret->init(sceneName)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool DailyRecordUI::init(std::string sceneName) {
    if (!ClosableUI::init()) {
        return false;
    }

    m_sceneName = sceneName;
    m_taskManager = taskManager;

    // 初始化屏幕和位置信息
    auto theme = UITheme::getInstance();
    auto config = UIConfig::getInstance();
    m_visibleSize = theme->getVisibleSize();

    Vec2 playerPos = player1->getPosition();
    m_adjustedPosition = config->adjustCoordinate(m_sceneName, playerPos);

    setupUI();

    return true;
}

void DailyRecordUI::setupUI() {
    // 1. 创建半透明遮罩
    auto darkOverlay = DarkOverlay::create(m_sceneName);
    this->addChild(darkOverlay, 0);

    // 2. 创建主要UI组件
    createBackground();
    createTaskScrollView();
    createCloseButton();

    // 3. 设置事件监听器
    setupEventListeners();
}

void DailyRecordUI::createBackground() {
    m_background = SpriteBuilder()
        .setTexture("UIresource/rizhi/DailyRecord.png")
        .setAutoScale(1.25f)
        .setPosition(m_adjustedPosition)
        .setZOrder(1)
        .setTag(101)
        .addToParent(this)
        .build();
}

void DailyRecordUI::createTaskScrollView() {
    // 创建滚动视图
    m_scrollView = ui::ScrollView::create();
    m_scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
    m_scrollView->setContentSize(Size(1630, 600));
    m_scrollView->setPosition(Vec2(
        m_adjustedPosition.x - m_visibleSize.width * 0.589f,
        m_adjustedPosition.y - m_visibleSize.height * 0.2f
    ));
    m_scrollView->setBounceEnabled(true);
    m_scrollView->setScrollBarEnabled(false);
    m_scrollView->setTag(102);

    // 获取已接受的任务
    std::vector<TaskManagement::Task> tasks = m_taskManager->returnAcceptTasks();

    // 清空现有任务框架
    m_taskFrames.clear();

    // 计算总高度
    const int itemCount = tasks.size();
    const float itemHeight = 500;
    float totalItemHeight = itemCount * itemHeight;

    // 设置内部容器大小
    m_scrollView->setInnerContainerSize(Size(1630, totalItemHeight));

    // 创建任务项
    float offsetY = 0;
    for (const auto& task : tasks) {
        createTaskItem(task, offsetY);
    }

    this->addChild(m_scrollView, 5);
}

void DailyRecordUI::createTaskItem(const TaskManagement::Task& task, float& offsetY) {
    // 创建任务框架
    auto taskFrame = SpriteBuilder()
        .setTexture("UIresource/SkillTree/background.png")
        .setScale(1.2f, 0.4f)
        .setPosition(Vec2(m_visibleSize.width * 0.6f, 539 + m_visibleSize.height * 1.4f - offsetY))
        .setZOrder(2)
        .setTag(200 + static_cast<int>(m_taskFrames.size()))
        .addToParent(m_scrollView)
        .build();

    m_taskFrames.push_back(taskFrame);

    // 创建任务信息标签
    std::string taskInfo = "Task_Name: " + task.name;

    auto taskMessage = LabelBuilder()
        .setText(taskInfo)
        .setFont("fonts/Comic Sans MS.ttf", 50)
        .setColor(Color3B::BLACK)
        .setAnchorPoint(Vec2(0, 0.5))
        .setPosition(Vec2(m_visibleSize.width * 0.35f, 539 + m_visibleSize.height * 1.4f - offsetY))
        .setZOrder(2)
        .addToParent(m_scrollView)
        .build();

    // 设置任务项交互
    setupTaskItemInteraction(taskFrame, task);

    // 更新偏移量
    offsetY += 350;
}

void DailyRecordUI::setupTaskItemInteraction(Sprite* taskFrame, const TaskManagement::Task& task) {
    auto listener = EventListenerMouse::create();

    listener->onMouseMove = [this, taskFrame](EventMouse* event) {
        Vec2 mousePos = Vec2(event->getCursorX(), event->getCursorY());
        mousePos = this->convertToNodeSpace(mousePos);

        Vec2 scrollViewPos = m_scrollView->getPosition();
        Vec2 innerContainerPos = m_scrollView->getInnerContainer()->getPosition();

        // 计算调整后的边界框
        Rect itemBoundingBox = taskFrame->getBoundingBox();
        float adjustedPosY = itemBoundingBox.getMinY() + innerContainerPos.y;
        float adjustedPosX = itemBoundingBox.getMinX() + innerContainerPos.x;

        // 检查鼠标是否悬停在任务项上
        if (mousePos.x >= adjustedPosX - 950 + m_adjustedPosition.x &&
            mousePos.x <= adjustedPosX + itemBoundingBox.size.width - 950 + m_adjustedPosition.x &&
            mousePos.y >= adjustedPosY + m_adjustedPosition.y - 250 &&
            mousePos.y <= m_adjustedPosition.y + adjustedPosY + itemBoundingBox.size.height - 250) {

            taskFrame->setTexture("UIresource/xinxiang/xuanzhong.png");
        } else {
            taskFrame->setTexture("UIresource/SkillTree/background.png");
        }
    };

    listener->onMouseDown = [this, task, taskFrame](EventMouse* event) {
        Vec2 mousePos = Vec2(event->getCursorX(), event->getCursorY());
        mousePos = this->convertToNodeSpace(mousePos);

        Vec2 scrollViewPos = m_scrollView->getPosition();
        Vec2 innerContainerPos = m_scrollView->getInnerContainer()->getPosition();

        Rect itemBoundingBox = taskFrame->getBoundingBox();
        float adjustedPosY = itemBoundingBox.getMinY() + innerContainerPos.y;
        float adjustedPosX = itemBoundingBox.getMinX() + innerContainerPos.x;

        // 检查是否点击了任务项
        if (mousePos.x >= adjustedPosX - 950 + m_adjustedPosition.x &&
            mousePos.x <= adjustedPosX + itemBoundingBox.size.width - 950 + m_adjustedPosition.x &&
            mousePos.y >= adjustedPosY + m_adjustedPosition.y - 250 &&
            mousePos.y <= m_adjustedPosition.y + adjustedPosY + itemBoundingBox.size.height - 250) {

            onTaskItemClicked(task);
        }
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, taskFrame);
}

void DailyRecordUI::createCloseButton() {
    m_closeButton = SpriteBuilder()
        .setTexture("npc/bacha.png")
        .setAutoScale(20.5f)
        .setPosition(m_adjustedPosition.x + m_visibleSize.width * 0.45f,
                    m_adjustedPosition.y + m_visibleSize.height * 0.4f)
        .setZOrder(1)
        .setTag(103)
        .addToParent(this)
        .build();
}

void DailyRecordUI::setupEventListeners() {
    // 鼠标事件监听器
    auto mouseListener = EventListenerMouse::create();

    mouseListener->onMouseMove = CC_CALLBACK_1(DailyRecordUI::onMouseMove, this);
    mouseListener->onMouseDown = CC_CALLBACK_1(DailyRecordUI::onMouseDown, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    // 滚动事件监听器
    auto scrollListener = EventListenerMouse::create();
    scrollListener->onMouseScroll = [this](EventMouse* event) {
        float scrollDelta = event->getScrollY();
        auto innerContainer = m_scrollView->getInnerContainer();
        float currentPosY = innerContainer->getPositionY();
        float newPosY = currentPosY + scrollDelta * 100;

        // 计算边界限制
        float lowerLimit = m_scrollView->getContentSize().height - innerContainer->getContentSize().height;
        float upperLimit = -1400;

        // 限制新位置在边界范围内
        newPosY = std::max(newPosY, lowerLimit);
        newPosY = std::min(newPosY, upperLimit);

        // 设置新位置
        innerContainer->setPositionY(newPosY);
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(scrollListener, this);

    // 使用基类的ESC关闭功能
    setupEscCloseListener();
}

void DailyRecordUI::onMouseMove(EventMouse* event) {
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
}

void DailyRecordUI::onMouseDown(EventMouse* event) {
    Vec2 mousePosition = Vec2(event->getCursorX(), event->getCursorY());
    mousePosition = this->convertToNodeSpace(mousePosition);

    // 检查关闭按钮点击
    if (m_closeButton && m_closeButton->getBoundingBox().containsPoint(mousePosition)) {
        onCloseClicked();
    }
}

void DailyRecordUI::onCloseClicked() {
    this->removeFromParent();
}

void DailyRecordUI::onTaskItemClicked(const TaskManagement::Task& task) {
    // 打开详细任务界面
    auto detailedTaskUI = DetailedtaskUI::create(task);
    if (detailedTaskUI) {
        Director::getInstance()->getRunningScene()->addChild(detailedTaskUI, 10);
    }
}