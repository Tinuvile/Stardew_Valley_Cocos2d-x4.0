#include "AppDelegate.h"
#include "farm.h"
#include "Forest.h"
#include "Player.h"
#include "physics/CCPhysicsWorld.h"
#include "ui/CocosGUI.h"
#include "vector"

USING_NS_CC;

Forest::Forest() {}

Forest::~Forest() {}

bool Forest::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    button = cocos2d::Sprite::create("CloseNormal.png");
    this->addChild(button, 11);

    // 设置计时器标签
    TimeUI = Timesystem::create();
    this->addChild(TimeUI, 13);

    // 恢复种植
    AllInitialize_ore();

    if (Weather == "Rainy") {
        // 下雨
        createRainEffect();
    }

    // 创建并初始化 Label 来显示角色的位置
    _positionLabel = Label::createWithTTF("Position: (0, 0)", "fonts/Marker Felt.ttf", 24);
    if (_positionLabel)
    {
        this->addChild(_positionLabel, 10);
        _positionLabel->setScale(2.3f);
    }

    // 设置背景图片
    auto background_real = Sprite::create("forest/forest.png");
    background_real->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(background_real, 1);
    background_real->setScale(2.3f);

    auto background = Sprite::create("forest/forest_path.png");
    this->addChild(background, 5);
    background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    background->setScale(2.3f);

    auto background_up = Sprite::create("forest/forest_up.png");
    background_up->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(background_up, 7);
    background_up->setScale(2.3f);


    Vec2 spritePosition = background->getPosition();   // 获取精灵的位置（中心点）
    Size spriteSize = background->getContentSize();    // 获取精灵的尺寸（宽度和高度）
  

    // 计算左下角的坐标
    Vec2 leftBottomPosition = Vec2(
        spritePosition.x - background->getScaleX() * spriteSize.width / 2,   // 中心点 x 坐标减去宽度的一半
        spritePosition.y - background->getScaleY() * spriteSize.height / 2   // 中心点 y 坐标减去高度的一半
    );
   

    Image img;
    if (img.initWithImageFile("forest/forest_path.png"))
    {
        int width = img.getWidth();
        int height = img.getHeight();

        // 获取像素数据
        unsigned char* data = img.getData();

        // 遍历所有像素，检查是否有内容（透明度大于0）
        for (int y = 0; y < height; y = y + 2)
        {
            for (int x = 0; x < width; x = x + 2)
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
        this->addChild(player1, 6);
        for (auto& pair : W_lastplace) {
            if (pair.second == true) { 
                player1->setPosition(pair.first.second);
                pair.second = false;
            }
        }
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
            if (keyCode == EventKeyboard::KeyCode::KEY_ENTER || keyCode == EventKeyboard::KeyCode::KEY_KP_ENTER) {
                isEnterKeyPressed = true;
                CCLOG("Enter key pressed. ");
            }
            else if (keyCode == EventKeyboard::KeyCode::KEY_L) {
                isLKeyPressed = true;
            }
            else if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
                static int isOpen = 0;
                static InventoryUI* currentInventoryUI = nullptr;  // 保存当前显示的 InventoryUI  
                // 如果当前没有打开 InventoryUI，则打开它  
                if (currentInventoryUI == nullptr || isOpen == 0) {
                    isOpen = 1;
                    CCLOG ( "Opening inventory." );
                    currentInventoryUI = InventoryUI::create ( inventory , "Forest" );
                    this->addChild ( currentInventoryUI , 20 );  // 将 InventoryUI 添加到 Town 的上层  
                }
                // 如果已经打开 InventoryUI，则关闭它  
                else {
                    isOpen = 0;
                    CCLOG ( "Closing inventory." );
                    this->removeChild ( currentInventoryUI , true );  // 从当前场景中移除 InventoryUI  
                    currentInventoryUI = nullptr;  // 重置指针  
                }
            }
        };

    listenerWithPlayer->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event* event)
        {
            // 释放 Enter 键时，设置为 false
            if (keyCode == EventKeyboard::KeyCode::KEY_ENTER || keyCode == EventKeyboard::KeyCode::KEY_KP_ENTER) {
                isEnterKeyPressed = false;
            }
            if (keyCode == EventKeyboard::KeyCode::KEY_L) {
                isLKeyPressed = false;
            }
        };

    // 将监听器添加到事件分发器中
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerWithPlayer, this);

    //界面下的背包显示
    miniBag = mini_bag::create ( inventory );
    miniBag->setScale ( 1.0f );
    Vec2 pos = miniBag->getPosition ();
    if (miniBag != NULL) {
        cocos2d::log ( "miniBagtest %f" , pos.x );
    }
    if (!this->getChildByName ( "mini_bag" )) {
        this->addChild ( miniBag , 10 , "mini_bag" );
    }


    // 更新物品栏
    schedule ( [=]( float deltaTime ) {
        if (inventory->is_updated == true) {
            miniBag->updateDisplay ();
            inventory->is_updated = false;
        }
        } , 0.1f , "item_update_key" );

    return true;
}


Forest* Forest::create()
{
    Forest* scene = new Forest();
    if (scene && scene->init())
    {
        scene->autorelease();
        return scene;
    }
    CC_SAFE_DELETE(scene);
    return nullptr;
}

void  Forest::AllInitialize_ore() {

    for (auto it = Tree_information.begin(); it != Tree_information.end(); /* no increment here */) {

        auto tree = *it;  // 解引用迭代器以访问 Crop 对象

      
        tree->recover_time = 2;

        if (!tree->available) {
            if (season[Season] * 7 + day - tree->mining_day >= tree->recover_time) {
                tree->available = true;
            }
        }
        

        if (tree->available) {

            if (Season == "Autumn" || Season == "Winter") {
                auto temp = Sprite::create(tree->Y_Ini_pic);
                this->addChild(temp, 5);
                temp->setPosition(tree->position);
                temp->setScale(3.1f);
            }
            else {
                auto temp = Sprite::create(tree->initial_pic);
                this->addChild(temp, 5);
                temp->setPosition(tree->position);
                temp->setScale(3.1f);
            }
        }
        else {
            auto temp = Sprite::create(tree->G_Cut_pic);
            this->addChild(temp, 5);
            temp->setPosition(tree->position);
            temp->setScale(3.1f);
        }


        it++;


    }

}

// 检查玩家是否接近背景的轮廓点
void  Forest::checkPlayerPosition()
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

        if (day % 3 == 1) {
            Weather = "Rainy";
        }
        else {
            Weather = "Sunny";
        }

        if ((Season == "Spring") && (day == 1)) {
            Festival = "Fishing Day";
        }
        else {
            Festival = "Noraml Day";
        }


        for (auto it = Crop_information.begin(); it != Crop_information.end();) {

            auto crop = *it;  // 解引用迭代器以访问 Crop 对象

            if (Weather == "Rainy") {
                crop->watered = true;
            }

            // 判断前一天是否浇水
            if ((crop->watered == false) && (crop->GetPhase() != Phase::MATURE)) {
                // 判断是否已经进入枯萎状态
                if (crop->GetPhase() != Phase::SAPLESS) {
                    crop->ChangePhase(Phase::SAPLESS);
                    crop->ChangMatureNeeded(2); // 延迟两天收获
                    it++;
                }
                else {
                    // 删除元素并更新迭代器
                    it = Crop_information.erase(it);
                }

            }
            else {
                // 更新状态
                crop->UpdateGrowth();
                it++;
            }

        }

        for (auto& pair : F_lastplace) {
            if (pair.first.first == "myhouse") {  // 检查 bool 值是否为 true
                pair.second = true;
            }
        }


        remainingTime = 0;
        player1->removeFromParent();
        auto nextday = Myhouse::create();
        Director::getInstance()->replaceScene(nextday);

    }

    // 更新标签位置
    float currentx = 0, currenty = 0;
    if (playerPos.x <= -600) {
        currentx = -600;
    }
    else if (playerPos.x >= 2197) {
        currentx = 2197;
    }
    else {
        currentx = playerPos.x;  
    }

    if (playerPos.y >= 2200) {
        currenty = 2200;
    }
    else if (playerPos.y <= -850) {
        currenty = -850;
    }
    else {
        currenty = playerPos.y;
    }

    TimeUI->setPosition(currentx, currenty);
    _positionLabel->setPosition(currentx - 570, currenty + 490);
    button->setPosition(currentx + 730, currenty - 590);
    miniBag->setPosition ( currentx , currenty );
    emitter->setPositionY(currenty + 350);

    if (isLKeyPressed) {

        isLKeyPressed = false;

        for (auto it = Tree_information.begin(); it != Tree_information.end(); ) {

            auto tree = *it;  

            float distance = tree->position.distance(playerPos);
            if (distance <= 250 && tree->available) {


                if (skill_tree->GetSkillLevels()[foraging_skill] >= 5) {
                    tree->removetimes -= 2;
                }
                else {
                    tree->removetimes -= 1;
                }

                if (tree->removetimes <= 0) {
                   
                    inventory->AddItem(Wood);

                    // 升级
                    skill_tree->AddExperience(foraging_skill, 10);


                    cocos2d::log("Cut Down");

                    tree->available = false;

                    tree->mining_day = season[Season] * 7 + day;


                    if (player1->pic_path == "character1/player_right3.png") {
                        player1->setTexture("character1/player_plant3.png");
                        player1->setScale(3.5f);

                        // 延迟0.3秒后切换到第二个图片
                        player1->scheduleOnce([=](float dt) {
                            player1->setTexture("character1/player_plant4.png");  // 更换为player_plant2
                            player1->setScale(3.7f);
                            }, 0.15f, "change_image1_key");

                        // 延迟0.6秒后切换到第三个图片
                        player1->scheduleOnce([=](float dt) {
                            player1->setTexture("character1/player_right3.png"); // 更换为player_left3
                            player1->setScale(2.3f);
                            auto temp = Sprite::create(tree->G_Cut_pic);
                            this->addChild(temp, 5);
                            temp->setPosition(tree->position);
                            temp->setScale(3.1f);
                            }, 0.35f, "change_image2_key");
                    }
                    else {
                        player1->setTexture("character1/player_plant1.png");
                        player1->setScale(3.5f);

                        // 延迟0.3秒后切换到第二个图片
                        player1->scheduleOnce([=](float dt) {
                            player1->setTexture("character1/player_plant2.png");  // 更换为player_plant2
                            player1->setScale(3.7f);
                            }, 0.15f, "change_image1_key");

                        // 延迟0.6秒后切换到第三个图片
                        player1->scheduleOnce([=](float dt) {
                            player1->setTexture("character1/player_left3.png"); // 更换为player_left3
                            player1->setScale(2.3f);
                            auto temp = Sprite::create(tree->G_Cut_pic);
                            this->addChild(temp, 5);
                            temp->setPosition(tree->position);
                            temp->setScale(3.1f);
                            }, 0.35f, "change_image2_key");
                    }
                }
                else {
                    if (player1->pic_path == "character1/player_right3.png") {
                        player1->setTexture("character1/player_plant3.png");
                        player1->setScale(3.5f);

                        // 延迟0.3秒后切换到第二个图片
                        player1->scheduleOnce([=](float dt) {
                            player1->setTexture("character1/player_plant4.png");  // 更换为player_plant2
                            player1->setScale(3.7f);
                            }, 0.15f, "change_image1_key");

                        // 延迟0.6秒后切换到第三个图片
                        player1->scheduleOnce([=](float dt) {
                            player1->setTexture("character1/player_right3.png"); // 更换为player_left3
                            player1->setScale(2.3f);
                            }, 0.35f, "change_image2_key");
                    }
                    else {
                        player1->setTexture("character1/player_plant1.png");
                        player1->setScale(3.5f);

                        // 延迟0.3秒后切换到第二个图片
                        player1->scheduleOnce([=](float dt) {
                            player1->setTexture("character1/player_plant2.png");  // 更换为player_plant2
                            player1->setScale(3.7f);
                            }, 0.15f, "change_image1_key");

                        // 延迟0.6秒后切换到第三个图片
                        player1->scheduleOnce([=](float dt) {
                            player1->setTexture("character1/player_left3.png"); // 更换为player_left3
                            player1->setScale(2.3f);
                            }, 0.35f, "change_image2_key");
                    }
                }
            }


            it++;

        }
    }

    // 是否前往农场
    if (farm_area.containsPoint(playerPos)) {
        if (isEnterKeyPressed) {
            for (auto& pair : W_lastplace) {
                if (pair.first.first == "farm") {  // 检查 bool 值是否为 true
                    pair.second = true;
                }
            }
            player1->removeFromParent();
            auto NextSence = farm::create();
            Director::getInstance()->replaceScene(NextSence);
        }
    }

    // 是否前往小镇
    if (town_area.containsPoint(playerPos)) {
        if (isEnterKeyPressed) {
            for (auto& pair : W_lastplace) {
                if (pair.first.first == "town") {  // 检查 bool 值是否为 true
                    pair.second = true;
                }
            }
            player1->removeFromParent();
            auto NextSence = Town::create();
            Director::getInstance()->replaceScene(NextSence);
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

int Forest::getRegionNumber(Vec2 pos) {

    int region_number = 1;

    return region_number;
}

void Forest::createRainEffect() {

    emitter = ParticleRain::create();
    emitter->setDuration(ParticleSystem::DURATION_INFINITY);
    emitter->setScale(5.7f);
    emitter->setTotalParticles(100);
    emitter->setSpeed(250);

    addChild(emitter, 10);

    // 每帧更新粒子生命周期
    schedule([this](float dt) {
        updaterain(dt);
        }, "update_rain_key");

}

void Forest::updaterain(float deltaTime) {
    if (emitter) {
        // 随机生成一个生命周期（范围 1 到 1.5 秒之间）
        float newLife = cocos2d::rand_0_1() * 1.5f;

        // 设置新的生命周期
        emitter->setLife(newLife);

        emitter->setEmissionRate(emitter->getTotalParticles() / emitter->getLife() * 1.3);
    }
}
