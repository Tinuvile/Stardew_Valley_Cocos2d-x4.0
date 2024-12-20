#include "AppDelegate.h"
#include "Myhouse.h"
#include "Barn.h"
#include "farm.h"
#include "Cave.h"
#include "Crop.h"
#include "Player.h"
#include "BasicInformation.h" 
#include "physics/CCPhysicsWorld.h"
#include "ui/CocosGUI.h"
#include "vector"
#include "mailBoxUI.h"

USING_NS_CC;

farm::farm () {}

farm::~farm () {}

bool farm::init ()
{

    auto test_milk = Food::create ( FoodType::Milk );
    inventory->AddItem ( *test_milk , 3 );
    inventory->DisplayPackageInCCLOG ();

    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    Vec2 origin = Director::getInstance ()->getVisibleOrigin ();

    button = cocos2d::Sprite::create ( "CloseNormal.png" );
    this->addChild ( button , 11 );

    // 设置计时器标签
    TimeUI = Timesystem::create ( "farm" );
    this->addChild ( TimeUI , 13 );

    // 恢复种植
    AllInitialize_crop ();

    if (Weather == "Rainy") {
        // 下雨
        createRainEffect ();
    }

    // 创建并初始化 Label 来显示角色的位置
    _positionLabel = Label::createWithTTF ( "Position: (0, 0)" , "fonts/Marker Felt.ttf" , 24 );
    if (_positionLabel)
    {
        this->addChild ( _positionLabel , 10 );
        _positionLabel->setScale ( 2.3f );
    }

    // 设置背景图片
    auto background_real = Sprite::create ( "farm/farm.png" );
    background_real->setPosition ( Vec2 ( visibleSize.width / 2 , visibleSize.height / 2 ) );
    this->addChild ( background_real , 1 );
    background_real->setScale ( 1.5f );

    auto background = Sprite::create ( "farm/farm_path.png" );
    this->addChild ( background , 5 );
    background->setPosition ( Vec2 ( visibleSize.width / 2 , visibleSize.height / 2 ) );
    background->setScale ( 1.5f );


    Vec2 spritePosition = background->getPosition ();   // 获取精灵的位置（中心点）
    Size spriteSize = background->getContentSize ();    // 获取精灵的尺寸（宽度和高度）


    // 计算左下角的坐标
    Vec2 leftBottomPosition = Vec2 (
        spritePosition.x - background->getScaleX () * spriteSize.width / 2 ,   // 中心点 x 坐标减去宽度的一半
        spritePosition.y - background->getScaleY () * spriteSize.height / 2   // 中心点 y 坐标减去高度的一半
    );


    Image img;
    if (img.initWithImageFile ( "farm/farm_path.png" ))
    {
        int width = img.getWidth ();
        int height = img.getHeight ();

        // 获取像素数据
        unsigned char* data = img.getData ();

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
                    float screenX = leftBottomPosition.x + x * background->getScaleX ();
                    float screenY = leftBottomPosition.y + (height - y - 1) * background->getScaleY ();  // 注意 Y 轴反向
                    nonTransparentPixels.push_back ( Vec2 ( screenX , screenY ) );  // 记录屏幕坐标
                }
            }
        }
    }

    // 初始化角色并将其添加到场景
    if (player1->getParent () == NULL) {
        this->addChild ( player1 , 17 );
        for (auto& pair : F_lastplace) {
            if (pair.second == true) {  // 检查 bool 值是否为 true
                player1->setPosition ( pair.first.second );
                pair.second = false;
            }
        }
        /* player1->speed = 3.5f;*/
         //仅为方便测试
        player1->speed = 20.0f;
        player1->setScale ( 1.5f );
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
    float scaledWidth = background->getContentSize ().width * background->getScaleX ();
    float scaledHeight = background->getContentSize ().height * background->getScaleY ();

    // 构造 Follow 的边界 Rect
    auto followRect = cocos2d::Rect ( leftBottomPosition.x , leftBottomPosition.y , scaledWidth , scaledHeight );

    // 创建 Follow 动作并限制玩家在背景范围内移动
    auto followAction = Follow::create ( player1 , followRect );
    this->runAction ( followAction );

    // 定期更新玩家状态
    this->schedule ( [this]( float dt ) {
        this->checkPlayerPosition ();  // 检查玩家是否接近轮廓点
        } , 0.01f , "check_position_key" );

    //信箱添加，用来领取任务
    auto mailBox = Sprite::create ( "UIresource/xinxiang/xinxiang.png" );
    mailBox->setPosition ( Vec2 ( 260 , 1050 ) );
    mailBox->setScale ( 0.7f );
    this->addChild ( mailBox , 10 );

    //箱子添加，用来卖东西
    Box = Sprite::create ( "UIresource/xiangzi/xiangzi.png" );
    Box->setPosition ( Vec2 ( 260 , 1150 ) );
    Box->setAnchorPoint ( Vec2 ( 0 , 0 ) );
    Box->setScale ( 0.7f );
    this->addChild ( Box , 10 );

    //交互距离
    float interactionRadius = 200.0f;

    auto listener = EventListenerMouse::create ();
    listener->onMouseDown = [this , mailBox , interactionRadius]( Event* event ) {

        // 获取鼠标点击的位置
        auto mouseEvent = static_cast<EventMouse*>(event);
        Vec2 clickPos ( mouseEvent->getCursorX () , mouseEvent->getCursorY () );
        clickPos = this->convertToNodeSpace ( clickPos );

        if (Box->getBoundingBox ().containsPoint ( clickPos )) {
            // 获取玩家的位置  
            Vec2 playerPos = player1->getPosition ();

            Vec2 BoxPos = Box->getPosition ();

            // 计算玩家与NPC之间的距离  
            float distance = playerPos.distance ( BoxPos );

            // 检查距离是否在允许的范围内  
            if (distance <= interactionRadius) {
                if (miniBag->getSelectedSlot ()) {
                    GoldAmount += inventory->GetItemAt ( miniBag->getSelectedSlot () )->GetValue ();
                    inventory->RemoveItem ( miniBag->getSelectedSlot () );
                    inventory->is_updated = true;
                    miniBag->getSelectBack ();
                }
            }
        }

        // 判断点击位置是否在信箱附近范围内
        if (button != nullptr && button->getBoundingBox ().containsPoint ( clickPos )) {
            Director::getInstance ()->end ();
        }
        if (mailBox->getBoundingBox ().containsPoint ( clickPos )) {
            // 获取玩家的位置  
            Vec2 playerPos = player1->getPosition ();

            // 计算玩家与信箱之间的距离  
            float distance = playerPos.distance ( mailBox->getPosition () );
            // 检查距离是否在允许的范围内  
            if (distance <= interactionRadius) {
                mailBoxUI* mailbox = mailBoxUI::create ();
                this->addChild ( mailbox , 20 );
            }
        }
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority ( listener , this );

    // 设置键盘监听器
    auto listenerWithPlayer = EventListenerKeyboard::create ();
    listenerWithPlayer->onKeyPressed = [this]( EventKeyboard::KeyCode keyCode , Event* event )
        {
            if (keyCode == EventKeyboard::KeyCode::KEY_ENTER || keyCode == EventKeyboard::KeyCode::KEY_KP_ENTER) {
                isEnterKeyPressed = true;
                CCLOG ( "Enter key pressed. " );
            }
            else if (keyCode == EventKeyboard::KeyCode::KEY_P) {
                isPKeyPressed = true;
            }
            else if (keyCode == EventKeyboard::KeyCode::KEY_W) {
                isWKeyPressed = true;
            }
            else if (keyCode == EventKeyboard::KeyCode::KEY_G) {
                isGKeyPressed = true;
            }
            else if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
                static int isOpen = 0;
                static InventoryUI* currentInventoryUI = nullptr;  // 保存当前显示的 InventoryUI  
                // 如果当前没有打开 InventoryUI，则打开它  
                if (currentInventoryUI == nullptr || isOpen == 0) {
                    isOpen = 1;
                    CCLOG ( "Opening inventory." );
                    currentInventoryUI = InventoryUI::create ( inventory , "farm" );
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

    listenerWithPlayer->onKeyReleased = [this]( EventKeyboard::KeyCode keyCode , Event* event )
        {
            // 释放 Enter 键时，设置为 false
            if (keyCode == EventKeyboard::KeyCode::KEY_ENTER || keyCode == EventKeyboard::KeyCode::KEY_KP_ENTER) {
                isEnterKeyPressed = false;
            }
            else if (keyCode == EventKeyboard::KeyCode::KEY_P) {
                isPKeyPressed = false;
            }
            else if (keyCode == EventKeyboard::KeyCode::KEY_W) {
                isWKeyPressed = false;
            }
            else if (keyCode == EventKeyboard::KeyCode::KEY_G) {
                isGKeyPressed = false;
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
        if (inventory->is_updated == true) {
            miniBag->updateDisplay ();
            inventory->is_updated = false;
        }
        } , 0.1f , "item_update_key" );

    return true;
}


farm* farm::create ()
{
    farm* scene = new farm ();
    if (scene && scene->init ())
    {
        scene->autorelease ();
        return scene;
    }
    CC_SAFE_DELETE ( scene );
    return nullptr;
}

void farm::AllInitialize_crop () {


    for (auto it = Crop_information.begin (); it != Crop_information.end (); /* no increment here */) {

        auto crop = *it;  // 解引用迭代器以访问 Crop 对象
        int nums = crop->nums;

        cocos2d::log ( "set nums = %d" , nums );

        // 获取类型
        std::string type = crop->GetName ();

        // 根据植物的状态选择显示的精灵
        if (crop->GetPhase () == Phase::MATURE) {
            auto test = Sprite::create ( crop->mature_pic );
            this->addChild ( test , 15 - nums / 19 );
            test->setPosition ( 545 + ((nums % 19) - 2) * 48 , 910 - ((nums / 19) - 1) * 48 );
            test->setScale ( 1.9f );
        }
        else if (crop->GetPhase () == Phase::GROWING) {
            auto test = Sprite::create ( crop->growing_pic );
            this->addChild ( test , 15 - nums / 19 );
            test->setPosition ( 545 + ((nums % 19) - 2) * 48 , 910 - ((nums / 19) - 1) * 48 );
            test->setScale ( 2.1f );
        }
        else if (crop->GetPhase () == Phase::SAPLESS) {
            auto test = Sprite::create ( "crop/sapless.png" );
            this->addChild ( test , 15 - nums / 19 );
            test->setPosition ( 545 + ((nums % 19) - 2) * 48 , 910 - ((nums / 19) - 1) * 48 );
            test->setScale ( 2.1f );
        }
        else {
            auto test = Sprite::create ( crop->initial_pic );
            this->addChild ( test , 15 - nums / 19 );
            test->setPosition ( 545 + ((nums % 19) - 2) * 48 , 910 - ((nums / 19) - 1) * 48 );
            test->setScale ( 2.1f );
        }

        // 遍历下一个元素
        ++it;
    }


}

// 检查玩家是否接近背景的轮廓点
void farm::checkPlayerPosition ()
{

    // 获取玩家的位置
    Vec2 playerPos = player1->getPosition ();

    // 计算玩家与箱子之间的距离  
    float distance = playerPos.distance ( Box->getPosition () );
    // 检查距离是否在允许的范围内  
    if (distance <= 200.0f) {
        Box->setTexture ( "UIresource/xiangzi/Open.png" );
    }
    else {
        Box->setTexture ( "UIresource/xiangzi/xiangzi.png" );
    }

    // 更新位置标签的内容
    if (_positionLabel)
    {
        _positionLabel->setString ( "Position: (" + std::to_string ( static_cast<int>(playerPos.x) ) + ", " + std::to_string ( static_cast<int>(playerPos.y) ) + ")" );

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


        for (auto it = Crop_information.begin (); it != Crop_information.end ();) {

            auto crop = *it;  // 解引用迭代器以访问 Crop 对象

            if (Weather == "Rainy") {
                crop->watered = true;
            }

            // 判断前一天是否浇水
            if ((crop->watered == false) && (crop->GetPhase () != Phase::MATURE)) {
                // 判断是否已经进入枯萎状态
                if (crop->GetPhase () != Phase::SAPLESS) {
                    crop->ChangePhase ( Phase::SAPLESS );
                    crop->ChangMatureNeeded ( 2 ); // 延迟两天收获
                    it++;
                }
                else {
                    // 删除元素并更新迭代器
                    it = Crop_information.erase ( it );
                }

            }
            else {
                // 更新状态
                crop->UpdateGrowth ();
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
        player1->removeFromParent ();
        auto nextday = Myhouse::create ();
        Director::getInstance ()->replaceScene ( nextday );

    }
    // 更新标签位置
    float currentx = 0 , currenty = 0;
    if (playerPos.x <= 637) {
        currentx = 637;
    }
    else if (playerPos.x >= 960) {
        currentx = 960;
    }
    else {
        currentx = playerPos.x;
    }

    if (playerPos.y >= 777) {
        currenty = 777;
    }
    else if (playerPos.y <= 500) {
        currenty = 500;
    }
    else {
        currenty = playerPos.y;
    }

    TimeUI->setPosition ( currentx , currenty );
    _positionLabel->setPosition ( currentx - 570 , currenty + 490 );
    button->setPosition ( currentx + 730 , currenty - 590 );
    miniBag->setPosition ( currentx , currenty );

    // 与种植有关的操作
    if (plant_area.containsPoint ( playerPos )) {

        // 是否执行种植
        if (isPKeyPressed) {

            int nums = getRegionNumber ( Vec2 ( playerPos.x + 10 , playerPos.y - 10 ) );

            bool Isplant = false;

            cocos2d::log ( "plant nums = %d" , nums );

            for (auto it = Crop_information.begin (); it != Crop_information.end (); /* no increment here */) {
                if ((*it)->nums == nums) {  // 使用 *it 解引用迭代器
                    Isplant = true;
                    break;
                }
                else {
                    ++it;
                }
            }

            if (Isplant == false) {

                auto temp = miniBag->getSelectedItem ();
                if (temp != nullptr) {
                    cocos2d::log ( "copy item" );
                    std::string TypeName = temp->GetName ();
                    auto point = cropbasicinformation.find ( TypeName );
                    if (point != cropbasicinformation.end ()) {
                        cocos2d::log ( "find crop" );
                        // 判断是否符合种植的季节
                        if (((cropbasicinformation[TypeName].GetSeason () == Season) || (cropbasicinformation[TypeName].GetSeason () == "All")) && strength >= 10) {
                            inventory->RemoveItem ( *temp );

                            strength -= 10;
                            TimeUI->energy_bar->setScaleY ( strength / 100.0 * 16.5f );

                            Crop_information.push_back ( cropbasicinformation[TypeName].GetCropCopy () );
                            Crop_information.back ()->plant_day = season[Season] * 7 + day;
                            Crop_information.back ()->nums = nums;

                            if (player1->pic_path == "character1/player_right3.png") {
                                // 初始设置：设置第一个图片并放大
                                player1->setTexture ( "character1/player_plant3.png" );
                                player1->setScale ( 2.5f );

                                // 延迟0.3秒后切换到第二个图片
                                player1->scheduleOnce ( [=]( float dt ) {
                                    player1->setTexture ( "character1/player_plant4.png" );  // 更换为player_plant2
                                    player1->setScale ( 2.7f );
                                    } , 0.15f , "change_image1_key" );

                                // 延迟0.6秒后切换到第三个图片
                                player1->scheduleOnce ( [=]( float dt ) {
                                    player1->setTexture ( "character1/player_right3.png" ); // 更换为player_left3
                                    player1->setScale ( 1.5f );
                                    auto temp = Sprite::create ( Crop_information.back ()->initial_pic );
                                    this->addChild ( temp , 15 - nums / 19 );
                                    temp->setPosition ( 500 + ((nums % 19) - 1) * 48 , 910 - ((nums / 19) - 1) * 48 );
                                    temp->setScale ( 2.1f );
                                    } , 0.35f , "change_image2_key" );
                            }
                            else {
                                // 初始设置：设置第一个图片并放大
                                player1->setTexture ( "character1/player_plant1.png" );
                                player1->setScale ( 2.5f );

                                // 延迟0.3秒后切换到第二个图片
                                player1->scheduleOnce ( [=]( float dt ) {
                                    player1->setTexture ( "character1/player_plant2.png" );  // 更换为player_plant2
                                    player1->setScale ( 2.7f );
                                    } , 0.15f , "change_image1_key" );

                                // 延迟0.6秒后切换到第三个图片
                                player1->scheduleOnce ( [=]( float dt ) {
                                    player1->setTexture ( "character1/player_left3.png" ); // 更换为player_left3
                                    player1->setScale ( 1.5f );
                                    auto temp = Sprite::create ( Crop_information.back ()->initial_pic );
                                    this->addChild ( temp , 15 - nums / 19 );
                                    temp->setPosition ( 500 + ((nums % 19) - 1) * 48 , 910 - ((nums / 19) - 1) * 48 );
                                    temp->setScale ( 2.1f );
                                    } , 0.35f , "change_image2_key" );
                            }

                        }
                    }
                }
            }
        }
        // 是否执行浇水
        else if (isWKeyPressed) {

            int nums = getRegionNumber ( Vec2 ( playerPos.x + 30 , playerPos.y - 10 ) );

            for (auto it : Crop_information) {
                if (it->nums == nums) {
                    // 改为已浇水
                    it->watered = true;

                    if (player1->pic_path == "character1/player_left3.png") {
                        // 初始设置：设置第一个图片并放大
                        player1->setTexture ( "character1/player_water4.png" );
                        player1->setScale ( 1.7f );

                        // 延迟0.3秒后切换到第二个图片
                        player1->scheduleOnce ( [=]( float dt ) {
                            player1->setTexture ( "character1/player_water3.png" );  // 更换为player_water1
                            player1->setScale ( 1.7f );
                            } , 0.15f , "change_image1_key" );

                        // 延迟0.6秒后切换到第三个图片
                        player1->scheduleOnce ( [=]( float dt ) {
                            player1->setTexture ( "character1/player_left3.png" ); // 更换为player_right3
                            player1->setScale ( 1.5f );
                            // 恢复角色其他的动作权限
                            player1->moveDown = true;
                            player1->moveLeft = true;
                            player1->moveUp = true;
                            player1->moveRight = true;
                            } , 0.35f , "change_image2_key" );

                    }
                    else {
                        // 初始设置：设置第一个图片并放大
                        player1->setTexture ( "character1/player_water2.png" );
                        player1->setScale ( 1.7f );

                        // 延迟0.3秒后切换到第二个图片
                        player1->scheduleOnce ( [=]( float dt ) {
                            player1->setTexture ( "character1/player_water1.png" );  // 更换为player_water1
                            player1->setScale ( 1.7f );
                            } , 0.15f , "change_image1_key" );

                        // 延迟0.6秒后切换到第三个图片
                        player1->scheduleOnce ( [=]( float dt ) {
                            player1->setTexture ( "character1/player_right3.png" ); // 更换为player_right3
                            player1->setScale ( 1.5f );
                            // 恢复角色其他的动作权限
                            player1->moveDown = true;
                            player1->moveLeft = true;
                            player1->moveUp = true;
                            player1->moveRight = true;
                            } , 0.35f , "change_image2_key" );
                    }

                }
            }

        }
        // 是否执行收获
        else if (isGKeyPressed) {

            int nums = getRegionNumber ( Vec2 ( playerPos.x + 10 , playerPos.y - 10 ) );


            for (auto it = Crop_information.begin (); it != Crop_information.end (); /* no increment here */) {
                if ((*it)->nums == nums) {  // 使用 *it 解引用迭代器
                    if ((*it)->GetPhase () == Phase::MATURE && strength >= 10) {

                        auto find_temp = (*it);

                        if (find_temp->GetName () == "potato") {
                            inventory->AddItem ( potato );
                        }

                        strength -= 10;
                        TimeUI->energy_bar->setScaleY ( strength / 100.0 * 16.5f );

                        // 覆盖精灵
                        auto test = Sprite::create ( "farm/tile.png" );
                        this->addChild ( test , 15 - nums / 19 );
                        test->setPosition ( 495 + ((nums % 19) - 1) * 48 , 910 - ((nums / 19) - 1) * 48 );
                        test->setScaleX ( 2.5f );
                        test->setScaleY ( 1.9f );

                        // 删除元素并更新迭代器
                        it = Crop_information.erase ( it );  // erase 返回新的迭代器 

                        // 初始设置：设置第一个图片并放大
                        player1->setTexture ( "character1/player_plant1.png" );
                        player1->setScale ( 2.5f );

                        // 延迟0.3秒后切换到第二个图片
                        player1->scheduleOnce ( [=]( float dt ) {
                            player1->setTexture ( "character1/player_plant2.png" );  // 更换为player_plant2
                            player1->setScale ( 2.7f );
                            } , 0.15f , "change_image1_key" );

                        // 延迟0.6秒后切换到第三个图片
                        player1->scheduleOnce ( [=]( float dt ) {
                            player1->setTexture ( "character1/player_left3.png" ); // 更换为player_left3
                            player1->setScale ( 1.5f );
                            } , 0.35f , "change_image2_key" );

                    }
                    else {
                        break;
                    }
                }
                else {
                    ++it;  // 继续遍历下一个元素
                }
            }

        }

    }

    // 是否进入玩家的家
    if (myhouse_area.containsPoint ( playerPos )) {
        if (isEnterKeyPressed) {
            for (auto& pair : F_lastplace) {
                if (pair.first.first == "myhouse") {
                    pair.second = true;
                }
            }
            player1->removeFromParent ();
            auto NextSence = Myhouse::create ();
            Director::getInstance ()->replaceScene ( NextSence );
        }
    }

    // 是否离开农场
    if (Out_Farm.containsPoint ( playerPos )) {
        if (isEnterKeyPressed) {

        }
    }

    // 是否进入畜棚
    if (barn_area.containsPoint ( playerPos )) {
        if (isEnterKeyPressed) {
            for (auto& pair : F_lastplace) {
                if (pair.first.first == "barn") {  // 检查 bool 值是否为 true
                    pair.second = true;
                }
            }
            player1->removeFromParent ();
            auto NextSence = Barn::create ();
            Director::getInstance ()->replaceScene ( NextSence );
        }
    }

    // 是否进入山洞
    if (cave_area.containsPoint ( playerPos )) {
        if (isEnterKeyPressed) {
            for (auto& pair : F_lastplace) {
                if (pair.first.first == "cave") {  // 检查 bool 值是否为 true
                    pair.second = true;
                }
            }
            player1->removeFromParent ();
            auto NextSence = Cave::create ();
            Director::getInstance ()->replaceScene ( NextSence );
        }
    }

    // 是否进入森林
    if (forest_area.containsPoint ( playerPos )) {
        if (isEnterKeyPressed) {
            for (auto& pair : F_lastplace) {
                if (pair.first.first == "forest") {  // 检查 bool 值是否为 true
                    pair.second = true;
                }
            }
            player1->removeFromParent ();
            auto NextSence = Forest::create ();
            Director::getInstance ()->replaceScene ( NextSence );
        }
    }

    for (const auto& point : nonTransparentPixels)
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

int farm::getRegionNumber ( Vec2 pos ) {

    // 定义矩形区域的参数
    int left_bottom_x = 496;  // 左下角x坐标
    int left_bottom_y = 467;  // 左下角y坐标
    int width = 912;          // 矩形宽度
    int height = 480;         // 矩形高度
    int block_size = 48;      // 每块的大小

    // 计算总的行数和列数
    int rows = height / block_size;  // 行数
    int cols = width / block_size;   // 列数

    // 计算给定坐标的列和行编号
    int col = (pos.x - left_bottom_x) / block_size;
    int row = (left_bottom_y + height - pos.y) / block_size;
    // 防止越界
    if (col < 0) {
        col = 0;
    }
    if (row < 0) {
        row = 0;
    }
    // 计算区域编号：先行后列
    int region_number = (row)*cols + col + 1;  // 编号从1开始

    return region_number;
}

void farm::createRainEffect () {

    emitter = ParticleRain::create ();
    emitter->setDuration ( ParticleSystem::DURATION_INFINITY );
    emitter->setScale ( 5.7f );
    emitter->setTotalParticles ( 100 );
    emitter->setSpeed ( 250 );

    addChild ( emitter , 10 );

    // 每帧更新粒子生命周期
    schedule ( [this]( float dt ) {
        updaterain ( dt );
        } , "update_rain_key" );

}


void farm::updaterain ( float deltaTime ) {
    if (emitter) {
        // 随机生成一个生命周期（范围 1 到 1.5 秒之间）
        float newLife = cocos2d::rand_0_1 () * 1.5f;

        // 设置新的生命周期
        emitter->setLife ( newLife );

        emitter->setEmissionRate ( emitter->getTotalParticles () / emitter->getLife () * 1.3 );
    }
}







