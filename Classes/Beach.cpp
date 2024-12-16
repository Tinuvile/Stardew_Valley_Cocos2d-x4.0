#include "AppDelegate.h"
#include "Beach.h"
#include "farm.h"
#include "Player.h"
#include "physics/CCPhysicsWorld.h"
#include "ui/CocosGUI.h"


USING_NS_CC;

Beach::Beach () {}

Beach::~Beach () {}

bool Beach::init ()
{
    //获取屏幕范围和坐标
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    Vec2 origin = Director::getInstance ()->getVisibleOrigin ();

    //创建退出按钮
    button = cocos2d::Sprite::create ( "CloseNormal.png" );
    this->addChild ( button , 11 );

    // 设置计时器标签
    _timerLabelD = Label::createWithTTF ( "Day: 0" , "fonts/Marker Felt.ttf" , 24 );
    this->addChild ( _timerLabelD , 10 );
    _timerLabelD->setScale ( 1.3f );
    _timerLabelD->setPosition ( Vec2 ( 50 , 1250 ) );

    _timerLabelH = Label::createWithTTF ( "0:00" , "fonts/Marker Felt.ttf" , 24 );
    this->addChild ( _timerLabelH , 10 );
    _timerLabelH->setScale ( 1.3f );
    _timerLabelH->setPosition ( Vec2 ( 130 , 1250 ) );

    _timerLabelS = Label::createWithTTF ( "Spring" , "fonts/Marker Felt.ttf" , 24 );
    this->addChild ( _timerLabelS , 10 );
    _timerLabelS->setScale ( 1.3f );
    _timerLabelS->setPosition ( Vec2 ( 210 , 1250 ) );

    // 创建并初始化 Label 来显示角色的位置
    _positionLabel = Label::createWithTTF ( "Position: (0, 0)" , "fonts/Marker Felt.ttf" , 24 );
    if (_positionLabel) {
        this->addChild ( _positionLabel , 10 );
        _positionLabel->setScale ( 1.3f );
    }
    _positionLabel->setPosition ( 130 , 1200 );


    // 设置背景图片
    auto background_real = Sprite::create ( "Beach/Beach.png" );
    background_real->setPosition ( Vec2 ( visibleSize.width / 2 , visibleSize.height / 2 ) );
    this->addChild ( background_real , 1 );
    background_real->setScale ( 2.3f );

    auto immovable_background = Sprite::create ( "Beach/Beach_path.png" );
    this->addChild ( immovable_background , 5 );
    immovable_background->setPosition ( Vec2 ( visibleSize.width / 2 , visibleSize.height / 2 ) );
    immovable_background->setScale ( 2.3f );


    Vec2 spritePosition = immovable_background->getPosition ();   // 获取精灵的位置（中心点）
    Size spriteSize = immovable_background->getContentSize ();    // 获取精灵的尺寸（宽度和高度）


    // 计算左下角的坐标
    Vec2 leftBottomPosition = Vec2 (
        spritePosition.x - immovable_background->getScaleX () * spriteSize.width / 2 ,   // 中心点 x 坐标减去宽度的一半
        spritePosition.y - immovable_background->getScaleY () * spriteSize.height / 2   // 中心点 y 坐标减去高度的一半
    );


    Image img;
    if (img.initWithImageFile ( "Beach/Beach_path.png" ))
    {
        int width = img.getWidth ();
        int height = img.getHeight ();

        // 获取像素数据
        unsigned char* data = img.getData ();

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
                    float screenX = leftBottomPosition.x + x * immovable_background->getScaleX ();
                    float screenY = leftBottomPosition.y + (height - y - 1) * immovable_background->getScaleY ();  // 注意 Y 轴反向
                    non_transparent_pixels.push_back ( Vec2 ( screenX , screenY ) );  // 记录屏幕坐标
                }
            }
        }
    }


    // 初始化角色并将其添加到场景
    if (player1->getParent () == NULL) {
        this->addChild ( player1 , 11 );
        player1->setScale ( 1.6f );
        player1->setPosition ( 320 ,1400 );
        player1->setAnchorPoint ( Vec2 ( 0.5f , 0.2f ) );


    }

    // 启动人物的定时器
    player1->schedule ( [=]( float dt ) {
        player1->player1_move ();
        } , 0.05f , "player1_move" );

    player1->schedule ( [=]( float dt ) {
        player1->player_change ();
        } , 0.3f , "player_change" );


    // 计算背景精灵的缩放后范围
    float scaledWidth = immovable_background->getContentSize ().width * immovable_background->getScaleX ();
    float scaledHeight = immovable_background->getContentSize ().height * immovable_background->getScaleY ();

    // 构造 Follow 的边界 Rect
    auto followRect = cocos2d::Rect ( leftBottomPosition.x , leftBottomPosition.y , scaledWidth , scaledHeight );

    // 创建 Follow 动作并限制玩家在背景范围内移动
    auto followAction = Follow::create ( player1 , followRect );
    this->runAction ( followAction );

    // 定期更新玩家状态
    this->schedule ( [this]( float dt ) {
        this->CheckPlayerPosition ();  // 检查玩家是否接近轮廓点
        } , 0.01f , "check_position_key" );

    auto listener = EventListenerMouse::create ();
    listener->onMouseDown = [this]( Event* event ) {

        // 获取鼠标点击的位置
        auto mouseEvent = static_cast<EventMouse*>(event);
        Vec2 clickPos ( mouseEvent->getCursorX () , mouseEvent->getCursorY () );
        clickPos = this->convertToNodeSpace ( clickPos );

        // 判断点击位置是否在精灵范围内
        if (button != nullptr && button->getBoundingBox ().containsPoint ( clickPos )) {
            Director::getInstance ()->end ();
        }
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority ( listener , button );

    // 设置键盘监听器
    auto listenerWithPlayer = EventListenerKeyboard::create ();
    listenerWithPlayer->onKeyPressed = [this]( EventKeyboard::KeyCode keyCode , Event* event )
        {
            if (keyCode == EventKeyboard::KeyCode::KEY_ENTER || keyCode == EventKeyboard::KeyCode::KEY_KP_ENTER) {
                isEnterKeyPressed = true;
                CCLOG ( "Enter key pressed. " );
            }
        };

    listenerWithPlayer->onKeyReleased = [this]( EventKeyboard::KeyCode keyCode , Event* event )
        {
            // 释放 Enter 键时，设置为 false
            if (keyCode == EventKeyboard::KeyCode::KEY_ENTER || keyCode == EventKeyboard::KeyCode::KEY_KP_ENTER) {
                isEnterKeyPressed = false;
            }
        };

    listenerWithPlayer->onKeyPressed = [this]( EventKeyboard::KeyCode key_code , Event* event ) {
        if (key_code == EventKeyboard::KeyCode::KEY_H) {

            if (!this->getChildByName ( "FishingGameLayer" )) {
                //将钓鱼游戏界面加入场景中
                auto fishing_game = FishingGame::create ( player1->getPosition () );
                this->addChild ( fishing_game , 10 , "FishingGameLayer" );
                ////暂停场景中其他节点的活动
                //player1->pause ();
                //this->pause ();
            }
        }
        else if (key_code == EventKeyboard::KeyCode::KEY_ESCAPE) {
            static int isOpen = 0;
            static InventoryUI* currentInventoryUI = nullptr;  // 保存当前显示的 InventoryUI  
            // 如果当前没有打开 InventoryUI，则打开它  
            if (currentInventoryUI == nullptr || isOpen == 0) {
                isOpen = 1;
                CCLOG ( "Opening inventory." );
                currentInventoryUI = InventoryUI::create ( inventory , "Beach" );
                this->addChild ( currentInventoryUI , 30 );  // 将 InventoryUI 添加到上层  
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

    // 将监听器添加到事件分发器中
    _eventDispatcher->addEventListenerWithSceneGraphPriority ( listenerWithPlayer , this );


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
        if (inventory->isupdated == true) {
            miniBag->updateDisplay ();
            inventory->isupdated = false;
        }
        } , 0.1f , "item_update_key" );

    return true;
}


Beach* Beach::create ()
{
    Beach* scene = new Beach ();
    if (scene && scene->init ())
    {
        scene->autorelease ();
        return scene;
    }
    CC_SAFE_DELETE ( scene );
    return nullptr;
}


// 检查玩家是否接近背景的轮廓点
void Beach::CheckPlayerPosition ()
{

    // 获取玩家的位置
    Vec2 playerPos = player1->getPosition ();

    // 更新位置标签的内容
    if (_positionLabel)
    {
        _positionLabel->setString ( "Position: (" + std::to_string ( static_cast<int>(playerPos.x) ) + ", " + std::to_string ( static_cast<int>(playerPos.y) ) + ")" );

    }

    // 更新计时器显示
    remainingTime++;
    _timerLabelD->setString ( "Day: " + std::to_string ( day ) );
    _timerLabelH->setString ( std::to_string ( remainingTime / 1800 ) + ":00" );
    _timerLabelS->setString ( Season );
    if (remainingTime == 432000) {

        day++;
        /*IsNextDay = true;*/

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

        remainingTime = 0;

        //for (auto it = Crop_information.begin(); it != Crop_information.end(); /* no increment here */) {

        //    auto crop = *it;  // 解引用迭代器以访问 Crop 对象

        //     判断前一天是否浇水
        //    if ((crop->watered == false) && (crop->GetPhase() != Phase::MATURE)) {
        //         判断是否已经进入枯萎状态
        //        if (crop->GetPhase() != Phase::SAPLESS) {
        //            crop->ChangePhase(Phase::SAPLESS);
        //            crop->ChangMatureNeeded(2); // 延迟两天收获
        //        }
        //        else {
        //             删除元素并更新迭代器
        //            it = Crop_information.erase(it);
        //        }
        //        ++it;
        //        continue;  // 跳过后续代码，直接继续循环
        //    }
        //    else {
        //         更新状态
        //        crop->UpdateGrowth();
        //    }

        //    it++;
        //}

        player1->removeFromParent ();
        auto nextday = farm::create ();
        Director::getInstance ()->replaceScene ( nextday );


    }

    // 更新标签位置
    float currentx = 0 , currenty = 0;
    if (playerPos.x <= -315) {
        currentx = -315;
    }
    else if (playerPos.x >= 20000) {
        currentx = 20000;
    }
    else {
        currentx = playerPos.x;
    }

    if (playerPos.y >= 920) {
        currenty = 920;
    }
    else if (playerPos.y <= 360) {
        currenty = 360;
    }
    else {
        currenty = playerPos.y;
    }

    _timerLabelD->setPosition ( currentx - 710 , currenty + 570 );
    _timerLabelH->setPosition ( currentx - 570 , currenty + 570 );
    _timerLabelS->setPosition ( currentx - 410 , currenty + 570 );
    _positionLabel->setPosition ( currentx - 570 , currenty + 490 );
    button->setPosition ( currentx + 730 , currenty - 590 );
    miniBag->setPosition ( currentx , currenty );


    // 是否进入农场
    if (Out_Beach.containsPoint ( playerPos )) {
        if (isEnterKeyPressed) {
            player1->removeFromParent ();
            auto NextSence = farm::create ();
            Director::getInstance ()->replaceScene ( NextSence );
        }
    }


    for (const auto& point : non_transparent_pixels)
    {
        // 计算玩家与轮廓点之间的距离
        float distance = 0;

        Vec2 temp;
        temp = playerPos;
        temp.x -= player1->speed;
        distance = temp.distance ( point );
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
        distance = temp.distance ( point );
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
        distance = temp.distance ( point );
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
        distance = temp.distance ( point );
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


