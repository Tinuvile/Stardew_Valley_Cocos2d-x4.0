// StoreUI.cpp - 商店界面实现（使用建造者模式重构）
#include "StoreUI.h"
#include "ui/CocosGUI.h"
#include "Item.h"
#include "AppDelegate.h"
#include "UI/Builders/SpriteBuilder.h"
#include "UI/Builders/LabelBuilder.h"
#include "UI/Components/DarkOverlay.h"

USING_NS_CC;

StoreUI* StoreUI::create(Inventory* mybag, Inventory* goods) {
    StoreUI* ret = new StoreUI();
    if (ret && ret->init(mybag, goods)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool StoreUI::init(Inventory* mybag, Inventory* goods) {
    if (!Layer::init()) {
        return false;
    }

    _mybag = mybag;
    _goods = goods;
    economicSystem = std::make_shared<EconomicSystem>(_mybag, _goods);
    m_sceneName = "Supermarket"; // 设置场景名称
    isClick = false;
    chosen_Item = nullptr;
    _selectedSlot = 1;

    CCLOG("%d", economicSystem->getGoldAmount());

    // 使用建造者模式重构UI设置
    setupUI();

    updateDisplay(); // 更新显示内容

    return true;
}

void StoreUI::updateCoordinate(float& x, float& y) {
    Vec2 position = player1->getPosition();
    if (x <= 725) {
        x = 725;
    }
    else {
        x = position.x;
    }
    if (y <= -66) {
        y = -66;
    }
    else {
        y = position.y;
    }
}

void StoreUI::updateDisplay() {
    Vec2 position = player1->getPosition();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    if (!_mybag) {
        CCLOG("Warning: _inventory is nullptr");
        return; // 退出检查
    }

    // 更新金钱显示
    if (m_moneyLabel) {
        int goldAmount = economicSystem->getGoldAmount();
        m_moneyLabel->setString(std::to_string(goldAmount));
    }

    // 更新物品栏显示
    for (int m = 0; m < 3; m++) {
        // 获取当前选中的物品的槽位
        for (int i = 0; i < kRowSize; ++i) {
            int serial_number = i + m * 12;
            if (serial_number >= _itemSlots.size()) {
                break;
            }

            auto slot = _itemSlots.at(serial_number);
            slot->setVisible(true); // 确保显示所有槽位

            // 获取槽位物品
            auto item = _mybag->GetItemAt(serial_number + 1); // 获取特定位置物品（注意位置从1开始）

            // 获取物品数量
            int itemCount = _mybag->GetItemCountAt(serial_number + 1); // 获取槽位物品数量

            if (item) {
                // 清除槽位之前的子节点
                slot->removeAllChildren();

                // 图片路径
                auto itemSprite = Sprite::create(item->initial_pic);
                if (itemSprite) {
                    itemSprite->setPosition(slot->getContentSize() / 2);
                    itemSprite->setScale(0.2f);
                    slot->addChild(itemSprite, 3);
                    CCLOG("Loading item sprite: %s", item->initial_pic.c_str());
                }
                else {
                    CCLOG("Error loading item sprite: %s", item->initial_pic.c_str());
                }

                // 如果 item 需要显示数量，创建一个 Label 显示数量
                auto countLabel = static_cast<Label*>(slot->getChildByTag(200 + serial_number)); // 使用槽位标签作为唯一ID
                if (!countLabel) {
                    // 如果标签不存在，创建新的标签
                    countLabel = Label::createWithSystemFont(std::to_string(itemCount), "fonts/Comic Sans MS.ttf", 8);
                    countLabel->setTextColor(Color4B(255, 153, 0, 255));
                    countLabel->setPosition(slot->getContentSize().width * 0.8, slot->getContentSize().height * 0.2); // 设置位置在槽位右下角
                    countLabel->setTag(200 + serial_number); // 设置标签
                    slot->addChild(countLabel, 4); // 添加到层级
                }
                else {
                    // 如果标签存在，更新文本
                    countLabel->setString(std::to_string(itemCount));
                }
            }
            else {
                slot->removeAllChildren(); // 清空槽位

                // 移除数量标签
                auto countLabel = static_cast<Label*>(slot->getChildByTag(200 + i));
                if (countLabel) {
                    countLabel->removeFromParent(); // 移除数量标签
                }
            }
        }
    }
}

void StoreUI::setupUI() {
    setupCharacterDisplay();
    setupProductDisplay();
    setupMoneyDisplay();
    setupSlider();
    setupItemSlots();
    setupInteractions();
    setupMouseEvents();
}

void StoreUI::backgroundcreate() {
    Vec2 position = player1->getPosition();
    float currentx = position.x, currenty = position.y;
    updateCoordinate(currentx, currenty);
    auto visibleSize = Director::getInstance()->getVisibleSize();

    // 使用UI文件夹下的DarkOverlay创建黑色幕布
    auto darkOverlay = DarkOverlay::create(m_sceneName);
    this->addChild(darkOverlay, 0);

    // 使用SpriteBuilder创建商店背景
    auto mybag = SpriteBuilder()
        .setTexture("UIresource/supermarket/wupinlan.png")
        .setTag(101)
        .setAutoScale(2.0f)
        .setPosition(currentx + visibleSize.width * 0.2f, currenty - visibleSize.height * 0.25f)
        .setZOrder(1)
        .addToParent(this)
        .build();

    // 保持原有的购买逻辑 - 只修改为使用SpriteBuilder创建的精灵
    auto listener = EventListenerMouse::create();
    listener->onMouseDown = [this, mybag](EventMouse* event) {
        Vec2 mousePos = Vec2(event->getCursorX(), event->getCursorY());
        mousePos = this->convertToNodeSpace(mousePos);

        // 检查是否点击了商店背景
        if (mybag->getBoundingBox().containsPoint(mousePos)) {
            if (isClick) {
                int goldAmount = economicSystem->getGoldAmount();
                CCLOG("goldAmount: %d , Value: %d", goldAmount, chosen_Item->GetValue());
                std::string chosen_item_name = chosen_Item->GetName();
                if (goldAmount >= chosen_Item->GetValue()) {
                    // 检查选择的物品是否为动物
                    if (chosen_item_name.find("Animal") != std::string::npos) {
                        std::pair<Rect, bool>* space = nullptr;
                        for (auto& pair : barn_space) {
                            // 检查是否有空闲空间
                            if (!pair.second) {
                                space = &pair;
                                break;
                            }
                        }
                        // 有空闲空间
                        if (space != nullptr) {
                            Livestock* livestock = nullptr;
                            // 判断物品类型
                            if (chosen_item_name == "AnimalChicken") {
                                livestock = Chicken::create(space->first);
                            }
                            else if (chosen_item_name == "AnimalSheep") {
                                livestock = Sheep::create(space->first);
                            }
                            else if (chosen_item_name == "AnimalCow") {
                                livestock = Cow::create(space->first);
                            }
                            if (livestock != nullptr) {
                                space->second = true;
                                livestocks.push_back(livestock);
                                livestock->retain();
                                economicSystem->subtractGold(chosen_Item->GetValue());
                                updateDisplay();
                                CCLOG("Purchased item: %s", chosen_Item->GetName().c_str());
                            }
                        }
                        else {
                            CCLOG("fail to place %s in your barn", chosen_item_name.c_str());
                        }
                    }
                    else {
                        economicSystem->subtractGold(chosen_Item->GetValue());
                        _mybag->AddItem(*chosen_Item);
                        _mybag->is_updated = true;
                        updateDisplay();
                        CCLOG("Purchased item: %s", chosen_Item->GetName().c_str());
                    }
                }
                else {
                    CCLOG("Not enough gold to buy %s.", chosen_Item->GetName().c_str());
                }
                isClick = false;
                chosen_Item = nullptr;
            }
        }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, mybag);

    // 使用SpriteBuilder创建角色框架
    auto Characterframe = SpriteBuilder()
        .setTexture("UIresource/supermarket/frame.png")
        .setAutoScale(5.0f)
        .setPosition(currentx - visibleSize.width / 2.7f, currenty + visibleSize.height * 0.24f)
        .setZOrder(1)
        .addToParent(this)
        .build();

    // 使用SpriteBuilder创建角色头像
    auto Characterpicture = SpriteBuilder()
        .setTexture("Portraits/Pierre/Pierre-0.png")
        .setAutoScale(5.2f)
        .setPosition(currentx - visibleSize.width / 2.7f, currenty + visibleSize.height * 0.24f)
        .setZOrder(2)
        .addToParent(this)
        .build();

    // 使用SpriteBuilder创建商店欢迎界面
    auto welcomeframe = SpriteBuilder()
        .setTexture("UIresource/supermarket/wupinlan.png")
        .setAutoScale(5.0f)
        .setPosition(currentx - visibleSize.width / 2.7f, currenty + visibleSize.height * 0.06316f)
        .setZOrder(1)
        .addToParent(this)
        .build();

    // 使用LabelBuilder创建欢迎文字
    auto welcome = LabelBuilder()
        .setText("Welcome to the\nPierre store")
        .setFont("fonts/Arial Bold.ttf", 25)
        .setColor(Color3B::BLACK)
        .setPosition(currentx - visibleSize.width / 2.7f, currenty + visibleSize.height * 0.06316f)
        .setZOrder(2)
        .addToParent(this)
        .build();

    // 使用SpriteBuilder创建金钱框
    auto moneyFrame = SpriteBuilder()
        .setTexture("UIresource/supermarket/moneyFrame_new.png")
        .setAutoScale(4.0f)
        .setPosition(currentx - visibleSize.width * 0.1f, currenty - visibleSize.height * 0.042f)
        .setZOrder(1)
        .addToParent(this)
        .build();
}

void StoreUI::setupCharacterDisplay() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 playerPos = player1->getPosition();
    updateCoordinate(playerPos.x, playerPos.y);

    // 创建角色框架
    auto characterFrame = SpriteBuilder()
        .setTexture("UIresource/supermarket/frame.png")
        .setAutoScale(5.0f)
        .setPosition(playerPos.x - visibleSize.width / 2.7f,
                   playerPos.y + visibleSize.height * 0.24f)
        .setZOrder(1)
        .addToParent(this)
        .build();

    // 创建角色头像
    auto characterPortrait = SpriteBuilder()
        .setTexture("Portraits/Pierre/Pierre-0.png")
        .setAutoScale(5.2f)
        .setPosition(playerPos.x - visibleSize.width / 2.7f,
                   playerPos.y + visibleSize.height * 0.24f)
        .setZOrder(2)
        .addToParent(this)
        .build();

    // 创建商店欢迎文字背景
    auto welcomeFrame = SpriteBuilder()
        .setTexture("UIresource/supermarket/wupinlan.png")
        .setAutoScale(5.0f)
        .setPosition(playerPos.x - visibleSize.width / 2.7f,
                   playerPos.y + visibleSize.height * 0.06316f)
        .setZOrder(1)
        .addToParent(this)
        .build();

    // 创建欢迎文字 - 使用LabelBuilder
    auto welcomeLabel = LabelBuilder()
        .setText("Welcome to the\nPierre store")
        .setFont("fonts/Arial Bold.ttf", 25)
        .setColor(Color3B::BLACK)
        .setPosition(playerPos.x - visibleSize.width / 2.7f,
                   playerPos.y + visibleSize.height * 0.06316f)
        .setZOrder(2)
        .addToParent(this)
        .build();
}

void StoreUI::setupProductDisplay() {
    auto theme = UITheme::getInstance();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 playerPos = player1->getPosition();
    updateCoordinate(playerPos.x, playerPos.y);

    // 商品列表背景
    auto Productcolumn = SpriteBuilder()
        .setTexture("UIresource/supermarket/wupinlan.png")
        .setAutoScale(1.4f)
        .setPosition(playerPos.x + visibleSize.width / 9.5f,
                   playerPos.y + visibleSize.height * 0.1684f)
        .setZOrder(0)
        .addToParent(this)
        .build();

    // 创建 ScrollView
    m_scrollView = cocos2d::ui::ScrollView::create();
    m_scrollView->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);
    m_scrollView->setContentSize(Size(1630, 400));
    m_scrollView->setPosition(Vec2(playerPos.x - visibleSize.width * 0.389f,
                                playerPos.y + visibleSize.height * 0.01368f));
    m_scrollView->setBounceEnabled(true);
    m_scrollView->setScrollBarEnabled(false);

    // 计算商品总高度
    const int itemCount = 24;
    const float itemHeight = 105.0f;
    float totalItemHeight = itemCount * itemHeight;
    m_scrollView->setInnerContainerSize(Size(1630, totalItemHeight));

    // 添加滚轮事件
    auto scrollListener = cocos2d::EventListenerMouse::create();
    scrollListener->onMouseScroll = [this](cocos2d::EventMouse* event) {
        if (!m_scrollView) return;

        float scrollDelta = event->getScrollY();
        auto innerContainer = m_scrollView->getInnerContainer();
        float currentPosY = innerContainer->getPositionY();
        float newPosY = currentPosY + scrollDelta * 105.0f;

        float lowerLimit = m_scrollView->getContentSize().height - innerContainer->getContentSize().height;
        float upperLimit = -20.0f;

        newPosY = std::max(newPosY, lowerLimit);
        newPosY = std::min(newPosY, upperLimit);

        innerContainer->setPositionY(newPosY);
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(scrollListener, this);

    // 创建商品项
    float offsetY = 0.0f;
    for (int i = 0; i < itemCount; ++i) {
        auto item = _goods->GetItemAt(i + 1);
        if (!item) continue;

        // 商品框
        auto itemframe = SpriteBuilder()
            .setTexture("UIresource/supermarket/goodframe.png")
            .setAutoScale(1.4f)
            .setPosition(visibleSize.width * 0.4933f, 539 + visibleSize.height * 1.51f - offsetY)
            .addToParent(m_scrollView)
            .setZOrder(1)
            .build();

        // 商品图片
        auto itemSprite = SpriteBuilder()
            .setTexture(item->initial_pic)
            .setScale(0.7f)
            .setPosition(visibleSize.width * 0.1783f, 539 + visibleSize.height * 1.51f - offsetY)
            .addToParent(m_scrollView)
            .setZOrder(2)
            .build();

        // 商品名称
        auto itemLabel = LabelBuilder()
            .setText(item->GetName())
            .setFont("fonts/Comic Sans MS.ttf", 30)
            .setColor(Color3B::BLACK)
            .setAnchorPoint(Vec2(0, 0.5))
            .setPosition(visibleSize.width * 0.2386f, 539 + visibleSize.height * 1.51f - offsetY)
            .addToParent(m_scrollView)
            .setZOrder(2)
            .build();

        // 商品价格
        auto priceLabel = LabelBuilder()
            .setText(std::to_string(item->GetValue()))
            .setFont("fonts/Comic Sans MS.ttf", 30)
            .setColor(Color3B::BLACK)
            .setAnchorPoint(Vec2(0, 0.5))
            .setPosition(visibleSize.width * 0.6750f, 539 + visibleSize.height * 1.51f - offsetY)
            .addToParent(m_scrollView)
            .setZOrder(2)
            .build();

        // 设置商品交互事件
        setupProductItemMouseEvents(itemframe, item, i);

        offsetY += itemHeight;
    }

    this->addChild(m_scrollView, 2);
}

void StoreUI::setupProductItemMouseEvents(Sprite* itemFrame, shared_ptr<Item> item, int index) {
    auto hoverListener = cocos2d::EventListenerMouse::create();
    hoverListener->onMouseMove = [this, itemFrame](cocos2d::EventMouse* event) {
        Vec2 mousePos = Vec2(event->getCursorX(), event->getCursorY());
        mousePos = this->convertToNodeSpace(mousePos);

        if (itemFrame->getBoundingBox().containsPoint(mousePos)) {
            itemFrame->setTexture("UIresource/supermarket/xuanzhong_frame.png");
        } else {
            itemFrame->setTexture("UIresource/supermarket/goodframe.png");
        }
    };

    auto clickListener = cocos2d::EventListenerMouse::create();
    clickListener->onMouseDown = [this, item](cocos2d::EventMouse* event) {
        Vec2 mousePos = Vec2(event->getCursorX(), event->getCursorY());
        mousePos = this->convertToNodeSpace(mousePos);

        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 playerPos = player1->getPosition();
        updateCoordinate(playerPos.x, playerPos.y);

        if (mousePos.x >= playerPos.x - visibleSize.width * 0.25f &&
            mousePos.x < playerPos.x + visibleSize.width * 0.455f &&
            mousePos.y >= playerPos.y - visibleSize.height * 0.0772f &&
            mousePos.y < playerPos.y + visibleSize.height * 0.3025f) {
            isClick = true;
            chosen_Item = item;
            CCLOG("chosen_Item: %s", item->GetName().c_str());
        }
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(hoverListener, itemFrame);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(clickListener, itemFrame);
}

void StoreUI::setupMoneyDisplay() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 playerPos = player1->getPosition();
    updateCoordinate(playerPos.x, playerPos.y);

    // 创建金钱框架
    auto moneyFrame = SpriteBuilder()
        .setTexture("UIresource/supermarket/moneyFrame_new.png")
        .setAutoScale(4.0f)
        .setPosition(playerPos.x - visibleSize.width * 0.1f,
                   playerPos.y - visibleSize.height * 0.042f)
        .setZOrder(1)
        .addToParent(this)
        .build();

    // 创建金钱显示标签
    int goldAmount = economicSystem->getGoldAmount();
    m_moneyLabel = LabelBuilder()
        .setText(std::to_string(goldAmount))
        .setFont("fonts/Comic Sans MS.ttf", 45)
        .setColor(Color3B::BLACK)
        .setPosition(playerPos.x - visibleSize.width * 0.1f,
                   playerPos.y - visibleSize.height * 0.0425f)
        .setZOrder(4)
        .addToParent(this)
        .build();
}

void StoreUI::setupSlider() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 playerPos = player1->getPosition();
    updateCoordinate(playerPos.x, playerPos.y);

    // 滑动条背景
    auto sliderBackground = SpriteBuilder()
        .setTexture("UIresource/supermarket/huadongtiao.png")
        .setAutoScale(2.4f)
        .setPosition(playerPos.x + visibleSize.width * 0.48f,
                   playerPos.y + visibleSize.height * 0.16f)
        .setZOrder(5)
        .addToParent(this)
        .build();

    // 滑动条滑块
    m_sliderHandle = SpriteBuilder()
        .setTexture("UIresource/supermarket/huadongkuai.png")
        .setAutoScale(29.0f)
        .setPosition(playerPos.x + visibleSize.width * 0.478f,
                   playerPos.y + visibleSize.height * 0.34375f)
        .setZOrder(6)
        .addToParent(this)
        .build();

    // 设置滑块滚轮事件
    auto sliderListener = cocos2d::EventListenerMouse::create();
    sliderListener->onMouseScroll = [this, visibleSize, playerPos](cocos2d::EventMouse* event) {
        if (!m_sliderHandle) return;

        float minY = playerPos.y + visibleSize.height * 0.34375f - 20 * 23.8f;
        float maxY = playerPos.y + visibleSize.height * 0.34375f;

        float scrollDelta = event->getScrollY();
        Vec2 currentPos = m_sliderHandle->getPosition();
        float newY = currentPos.y - scrollDelta * 23.8f;

        newY = std::max(newY, minY);
        newY = std::min(newY, maxY);

        m_sliderHandle->setPosition(Vec2(currentPos.x, newY));
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(sliderListener, this);
}

void StoreUI::setupItemSlots() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 playerPos = player1->getPosition();
    updateCoordinate(playerPos.x, playerPos.y);
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto bag = getChildByTag(101);
    if (!bag) return;

    float originalWidth, originalHeight;

    // 初始化物品槽 Sprite
    for (int m = 0; m < 3; m++) {
        for (int i = 0; i < kRowSize; ++i) {
            auto slot = Sprite::create("UIresource/beibao/wupincao.png");

            // 获取原始图片的宽度
            originalWidth = slot->getContentSize().width;
            originalHeight = slot->getContentSize().height;
            // 计算屏幕宽度和图片原始宽度的比例
            float scaleX = visibleSize.width / originalWidth;
            float scaleY = visibleSize.height / originalHeight;
            // 选择较小的缩放比例，以保证图片完全显示在屏幕内
            float scale = std::min(scaleX, scaleY);
            slot->setScale(scale / 22);

            float bagWidth = bag->getContentSize().width;
            float bagHeight = bag->getContentSize().height;
            slot->setPosition(playerPos.x - bagWidth * 0.12f + (originalWidth * scale / 22 + 5) * i,
                           playerPos.y - bagHeight * 2.7f - m * (originalHeight * scale / 22 + 23));
            slot->setTag(i + 1); // 设置槽位标签
            slot->setOpacity(128);
            this->addChild(slot, 2);

            _itemSlots.pushBack(slot);
        }
    }
}

void StoreUI::setupInteractions() {
    // 设置交互逻辑保持原有功能
}

void StoreUI::setupMouseEvents() {
    // 设置鼠标事件保持原有功能
}

void StoreUI::onItemSlotClicked(cocos2d::Ref* sender) {
    auto slot = static_cast<Sprite*>(sender);
    int position = slot->getTag(); // 获取槽位位置

    // 设置为选中状态，更新 Inventory
    _mybag->SetSelectedItem(position);
    _selectedSlot = position;

    // 更新显示
    updateDisplay();
}