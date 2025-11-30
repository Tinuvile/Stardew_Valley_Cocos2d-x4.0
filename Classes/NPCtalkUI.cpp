// NPCtalkUI.cpp - NPC对话界面实现（使用建造者模式重构）
#include "NPCtalkUI.h"
#include "ui/CocosGUI.h"
#include "UI/Core/UITheme.h"
#include "UI/Core/UIConfig.h"
#include "UI/Builders/SpriteBuilder.h"
#include "UI/Builders/LabelBuilder.h"
#include "UI/Components/DarkOverlay.h"

extern Player* player1;
extern NpcRelationship* npc_relationship;
extern std::string Season;

USING_NS_CC;

NPCtalkUI* NPCtalkUI::create(NPC* npc_name, std::string sceneName) {
    NPCtalkUI* ret = new NPCtalkUI();
    if (ret && ret->init(npc_name, sceneName)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool NPCtalkUI::init(NPC* npc_name, std::string sceneName) {
    if (!ClosableUI::init()) {
        return false;
    }

    m_npc = npc_name;
    m_sceneName = sceneName;
    m_npcRelationship = npc_relationship;

    // 初始化屏幕和位置信息
    auto theme = UITheme::getInstance();
    auto config = UIConfig::getInstance();
    m_visibleSize = theme->getVisibleSize();

    Vec2 playerPos = player1->getPosition();
    m_adjustedPosition = config->adjustCoordinate(m_sceneName, playerPos);

    setupUI();

    return true;
}

void NPCtalkUI::setupUI() {
    // 1. 创建半透明遮罩
    auto darkOverlay = DarkOverlay::create(m_sceneName);
    this->addChild(darkOverlay, 0);

    // 2. 创建主要UI组件
    createDialogBox();
    createCharacterPhoto();
    createCharacterName();
    createSelectionBoxes();
    createCloseButton();

    // 3. 设置事件监听器
    setupEventListeners();
}

void NPCtalkUI::createDialogBox() {
    m_dialogBox = SpriteBuilder()
        .setTexture("npc/kuang.png")
        .setAutoScale(1.1f)  // 替代原来的 scale * 0.9
        .setPosition(m_adjustedPosition.x, m_adjustedPosition.y - m_visibleSize.height * 0.27f)
        .setZOrder(1)
        .setTag(101)
        .addToParent(this)
        .build();
}

void NPCtalkUI::createCharacterPhoto() {
    // 根据季节选择合适的头像
    std::string photo;
    if (Season == "Spring" || Season == "Autumn") {
        photo = getNPCportraits(m_npc->GetName(), "Normal");
    } else {
        photo = getNPCportraits(m_npc->GetName(), Season + "Normal");
    }

    m_characterPhoto = SpriteBuilder()
        .setTexture(photo)
        .setAutoScale(4.0f)  // 替代原来的 scale * 0.25
        .setPosition(m_adjustedPosition.x + m_visibleSize.width * 0.27f,
                     m_adjustedPosition.y - m_visibleSize.height * 0.233f)
        .setZOrder(2)
        .setTag(102)
        .addToParent(this)
        .build();
}

void NPCtalkUI::createCharacterName() {
    std::string name = m_npc->GetName();

    LabelBuilder()
        .setText(name)
        .setFont("fonts/Comic Sans MS.ttf", 40)
        .setColor(Color3B::BLACK)
        .setPosition(m_adjustedPosition.x + m_visibleSize.width * 0.26f,
                     m_adjustedPosition.y - m_visibleSize.height * 0.40f)
        .setZOrder(2)
        .setTag(103)
        .addToParent(this)
        .build();
}

void NPCtalkUI::createSelectionBoxes() {
    // 清空现有数据
    m_selectionBoxes.clear();
    m_dialogLabels.clear();

    // 获取NPC对话
    std::vector<std::vector<std::string>> npc_Dialog = getDialog(
        m_npc->GetName(),
        m_npcRelationship->getRelationshipLevel("player", m_npc->GetName())
    );

    int choose = rand() % npc_Dialog.size();
    m_currentDialog = npc_Dialog[choose];

    // 创建NPC对话标签
    auto npcTalkLabel = LabelBuilder()
        .setText(m_currentDialog[0])
        .setFont("fonts/Comic Sans MS.ttf", 40)
        .setColor(Color3B::BLACK)
        .setPosition(m_adjustedPosition.x - m_visibleSize.width * 0.17f,
                     m_adjustedPosition.y - m_visibleSize.height * 0.14f)
        .setZOrder(2)
        .setTag(104)
        .addToParent(this)
        .build();
    m_dialogLabels.push_back(npcTalkLabel);

    // 创建4个选择框和对应的标签
    std::vector<Vec2> positions = {
        Vec2(m_adjustedPosition.x - m_visibleSize.width * 0.17f,
              m_adjustedPosition.y - m_visibleSize.height * 0.21f),
        Vec2(m_adjustedPosition.x - m_visibleSize.width * 0.17f,
              m_adjustedPosition.y - m_visibleSize.height * 0.274f),
        Vec2(m_adjustedPosition.x - m_visibleSize.width * 0.17f,
              m_adjustedPosition.y - m_visibleSize.height * 0.338f),
        Vec2(m_adjustedPosition.x - m_visibleSize.width * 0.17f,
              m_adjustedPosition.y - m_visibleSize.height * 0.402f)
    };

    for (int i = 1; i <= 4 && i < m_currentDialog.size(); i++) {
        // 创建选择框
        auto selectionBox = SpriteBuilder()
            .setTexture("npc/xuanzhongkuang.png")
            .setAutoScale(2.0f)  // 替代原来的 scale * 0.5
            .setPosition(positions[i-1])
            .setZOrder(0)
            .setTag(105 + i)
            .addToParent(this)
            .build();

        m_selectionBoxes.push_back(selectionBox);

        // 创建对话选项标签
        auto dialogLabel = LabelBuilder()
            .setText(m_currentDialog[i])
            .setFont("fonts/Comic Sans MS.ttf", 30)
            .setColor(Color3B::BLACK)
            .setPosition(positions[i-1])
            .setZOrder(2)
            .setTag(200 + i)
            .addToParent(this)
            .build();

        m_dialogLabels.push_back(dialogLabel);
    }
}

void NPCtalkUI::createCloseButton() {
    m_closeButton = SpriteBuilder()
        .setTexture("npc/bacha.png")
        .setAutoScale(20.5f)
        .setPosition(m_adjustedPosition.x + m_visibleSize.width * 0.40f,
                    m_adjustedPosition.y - m_visibleSize.height * 0.13f)
        .setZOrder(1)
        .setTag(109)
        .addToParent(this)
        .build();
}

void NPCtalkUI::setupEventListeners() {
    auto mouseListener = EventListenerMouse::create();

    mouseListener->onMouseMove = CC_CALLBACK_1(NPCtalkUI::onMouseMove, this);
    mouseListener->onMouseDown = CC_CALLBACK_1(NPCtalkUI::onMouseDown, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    // 使用基类的ESC关闭功能
    setupEscCloseListener();
}

void NPCtalkUI::onMouseMove(EventMouse* event) {
    Vec2 mousePosition = Vec2(event->getCursorX(), event->getCursorY());
    mousePosition = this->convertToNodeSpace(mousePosition);

    // 检查选择框悬停效果
    for (size_t i = 0; i < m_selectionBoxes.size(); i++) {
        if (m_selectionBoxes[i] && m_selectionBoxes[i]->getBoundingBox().containsPoint(mousePosition)) {
            m_selectionBoxes[i]->setLocalZOrder(2);  // 显示在上层
        } else {
            m_selectionBoxes[i]->setLocalZOrder(0);  // 隐藏在下层
        }
    }

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

void NPCtalkUI::onMouseDown(EventMouse* event) {
    Vec2 mousePosition = Vec2(event->getCursorX(), event->getCursorY());
    mousePosition = this->convertToNodeSpace(mousePosition);

    // 检查关闭按钮点击
    if (m_closeButton && m_closeButton->getBoundingBox().containsPoint(mousePosition)) {
        onCloseClicked();
        return;
    }

    // 检查选择框点击
    for (size_t i = 0; i < m_selectionBoxes.size(); i++) {
        if (m_selectionBoxes[i] && m_selectionBoxes[i]->getBoundingBox().containsPoint(mousePosition)) {
            onSelectionClicked(static_cast<int>(i));
            return;  // 提前返回，避免执行后续检查
        }
    }
}

void NPCtalkUI::onCloseClicked() {
    this->removeFromParent();
}

void NPCtalkUI::onSelectionClicked(int selectionIndex) {
    // 根据选择影响亲密度关系
    float relationshipChange = 0.0f;

    switch (selectionIndex) {
        case 0:  // 第一个选项，增加较多亲密度
            if (m_npcRelationship->getRelationship("player", m_npc->GetName()) < 60) {
                relationshipChange = 10.2f;
            }
            break;
        case 1:  // 第二个选项，增加少量亲密度
            if (m_npcRelationship->getRelationship("player", m_npc->GetName()) < 60) {
                relationshipChange = 5.0001f;
            }
            break;
        case 2:  // 第三个选项，略微减少亲密度
            relationshipChange = -0.001f;
            break;
        case 3:  // 第四个选项，减少较多亲密度
            relationshipChange = -5.01f;
            break;
    }

    if (relationshipChange > 0) {
        m_npcRelationship->increaseRelationship("player", m_npc->GetName(), relationshipChange);
    } else if (relationshipChange < 0) {
        m_npcRelationship->decreaseRelationship("player", m_npc->GetName(), -relationshipChange);
    }

    this->removeFromParent();
}