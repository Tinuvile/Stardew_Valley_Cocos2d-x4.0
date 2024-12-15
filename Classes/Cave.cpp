#include "AppDelegate.h"
#include "farm.h"
#include "Cave.h"
#include "Player.h"
#include "physics/CCPhysicsWorld.h"
#include "ui/CocosGUI.h"
#include "vector"

USING_NS_CC;

Cave::Cave() {}

Cave::~Cave() {}

bool Cave::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    button = cocos2d::Sprite::create("CloseNormal.png");
    this->addChild(button, 11);

    // 设置计时器标签
    _timerLabelD = Label::createWithTTF("Day: 0", "fonts/Marker Felt.ttf", 24);
    this->addChild(_timerLabelD, 10);
    _timerLabelD->setScale(2.3f);

    _timerLabelH = Label::createWithTTF("0:00", "fonts/Marker Felt.ttf", 24);
    this->addChild(_timerLabelH, 10);
    _timerLabelH->setScale(2.3f);

    _timerLabelS = Label::createWithTTF("Spring", "fonts/Marker Felt.ttf", 24);
    this->addChild(_timerLabelS, 10);
    _timerLabelS->setScale(2.3f);

    // 恢复种植
    AllInitialize_ore();

    // 创建并初始化 Label 来显示角色的位置
    _positionLabel = Label::createWithTTF("Position: (0, 0)", "fonts/Marker Felt.ttf", 24);
    if (_positionLabel)
    {
        this->addChild(_positionLabel, 10);
        _positionLabel->setScale(2.3f);
    }

    // 设置背景图片
    auto background_real = Sprite::create("Cave/cave.png");
    background_real->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(background_real, 1);
    background_real->setScale(2.9f);

    auto background = Sprite::create("Cave/cave_path.png");
    this->addChild(background, 5);
    background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    background->setScale(2.9f);


    Vec2 spritePosition = background->getPosition();   // 获取精灵的位置（中心点）
    Size spriteSize = background->getContentSize();    // 获取精灵的尺寸（宽度和高度）
  

    // 计算左下角的坐标
    Vec2 leftBottomPosition = Vec2(
        spritePosition.x - background->getScaleX() * spriteSize.width / 2,   // 中心点 x 坐标减去宽度的一半
        spritePosition.y - background->getScaleY() * spriteSize.height / 2   // 中心点 y 坐标减去高度的一半
    );
   

    Image img;
    if (img.initWithImageFile("Cave/cave_path.png"))
    {
        int width = img.getWidth();
        int height = img.getHeight();

        // 获取像素数据
        unsigned char* data = img.getData();

        // 遍历所有像素，检查是否有内容（透明度大于0）
        for (int y = 0; y < height; y = y + 8)
        {
            for (int x = 0; x < width; x = x + 8)
            {
                // 获取当前像素的 RGBA 值
                int index = (y * width + x) * 4;    // 每个像素占用 4 个字节 (RGBA)
                unsigned char a = data[index + 3];  // 透明度

                // 如果透明度 (alpha) 大于 0，表示此像素有内容
                if (a > 0)
                {
                    float screenX = leftBottomPosition.x + x * background->getScaleX();
                    float screenY = leftBottomPosition.y + (height - y - 1) * background->getScaleY();  // 注意 Y 轴反向
                    nonTransparentPixels.push_back(Vec2(screenX, screenY));                             // 记录屏幕坐标
                }
            }
        }
    }

    // 初始化角色并将其添加到场景
    if (player1->getParent() == NULL) {
        this->addChild(player1, 17);
        
        player1->setPosition(500,650);      
        player1->speed = 6.1f;
        player1->setScale(2.3f);
        player1->setAnchorPoint(Vec2(0.5f, 0.2f));
    }    

    
    // 启动人物的定时器
    player1->schedule([=](float dt) {
        player1->player1_move();
        }, 0.05f, "player1_move");

    player1->schedule([=](float dt) {
        player1->player_change();
        }, 0.3f, "player_change");


    // 计算背景精灵的缩放后范围
    float scaledWidth = background->getContentSize().width * background->getScaleX();
    float scaledHeight = background->getContentSize().height * background->getScaleY();

    // 构造 Follow 的边界 Rect
    auto followRect = cocos2d::Rect(leftBottomPosition.x, leftBottomPosition.y, scaledWidth, scaledHeight);

    // 创建 Follow 动作并限制玩家在背景范围内移动
    auto followAction = Follow::create(player1, followRect);
    this->runAction(followAction);

    // 定期更新玩家状态
    this->schedule([this](float dt) {
        this->checkPlayerPosition();  // 检查玩家是否接近轮廓点
        }, 0.01f, "check_position_key");

    auto listener = EventListenerMouse::create();
    listener->onMouseDown = [this](Event* event) {
       
        // 获取鼠标点击的位置
        auto mouseEvent = static_cast<EventMouse*>(event);
        Vec2 clickPos(mouseEvent->getCursorX(), mouseEvent->getCursorY());
        clickPos = this->convertToNodeSpace(clickPos);

        // 判断点击位置是否在精灵范围内
        if (button != nullptr && button->getBoundingBox().containsPoint(clickPos)) {
            Director::getInstance()->end();
        }
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, button);

    // 设置键盘监听器
    auto listenerWithPlayer = EventListenerKeyboard::create();
    listenerWithPlayer->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event)
        {
            if (keyCode == EventKeyboard::KeyCode::KEY_ENTER) {
                isEnterKeyPressed = true;
                CCLOG("Enter key pressed. ");
            }
            else if (keyCode == EventKeyboard::KeyCode::KEY_M) {
                isMKeyPressed = true;
            }
        };

    listenerWithPlayer->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event* event)
        {
            // 释放 Enter 键时，设置为 false
            if (keyCode == EventKeyboard::KeyCode::KEY_ENTER) {
                isEnterKeyPressed = false;
            }
            if (keyCode == EventKeyboard::KeyCode::KEY_M) {
                isMKeyPressed = false;
            }
        };

    // 将监听器添加到事件分发器中
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerWithPlayer, this);

    return true;
}


Cave* Cave::create()
{
    Cave* scene = new Cave();
    if (scene && scene->init())
    {
        scene->autorelease();
        return scene;
    }
    CC_SAFE_DELETE(scene);
    return nullptr;
}

void Cave::AllInitialize_ore() {

    for (auto it = Ore_information.begin(); it != Ore_information.end(); /* no increment here */) {

        auto ore = *it;  // 解引用迭代器以访问 Crop 对象
        
        if (IsNextDay) {
            if (!ore->available) {
                if (season[Season] * 7 + day - ore->mining_day >= ore->recover_time) {
                    ore->available = true;
                }
            }
        }

        cocos2d::log("Create Ore");

        if (ore->available) {
            auto temp = Sprite::create(ore->initial_pic);
            this->addChild(temp, 5);
            temp->setPosition(ore->position);
            temp->setScale(2.7f);
        }
        else {
            auto temp = Sprite::create(ore->mining_pic);
            this->addChild(temp, 5);
            temp->setPosition(ore->position);
            temp->setScale(2.7f);
        }
        it++;


    }

}

// 检查玩家是否接近背景的轮廓点
void Cave::checkPlayerPosition()
{

    // 获取玩家的位置
    Vec2 playerPos = player1->getPosition();

    // 更新位置标签的内容
    if (_positionLabel)
    {
        _positionLabel->setString("Position: (" + std::to_string(static_cast<int>(playerPos.x)) + ", " + std::to_string(static_cast<int>(playerPos.y)) + ")");
    
    }
    
    // 更新计时器显示
    remainingTime++;
    _timerLabelD->setString("Day: " + std ::to_string(day));
    _timerLabelH->setString(std::to_string(remainingTime / 1800) + ":00");
    _timerLabelS->setString(Season);
    if (remainingTime == 43200) {
        
        day++;

        IsNextDay = true;

        if (day == 8) {
            if (Season == "Spring") {
                Season = "Summer";
            }
            else if (Season == "Summer") {
                Season = "Autumn";
            }
            else {
                Season = "Winter";
            }
            day = 1;
        }


        for (auto it = Crop_information.begin(); it != Crop_information.end(); /* no increment here */) {

            auto crop = *it;  // 解引用迭代器以访问 Crop 对象

            // 判断前一天是否浇水
            if ((crop->watered == false) && (crop->GetPhase() != Phase::MATURE)) {
                // 判断是否已经进入枯萎状态
                if (crop->GetPhase() != Phase::SAPLESS) {
                    crop->ChangePhase(Phase::SAPLESS);
                    crop->ChangMatureNeeded(2); // 延迟两天收获
                }
                else {
                    // 删除元素并更新迭代器
                    it = Crop_information.erase(it);
                }
                ++it;
                continue;  // 跳过后续代码，直接继续循环
            }
            else {
                // 更新状态
                crop->UpdateGrowth();
            }

            it++;
        }

         remainingTime = 0;
         player1->removeFromParent();
         auto nextday = Myhouse::create();
         Director::getInstance()->replaceScene(nextday);
           

    }

    // 更新标签位置
    float currentx = 0, currenty = 0;
    if (playerPos.x <= 786) {
        currentx = 786;
    }
    else if (playerPos.x >= 817) {
        currentx = 817;
    }
    else {
        currentx = playerPos.x;  
    }

    if (playerPos.y >= 808) {
        currenty = 808;
    }
    else if (playerPos.y <= 460) {
        currenty = 460;
    }
    else {
        currenty = playerPos.y;
    }

    _timerLabelD->setPosition(currentx - 710, currenty + 570);
    _timerLabelH->setPosition(currentx - 570, currenty + 570);
    _timerLabelS->setPosition(currentx - 410, currenty + 570);
    _positionLabel->setPosition(currentx - 570, currenty + 490);
    button->setPosition(currentx + 730, currenty - 590);

    if (isMKeyPressed) {
        for (auto it = Ore_information.begin(); it != Ore_information.end(); /* no increment here */) {

            auto ore = *it;  // 解引用迭代器以访问 Crop 对象

            float distance = ore->position.distance(playerPos);
            if (distance <= 75 && ore->available) {

                ore->available = false;

                ore->mining_day = season[Season] * 7 + day;

                if (player1->pic_path == "character1/player_right3.png") {
                   
                    player1->setTexture("character1/player_plant3.png");
                    player1->setScale(3.9f);

                    // 延迟0.3秒后切换到第二个图片
                    player1->scheduleOnce([=](float dt) {
                        player1->setTexture("character1/player_plant4.png");  // 更换为player_plant2
                        player1->setScale(4.1f);
                        }, 0.15f, "change_image1_key");

                    // 延迟0.6秒后切换到第三个图片
                    player1->scheduleOnce([=](float dt) {
                        player1->setTexture("character1/player_right3.png"); // 更换为player_left3
                        player1->setScale(2.3f);
                        auto earth = Sprite::create("Ore/earth.png");
                        this->addChild(earth, 5);
                        earth->setPosition(ore->position);
                        earth->setScale(2.9f);
                        auto temp = Sprite::create(ore->mining_pic);
                        this->addChild(temp, 6);
                        temp->setPosition(ore->position);
                        temp->setScale(2.7f);
                        }, 0.35f, "change_image2_key");

                }
                else {
                    player1->setTexture("character1/player_plant1.png");
                    player1->setScale(3.9f);

                    // 延迟0.3秒后切换到第二个图片
                    player1->scheduleOnce([=](float dt) {
                        player1->setTexture("character1/player_plant2.png");  // 更换为player_plant2
                        player1->setScale(4.1f);
                        }, 0.15f, "change_image1_key");

                    // 延迟0.6秒后切换到第三个图片
                    player1->scheduleOnce([=](float dt) {
                        player1->setTexture("character1/player_left3.png"); // 更换为player_left3
                        player1->setScale(2.3f);
                        auto earth = Sprite::create("Ore/earth.png");
                        this->addChild(earth, 5);
                        earth->setPosition(ore->position);
                        earth->setScale(2.9f);
                        auto temp = Sprite::create(ore->mining_pic);
                        this->addChild(temp, 6);
                        temp->setPosition(ore->position);
                        temp->setScale(2.7f);
                        }, 0.35f, "change_image2_key");
                }
            }


            it++;

        }
    }

    if (Out_cave.containsPoint(playerPos)) {
        if (isEnterKeyPressed) {
            player1->removeFromParent();
            auto nextscene = farm::create();
            Director::getInstance()->replaceScene(nextscene);
        }
    }

    for (const auto& point : nonTransparentPixels)
    {
        // 计算玩家与轮廓点之间的距离
        float distance = 0;

        Vec2 temp;
        temp = playerPos;
        temp.x -= player1->speed;
        distance = temp.distance(point);
        if (distance <= 17) {
            player1->moveLeft = false;
        }
        else {
            if (player1->leftpressed == false) {
                player1->moveLeft = true;
            }
        }
        
        temp = playerPos;
        temp.y -= 10;
        distance = temp.distance(point);
        if (distance <= 15) {
            player1->moveDown = false;
        }
        else {
            if (player1->downpressed == false) {
                player1->moveDown = true;
            }
        }

        temp = playerPos;
        temp.y += 10;
        distance = temp.distance(point);
        if (distance <= 15) {
            player1->moveUp = false;
        }
        else {
            if (player1->uppressed == false) {
                player1->moveUp = true;
            }
        }

        temp = playerPos;
        temp.x += 10;
        distance = temp.distance(point);
        if (distance <= 15) {
            player1->moveRight = false;
        }
        else{
            if (player1->rightpressed == false) {
                player1->moveRight = true;
            }
        }
       
    }
    

}

int Cave::getRegionNumber(Vec2 pos) {

    int region_number = 1;

    return region_number;
}






