#include "AppDelegate.h"
#include "Barn.h"
#include "farm.h"
#include "Player.h"



Barn::Barn() {}

Barn::~Barn() {}

bool Barn::init ()
{
    //if (barn_space.size () < kMaxLivestock) {
     //    auto scene_size = Director::getInstance ()->getVisibleSize ();
     //    float rectWidth = scene_size.width / 14;
     //    float rectHeight = scene_size.height / 12;
     //    // 遍历每个矩形区域
     //    for (int row = 0; row < 12; ++row) {
     //        for (int col = 0; col < 14; ++col) {
     //            if ((row == 2 || row == 4 || row == 6) &&
     //                (col == 6 || col == 7 || col == 8 || col == 10)) {
     //                // 左下角坐标
     //                float x = col * rectWidth;
     //                float y = row * rectHeight;
     //                // 创建矩形并存储到 vector 中
     //                cocos2d::Rect rect ( x , y , rectWidth , rectHeight );
     //                CCLOG ( "%f,%f,%f,%f\n" ,x,y,rectWidth,rectHeight);
     //                barn_space.push_back ( std::make_pair ( rect , false ) );
     //                if (row == 6 && col == 10) {
     //                    break;
     //                }
     //            }
     //            else {
     //                continue;
     //            }
     //        }
     //    }
     //}

     //创建测试家畜
    /* for (int i = 0; i < 3; i++) {
         for (int j = 0; j < 4; j++) {
             Livestock* livestock;
             Rect area = barn_space[4 * i + j].first;
 @@ -61,7 +63,7 @@ bool Barn::init ()
             }
             livestocks.push_back ( livestock );
         }
     }
     }*/

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //button = cocos2d::Sprite::create("CloseNormal.png");
    //this->addChild(button, 11);

    // 设置计时器标签
    // 设置计时器标签
    auto temp_pos = player1->getPosition();
    TimeUI = Timesystem::create();
    this->addChild(TimeUI, 17);
    temp_pos.x += 90;
    temp_pos.y += 150;
    TimeUI->setPosition(temp_pos.x, temp_pos.y);

    // 创建并初始化 Label 来显示角色的位置
    _positionLabel = Label::createWithTTF("Position: (0, 0)", "fonts/Marker Felt.ttf", 24);
    if (_positionLabel) {
        this->addChild(_positionLabel, 10);
        _positionLabel->setScale(1.3f);
    }
    _positionLabel->setPosition(130, 1200);


    // 设置背景图片
    auto background_real = Sprite::create("Barn/Barn.png");
    background_real->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(background_real, 1);
    background_real->setScale(5.1f);

    auto background = Sprite::create("Barn/Barn_path.png");
    this->addChild(background, 5);
    background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    background->setScale(5.1f);


    Vec2 spritePosition = background->getPosition();   // 获取精灵的位置（中心点）
    Size spriteSize = background->getContentSize();    // 获取精灵的尺寸（宽度和高度）


    // 计算左下角的坐标
    Vec2 leftBottomPosition = Vec2(
        spritePosition.x - background->getScaleX() * spriteSize.width / 2,   // 中心点 x 坐标减去宽度的一半
        spritePosition.y - background->getScaleY() * spriteSize.height / 2   // 中心点 y 坐标减去高度的一半
    );


    Image img;
    if (img.initWithImageFile("Barn/Barn_path.png"))
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


    // 初始化角色并将其添加到场景
    if (player1->getParent() == NULL) {
        this->addChild(player1, 11);
        player1->setScale(2.7f);
        player1->setPosition(700, 450);
        player1->speed = 7.0f;
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

        //// 判断点击位置是否在精灵范围内
        //if (button != nullptr && button->getBoundingBox().containsPoint(clickPos)) {
        //    Director::getInstance()->end();
        //}
        };

    //_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, button);

    // 设置键盘监听器
    auto listenerWithPlayer = EventListenerKeyboard::create();
    listenerWithPlayer->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event)
        {
            if (keyCode == EventKeyboard::KeyCode::KEY_ENTER || keyCode == EventKeyboard::KeyCode::KEY_KP_ENTER) {
                isEnterKeyPressed = true;
                CCLOG("Enter key pressed. ");
            }
            else if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
                static int isOpen = 0;
                static InventoryUI* currentInventoryUI = nullptr;  // 保存当前显示的 InventoryUI  
                // 如果当前没有打开 InventoryUI，则打开它  
                if (currentInventoryUI == nullptr || isOpen == 0) {
                    isOpen = 1;
                    CCLOG ( "Opening inventory." );
                    currentInventoryUI = InventoryUI::create ( inventory , "Barn" );
                    this->addChild ( currentInventoryUI , 20 );  // 将 InventoryUI 添加到上层  
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
        };

    // 将监听器添加到事件分发器中
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerWithPlayer, this);

    // 设置鼠标监听器
    auto mouse_listener = cocos2d::EventListenerMouse::create ();

    // 鼠标点击事件的回调函数
    mouse_listener->onMouseDown = CC_CALLBACK_1 ( Barn::GetProduction , this );

    // 将监听器添加到事件分发器
    _eventDispatcher->addEventListenerWithSceneGraphPriority ( mouse_listener , this );

    //界面下的背包显示
    std::string scenename = "town";
    miniBag = mini_bag::create ( inventory);
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


Barn* Barn::create()
{
    Barn* scene = new Barn();
    if (scene && scene->init())
    {
        scene->autorelease();
        return scene;
    }
    CC_SAFE_DELETE(scene);
    return nullptr;
}


// 检查玩家是否接近背景的轮廓点
void Barn::checkPlayerPosition()
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

    // 是否进入农场
    if (Out_Barn.containsPoint(playerPos)) {
        if (isEnterKeyPressed) {
            player1->removeFromParent();
            auto NextSence = farm::create();
            Director::getInstance()->replaceScene(NextSence);
        }
    }


   
    if (Out_Barn.containsPoint(playerPos)) {
        if (isEnterKeyPressed) {
            player1->removeFromParent();
            auto NextSence = farm::create();
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
        else {
            if (player1->rightpressed == false) {
                player1->moveRight = true;
            }
        }

    }


}

void Barn::GetProduction ( cocos2d::EventMouse* event ) {
    // 判断是否是鼠标右键点击
    if (event->getMouseButton () == cocos2d::EventMouse::MouseButton::BUTTON_RIGHT)
    {
        // 获取鼠标点击位置
        cocos2d::Vec2 click_pos = this->convertToNodeSpace ( event->getLocationInView () );

        //遍历livestocks
        for (auto& livestock : livestocks) {
            if (livestock->IsCanProduce ()) {
                // 判断点击位置是否在 Sprite 内部
                if (livestock->getBoundingBox ().containsPoint ( click_pos )) {
                    CCLOG ( "Right-clicked on the produce_enabled livestock!" );
                    auto product = livestock->ProduceProduct ();
                    inventory->AddItem ( *product );
                    int experience_to_add = 10;
                    skill_tree->AddExperience ( farming_skill , experience_to_add );
                    inventory->DisplayPackageInCCLOG ();
                    //更新对应livestock的can_produce状态为false
                    livestock->SetCanProduce ( false );
                }
            }

        }
    }
}
