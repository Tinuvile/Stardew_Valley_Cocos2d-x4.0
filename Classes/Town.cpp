#include "AppDelegate.h"
#include "Town.h"
#include "Crop.h"
#include "Beach.h"
#include "supermarket.h"
#include "Player.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Town::Town() {}

Town::~Town() {}

bool Town::init()
{

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    button = cocos2d::Sprite::create("CloseNormal.png");
    this->addChild(button, 11);


    // 设置计时器标签
    TimeUI = Timesystem::create("Town");
    this->addChild(TimeUI, 13);


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
    auto background_real = Sprite::create("Town/Town.png");
    background_real->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(background_real, 1);
    background_real->setScale(1.7f);

    auto background_up = Sprite::create("Town/Town_up.png");
    background_up->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(background_up, 7);
    background_up->setScale(1.7f);

    auto background = Sprite::create("Town/Town_path.png");
    this->addChild(background, 5);
    background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    background->setScale(1.7f);


    Vec2 spritePosition = background->getPosition();   // 获取精灵的位置（中心点）
    Size spriteSize = background->getContentSize();    // 获取精灵的尺寸（宽度和高度）


    // 计算左下角的坐标
    Vec2 leftBottomPosition = Vec2(
        spritePosition.x - background->getScaleX() * spriteSize.width / 2,   // 中心点 x 坐标减去宽度的一半
        spritePosition.y - background->getScaleY() * spriteSize.height / 2   // 中心点 y 坐标减去高度的一半
    );


    Image img;
    if (img.initWithImageFile("Town/Town_path.png"))
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
                int index = (y * width + x) * 4;  // 每个像素占用 4 个字节 (RGBA)
                unsigned char a = data[index + 3];  // 透明度

                // 如果透明度 (alpha) 大于 0，表示此像素有内容
                if (a > 0)
                {
                    float screenX = leftBottomPosition.x + x * background->getScaleX();
                    float screenY = leftBottomPosition.y + (height - y - 1) * background->getScaleY();  // 注意 Y 轴反向
                    nonTransparentPixels.push_back(Vec2(screenX, screenY));  // 记录屏幕坐标
                }
            }
        }
    }


    // 初始化开门键
    opendoor = Sprite::create("opendoor.png");
    this->addChild(opendoor, 11);

    // 恢复玩家的状态
    if (player1)
    {
        for (auto& pair : T_lastplace) {
            if (pair.second == true) {  // 检查 bool 值是否为 true
                player1->setPosition(pair.first.second);
                pair.second = false;
            }
        }
        /*player1->speed = 3.7f;*/
        //仅为方便测试
        player1->speed = 20.0f;
    }

    //界面下的背包显示
    miniBag = mini_bag::create(inventory);
    miniBag->setScale(1.0f);
    Vec2 pos = miniBag->getPosition();
    if (miniBag != NULL) {
        cocos2d::log("miniBagtest %f", pos.x);
    }
    if (!this->getChildByName("mini_bag")) {
        this->addChild(miniBag, 10, "mini_bag");
    }


    // 更新物品栏
    schedule([=](float deltaTime) {
        if (inventory->is_updated == true) {
            miniBag->updateDisplay();
            inventory->is_updated = false;
        }
        }, 0.1f, "item_update_key");


    // 初始化角色并将其添加到场景
    if (player1->getParent() == NULL) {
        cocos2d::log("player1->get");
        this->addChild(player1, 6);
    }
    player1->setScale(1.5f);
    player1->setAnchorPoint(Vec2(0.5f, 0.2f));
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


    if ((Season == "Summer" && day == 3) || (Season == "Winter" && day == 3)) {}
    else {
        // 允许的交互半径  
        const float interactionRadius = 300.0f;


        // 使用 getAlexAnimations() 获取 NPC 动画帧  
        auto alexAnimations = getAlexAnimations(Season);
        // 创建 NPC 示例  
        auto alex = NPCreate::CreateNPC("Alex", cocos2d::Vec2(-550, 1450), alexAnimations, nonTransparentPixels);
        if (alex) {
            // CCLOG ( "NPC Alex created successfully." );  
            auto alexSprite = alex->GetSprite();
            if (alexSprite) {
                // CCLOG ( "Alex sprite created successfully at position: (%f, %f)" , alexSprite->getPositionX () , alexSprite->getPositionY () );  
                this->addChild(alexSprite, 5); // 确保添加到场景中  

                // 使用调度器每 1.0 秒调用 RandomMove  
                this->schedule([alex](float dt) {
                    alex->RandomMove();

                    // 获取 Alex 的当前位置  
                    auto alexSprite = alex->GetSprite(); // 获取精灵  
                    if (alexSprite) {
                        // 获取当前精灵的位置和大小  
                        Vec2 position = alexSprite->getPosition();
                        Size size = alexSprite->getContentSize();
                        // CCLOG ( "Alex's current position: (%f, %f)" , position.x , position.y ); // 打印位置  
                    }
                    }, 1.0f, "random_move_key_alex"); // 每 1.0 秒随机移动一次  
            }
            else {
                CCLOG("Alex sprite is nullptr.");
            }
        }
        else {
            CCLOG("Failed to create NPC Alex.");
        }

        // 使用 getElliottAnimations() 获取 NPC 动画帧  
        auto elliottAnimations = getElliottAnimations(Season);
        // 创建 NPC 示例  
        auto elliott = NPCreate::CreateNPC("Elliott", cocos2d::Vec2(1550, 600), elliottAnimations, nonTransparentPixels);
        if (elliott) {
            // CCLOG ( "NPC Elliott created successfully." );
            auto elliottSprite = elliott->GetSprite();
            if (elliottSprite) {
                // CCLOG ( "Elliott sprite created successfully at position: (%f, %f)" , elliottSprite->getPositionX () , elliottSprite->getPositionY () );
                this->addChild(elliottSprite, 5); // 确保添加到场景中  

                // 使用调度器每 1.0 秒调用 RandomMove  
                this->schedule([elliott](float dt) {
                    elliott->RandomMove();

                    // 获取 Elliott 的当前位置  
                    auto elliottSprite = elliott->GetSprite(); // 获取精灵  
                    if (elliottSprite) {
                        // 获取当前精灵的位置和大小  
                        Vec2 position = elliottSprite->getPosition();
                        Size size = elliottSprite->getContentSize();
                        // CCLOG ( "Elliott's current position: (%f, %f)" , position.x , position.y ); // 打印位置  
                    }
                    }, 1.0f, "random_move_key_elliott"); // 每 1.0 秒随机移动一次  
            }
            else {
                CCLOG("Elliott sprite is nullptr.");
            }
        }
        else {
            CCLOG("Failed to create NPC Elliott.");
        }

        // 使用 getCarolineAnimations() 获取 NPC 动画帧  
        auto carolineAnimations = getCarolineAnimations(Season);
        // 创建 NPC 示例  
        auto caroline = NPCreate::CreateNPC("Caroline", cocos2d::Vec2(700, 1400), carolineAnimations, nonTransparentPixels);
        if (caroline) {
            // CCLOG ( "NPC Caroline created successfully." );  
            auto carolineSprite = caroline->GetSprite();
            if (carolineSprite) {
                // CCLOG ( "Caroline sprite created successfully at position: (%f, %f)" , carolineSprite->getPositionX () , carolineSprite->getPositionY () );  
                this->addChild(carolineSprite, 5); // 确保添加到场景中  

                // 使用调度器每 1.0 秒调用 RandomMove  
                this->schedule([caroline](float dt) {
                    caroline->RandomMove();

                    // 获取 Caroline 的当前位置  
                    auto carolineSprite = caroline->GetSprite(); // 获取精灵  
                    if (carolineSprite) {
                        // 获取当前精灵的位置和大小  
                        Vec2 position = carolineSprite->getPosition();
                        Size size = carolineSprite->getContentSize();
                        // CCLOG ( "Caroline's current position: (%f, %f)" , position.x , position.y ); // 打印位置  
                    }
                    }, 1.0f, "random_move_key_caroline"); // 每 1.0 秒随机移动一次  
            }
            else {
                CCLOG("Caroline sprite is nullptr.");
            }
        }
        else {
            CCLOG("Failed to create NPC Caroline.");
        }

        // 使用 getAbigailAnimations() 获取 NPC 动画帧  
        auto abigailAnimations = getAbigailAnimations(Season);
        // 创建 NPC 示例  
        auto abigail = NPCreate::CreateNPC("Abigail", cocos2d::Vec2(60, 100), abigailAnimations, nonTransparentPixels);
        if (abigail) {
            // CCLOG ( "NPC Abigail created successfully." );  
            auto abigailSprite = abigail->GetSprite();
            if (abigailSprite) {
                // CCLOG ( "Abigail sprite created successfully at position: (%f, %f)" , abigailSprite->getPositionX () , abigailSprite->getPositionY () );  
                this->addChild(abigailSprite, 5); // 确保添加到场景中  

                // 使用调度器每 1.0 秒调用 RandomMove  
                this->schedule([abigail](float dt) {
                    abigail->RandomMove();

                    // 获取 Abigail 的当前位置  
                    auto abigailSprite = abigail->GetSprite(); // 获取精灵  
                    if (abigailSprite) {
                        // 获取当前精灵的位置和大小  
                        Vec2 position = abigailSprite->getPosition();
                        Size size = abigailSprite->getContentSize();
                        // CCLOG ( "Abigail's current position: (%f, %f)" , position.x , position.y ); // 打印位置  
                    }
                    }, 1.0f, "random_move_key_abigail"); // 每 1.0 秒随机移动一次  
            }
            else {
                CCLOG("Abigail sprite is nullptr.");
            }
        }
        else {
            CCLOG("Failed to create NPC Abigail.");
        }

        // 使用 getEmilyAnimations() 获取 NPC 动画帧  
        auto emilyAnimations = getEmilyAnimations(Season);
        // 创建 NPC 示例  
        auto emily = NPCreate::CreateNPC("Emily", cocos2d::Vec2(180, 1550), emilyAnimations, nonTransparentPixels);
        if (emily) {
            // CCLOG ( "NPC Emily created successfully." );  
            auto emilySprite = emily->GetSprite();
            if (emilySprite) {
                // CCLOG ( "Emily sprite created successfully at position: (%f, %f)" , emilySprite->getPositionX () , emilySprite->getPositionY () );  
                this->addChild(emilySprite, 5); // 确保添加到场景中  

                // 使用调度器每 1.0 秒调用 RandomMove  
                this->schedule([emily](float dt) {
                    emily->RandomMove();

                    // 获取 Emily 的当前位置  
                    auto emilySprite = emily->GetSprite(); // 获取精灵  
                    if (emilySprite) {
                        // 获取当前精灵的位置和大小  
                        Vec2 position = emilySprite->getPosition();
                        Size size = emilySprite->getContentSize();
                        // CCLOG ( "Emily's current position: (%f, %f)" , position.x , position.y ); // 打印位置  
                    }
                    }, 1.0f, "random_move_key_emily"); // 每 1.0 秒随机移动一次  
            }
            else {
                CCLOG("Emily sprite is nullptr.");
            }
        }
        else {
            CCLOG("Failed to create NPC Abigail.");
        }


        // 鼠标事件监听器
        auto listener = EventListenerMouse::create();
        listener->onMouseDown = [this, abigail, alex, caroline, elliott, emily, interactionRadius](Event* event) {

            // 获取鼠标点击的位置  
            auto mouseEvent = static_cast<EventMouse*>(event);
            Vec2 clickPos(mouseEvent->getCursorX(), mouseEvent->getCursorY());
            clickPos = this->convertToNodeSpace(clickPos);

            // 检查是否点击了NPC并打开对话框  
            std::vector<std::pair<NPC*, std::string>> npcs = {
                {abigail, "Abigail"},
                {alex, "Alex"},
                {caroline, "Caroline"},
                {elliott, "Elliott"},
                {emily, "Emily"}
            };

            for (auto& npcPair : npcs) {
                NPC* npc = npcPair.first;
                const std::string& npcName = npcPair.second;

                if (npc) {
                    auto npcSprite = npc->GetSprite();
                    if (npcSprite && npcSprite->getBoundingBox().containsPoint(clickPos)) {
                        // 获取玩家的位置  
                        Vec2 playerPos = player1->getPosition();

                        // 计算玩家与NPC之间的距离  
                        float distance = playerPos.distance(npcSprite->getPosition());

                        // 检查距离是否在允许的范围内  
                        if (distance <= interactionRadius) {
                            if (!miniBag->getSelectedSlot() || npc_relationship->NpcGiftTIme(npc->GetName()) == 2) {
                                // 打开对话框，确保对话框每次都是新的实例  
                                NPCtalkUI* currentNPCtalkUI = NPCtalkUI::create(npc, "Town");
                                this->addChild(currentNPCtalkUI, 12); // 将当前NPC对话框添加到场景中  
                                return; // 处理完一个NPC后直接返回  
                            }
                            else if (miniBag->getSelectedSlot()) {
                                Vec2 playerPos = player1->getPosition();
                                npc_relationship->increaseRelationship("player", npc->GetName(), 15.2);
                                inventory->RemoveItem(miniBag->getSelectedSlot());
                                inventory->is_updated = true;
                                npc_relationship->AddGiftTime(npc->GetName());
                                // 这里改成礼物的图
                                auto ItemClickByminiBag = Sprite::create("npc/gift.png");
                                ItemClickByminiBag->setPosition(playerPos);
                                this->addChild(ItemClickByminiBag, 6);
                                // 一个延迟，2秒后移除 ItemClickByminiBag  
                                this->runAction(Sequence::create(
                                    DelayTime::create(1.5f), // 等待2秒  
                                    CallFunc::create([=]() {
                                        this->removeChild(ItemClickByminiBag); // 移除 ItemClickByminiBag  
                                        }),
                                    nullptr
                                ));
                                miniBag->getSelectBack();
                            }
                        }
                        else {
                            CCLOG("Player is too far from %s to interact.", npcName.c_str());
                        }
                    }
                }
            }
            };

        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, button);
    }



    // 设置键盘监听器
    auto listenerWithPlayer = EventListenerKeyboard::create();
    listenerWithPlayer->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event)
        {
            // 记录 Enter 键被按下
            if (keyCode == EventKeyboard::KeyCode::KEY_ENTER || keyCode == EventKeyboard::KeyCode::KEY_KP_ENTER) {
                isEnterKeyPressed = true;

                CCLOG("Enter key pressed. ");
            }
            else if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
                CCLOG("%d", GoldAmount);
                static int isOpen = 0;
                static InventoryUI* currentInventoryUI = nullptr;  // 保存当前显示的 InventoryUI  
                // 如果当前没有打开 InventoryUI，则打开它  
                if (currentInventoryUI == nullptr || isOpen == 0) {
                    isOpen = 1;
                    CCLOG("Opening inventory.");
                    currentInventoryUI = InventoryUI::create(inventory, "Town");
                    this->addChild(currentInventoryUI, 20);  // 将 InventoryUI 添加到 Town 的上层  
                }
                // 如果已经打开 InventoryUI，则关闭它  
                else {
                    isOpen = 0;
                    CCLOG("Closing inventory.");
                    this->removeChild(currentInventoryUI, true);  // 从当前场景中移除 InventoryUI  
                    currentInventoryUI = nullptr;  // 重置指针  
                }
            }

        };

    listenerWithPlayer->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event* event)
        {
            // 释放 Enter 键时，设置为 false
            if (keyCode == EventKeyboard::KeyCode::KEY_KP_ENTER || keyCode == EventKeyboard::KeyCode::KEY_KP_ENTER) {
                isEnterKeyPressed = false;
                CCLOG("Enter key released. ");
            }
        };

    // 将监听器添加到事件分发器中
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerWithPlayer, this);

    return true;
}


Town* Town::create()
{
    Town* scene = new Town();
    if (scene && scene->init())
    {
        scene->autorelease();
        return scene;
    }
    CC_SAFE_DELETE(scene);
    return nullptr;
}

// 检查玩家是否接近背景的轮廓点
void Town::checkPlayerPosition()
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

        IsSleep = false;
        frombed = true;
        remainingTime = 10800;
        player1->removeFromParent();
        auto nextday = Myhouse::create();
        Director::getInstance()->replaceScene(nextday);

    }

    // 更新标签位置
    float currentx = 0, currenty = 0;
    if (playerPos.x <= -170) {
        currentx = -170;
    }
    else if (playerPos.x >= 1773) {
        currentx = 1773;
    }
    else {
        currentx = playerPos.x;
    }

    if (playerPos.y >= 1498) {
        currenty = 1498;
    }
    else if (playerPos.y <= -222) {
        currenty = -222;
    }
    else {
        currenty = playerPos.y;
    }

    TimeUI->setPosition(currentx, currenty);
    _positionLabel->setPosition(currentx - 570, currenty + 490);
    button->setPosition(currentx + 730, currenty - 590);
    miniBag->setPosition (currentx, currenty);
    emitter->setPositionY(currenty + 350);
   
    // 检查玩家是否进入目标区域，并且按下 Enter 键
    if (Region_supermarket.containsPoint(playerPos)) {
        // 玩家进入目标区域
        opendoor->setVisible(true);
        opendoor->setPosition(playerPos.x + 110, playerPos.y + 30);
        CCLOG("Player in target area");

        if (isEnterKeyPressed) {
            for (auto& pair : T_lastplace) {
                if (pair.first.first == "seedshop") {  // 检查 bool 值是否为 true
                    pair.second = true;
                }
            }
            // 打印调试信息，检查 Enter 键的状态
            CCLOG("Player in target area, isEnterKeyPressed: %d", isEnterKeyPressed);
            // 调用场景切换逻辑
            player1->removeFromParent();
            
            auto seedshop = supermarket::create();
            // miniBag->removeFromParent();
            Director::getInstance()->replaceScene(seedshop);
        }

    }
    else {
        opendoor->setVisible(false);
    }    
    
    if (Region_forest.containsPoint(playerPos)) {
        if (isEnterKeyPressed) {
            for (auto& pair : T_lastplace) {
                if (pair.first.first == "forest") {  
                    pair.second = true;
                }
            }
            // 调用场景切换逻辑
            player1->removeFromParent();
            auto nextscene = Forest::create();
            Director::getInstance()->replaceScene(nextscene);
        }

    }

    if (Region_beach.containsPoint(playerPos)) {
        if (isEnterKeyPressed) {
            for (auto& pair : T_lastplace) {
                if (pair.first.first == "beach") {
                    pair.second = true;
                }
            }
            // 调用场景切换逻辑
            player1->removeFromParent();
            auto nextscene = Beach::create();
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

void Town::createRainEffect() {

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



void Town::updaterain(float deltaTime) {
    if (emitter) {
        // 随机生成一个生命周期（范围 1 到 1.5 秒之间）
        float newLife = cocos2d::rand_0_1() * 1.5f;

        // 设置新的生命周期
        emitter->setLife(newLife);

        emitter->setEmissionRate(emitter->getTotalParticles() / emitter->getLife() * 1.3);
    }
}


