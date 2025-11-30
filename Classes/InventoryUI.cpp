// InventoryUI.cpp - 背包界面实现（使用建造者模式重构）
#include "InventoryUI.h"
#include "ui/CocosGUI.h"
#include "Item.h"
#include "UI/Core/UITheme.h"
#include "UI/Core/UIConfig.h"
#include "UI/Builders/SpriteBuilder.h"
#include "UI/Builders/LabelBuilder.h"
#include "UI/Components/DarkOverlay.h"
#include "UI/Components/TabSwitcher.h"

USING_NS_CC;

InventoryUI* InventoryUI::create(Inventory* inventory, std::string sceneName) {
    InventoryUI* ret = new InventoryUI();
    if (ret && ret->init(inventory, sceneName)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool InventoryUI::init(Inventory* inventory, std::string sceneName) {
    if (!ClosableUI::init()) {
        return false;
    }

    _inventory = inventory;
    m_sceneName = sceneName;
    _selectedSlot = 1;

    setupUI();
    setupItemSlots();
    setupEscCloseListener();  // 使用基类的ESC关闭功能
    updateDisplay(); // 更新物品显示

    return true;
}

void InventoryUI::setupUI() {
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
        .setTexture(UIConfig::UIResources::BAG_BACKGROUND)
        .setAutoScale(1.5f)
        .setPosition(adjustedPos)
        .setTag(101)
        .addToParent(this)
        .build();

    // 3. 创建角色显示
    auto characterDisplay = SpriteBuilder()
        .setTexture("character1/player_down3.png")
        .setAutoScale(7.5f)
        .setPosition(adjustedPos.x - Director::getInstance()->getVisibleSize().width * 0.2f,
                   adjustedPos.y - Director::getInstance()->getVisibleSize().height * 0.12f)
        .setZOrder(2)
        .addToParent(this)
        .build();

    // 4. 创建玩家名称显示
    auto playerNameLabel = LabelBuilder()
        .setText(protagonistName)
        .setFont("fonts/Comic Sans MS.ttf", 45)
        .setColor(Color3B::BLACK)
        .setPosition(adjustedPos.x + Director::getInstance()->getVisibleSize().width * 0.1f,
                   adjustedPos.y - Director::getInstance()->getVisibleSize().height * 0.07f)
        .setZOrder(4)
        .addToParent(this)
        .build();

    // 5. 创建农场名称显示
    auto farmNameLabel = LabelBuilder()
        .setText(FarmName)
        .setFont("fonts/Comic Sans MS.ttf", 45)
        .setColor(Color3B::BLACK)
        .setPosition(adjustedPos.x + Director::getInstance()->getVisibleSize().width * 0.1f,
                   adjustedPos.y - Director::getInstance()->getVisibleSize().height * 0.15f)
        .setZOrder(4)
        .addToParent(this)
        .build();

    // 6. 创建物品信息显示
    _itemLabel = LabelBuilder()
        .setText("No item selected.")
        .setFont("fonts/Comic Sans MS.ttf", 20)
        .setColor(Color3B::BLACK)
        .setPosition(adjustedPos.x, adjustedPos.y - Director::getInstance()->getVisibleSize().height * 0.3f)
        .setZOrder(5)
        .addToParent(this)
        .build();

    // 7. 创建标签切换器
    auto tabSwitcher = TabSwitcher::create(m_sceneName, TabSwitcher::TabType::INVENTORY);
    this->addChild(tabSwitcher, 2);
}

void InventoryUI::setupItemSlots() {
    auto theme = UITheme::getInstance();
    auto config = UIConfig::getInstance();
    auto visibleSize = Director::getInstance()->getVisibleSize();

    // 获取玩家位置并调整坐标
    Vec2 playerPos = player1->getPosition();
    Vec2 adjustedPos = config->adjustCoordinate(m_sceneName, playerPos);

    // 清空现有物品槽
    _itemSlots.clear();

    // 获取背景面板用于定位
    auto bag = getChildByTag(101);
    if (!bag) return;

    // 创建物品格子 Sprite (3行 x kRowSize列)
    for (int m = 0; m < 3; m++) {
        for (int i = 0; i < kRowSize; i++) {
            float originalWidth = 64;
            float originalHeight = 64;
            float scaleX = visibleSize.width / originalWidth;
            float scaleY = visibleSize.height / originalHeight;
            float scale = std::min(scaleX, scaleY) / 16.5f;

            float bagWidth = bag->getContentSize().width;
            float bagHeight = bag->getContentSize().height;

            Vec2 slotPos = Vec2(
                adjustedPos.x - bagWidth * 0.545f + (originalWidth * scale + 5) * i,
                adjustedPos.y + bagHeight * 1.73f / 3.643f - m * (originalHeight * scale + 10)
            );

            auto slot = SpriteBuilder()
                .setTexture(UIConfig::UIResources::ITEM_BLOCK)
                .setScale(scale)
                .setPosition(slotPos)
                .setTag(m * kRowSize + i)
                .setZOrder(2)
                .addToParent(this)
                .build();

            _itemSlots.pushBack(slot);
        }
    }
}

void InventoryUI::updateDisplay() {
    if (!_inventory) {
        CCLOG("Warning: _inventory is nullptr");
        return;
    }

    for (int m = 0; m < 3; m++) {
        for (int i = 0; i < kRowSize; ++i) {
            int serial_number = i + m * 12;
            auto slot = _itemSlots.at(serial_number);
            if (!slot) continue;

            slot->setVisible(true);

            auto item = _inventory->GetItemAt(serial_number + 1);
            int itemCount = _inventory->GetItemCountAt(serial_number + 1);

            if (item) {
                CCLOG("Item in slot %d: %s", serial_number + 1, item->GetName().c_str());
            } else {
                CCLOG("No item in slot %d", serial_number + 1);
            }

            if (item) {
                slot->removeAllChildren();

                auto itemSprite = SpriteBuilder()
                    .setTexture(item->initial_pic)
                    .setPosition(slot->getContentSize() / 2)
                    .setScale(0.7f)
                    .setZOrder(3)
                    .addToParent(slot)
                    .build();

                if (itemSprite) {
                    CCLOG("Loading item sprite: %s", item->initial_pic.c_str());
                } else {
                    CCLOG("Error loading item sprite: %s", item->initial_pic.c_str());
                }

                auto countLabel = static_cast<Label*>(slot->getChildByTag(200 + serial_number));
                if (!countLabel) {
                    countLabel = LabelBuilder()
                        .setText(std::to_string(itemCount))
                        .setFont("fonts/Comic Sans MS.ttf", 20)
                        .setColor(Color3B(255, 153, 0))
                        .setPosition(slot->getContentSize().width * 0.8, slot->getContentSize().height * 0.2)
                        .setTag(200 + serial_number)
                        .setZOrder(4)
                        .addToParent(slot)
                        .build();
                } else {
                    countLabel->setString(std::to_string(itemCount));
                }

                auto listener = EventListenerMouse::create();

                listener->onMouseMove = [this, slot, itemSprite, countLabel](EventMouse* event) {
                    Vec2 mousePos = Vec2(event->getCursorX(), event->getCursorY());
                    mousePos = this->convertToNodeSpace(mousePos);
                    if (slot && slot->getBoundingBox().containsPoint(mousePos)) {
                        itemSprite->setScale(1.1f);
                        countLabel->setScale(1.5f);
                    } else if (slot && itemSprite != currentItemSprite) {
                        itemSprite->setScale(0.7f);
                        countLabel->setScale(1.0f);
                    }
                };

                listener->onMouseDown = [this, slot, itemSprite, serial_number](EventMouse* event) {
                    Vec2 mousePos = Vec2(event->getCursorX(), event->getCursorY());
                    mousePos = this->convertToNodeSpace(mousePos);

                    if (slot->getBoundingBox().containsPoint(mousePos)) {
                        if (!isClick) {
                            currentItemSprite = itemSprite;
                            _selectedSlot = serial_number + 1;
                            CCLOG("_selectedSlot:%d", _selectedSlot);
                        } else {
                            currentItemSprite = nullptr;
                        }
                        isClick = !isClick;
                    }
                };

                _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, itemSprite);
            } else {
                slot->removeAllChildren();

                auto countLabel = static_cast<Label*>(slot->getChildByTag(200 + i));
                if (countLabel) {
                    countLabel->removeFromParent();
                }
            }
        }
    }

    // 更新物品槽信息标签（如果存在的话）
    if (_itemLabel) {
        if (auto selectedItem = _inventory->GetSelectedItem()) {
            _itemLabel->setString("Selected: " + selectedItem->GetName());
        } else {
            _itemLabel->setString("No item selected.");
        }
    } else {
        CCLOG("Warning: _itemLabel is nullptr");
    }
}

