#include "AppDelegate.h"
#include "Town.h"
#include "Player.h"
#include "physics/CCPhysicsWorld.h"

USING_NS_CC;

extern int remainingTime;

myhouse::myhouse() {}

myhouse::~myhouse() {}

bool myhouse::init()
{
    if (!Scene::init())
    {
        return false;
    }

   
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
   
 

    // 创建退出按钮（"X" 图标），点击时退出游戏
    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",  // 普通状态下的图片
        "CloseSelected.png",  // 被选中状态下的图片
        CC_CALLBACK_1(myhouse::menuCloseCallback, this));  // 点击按钮时调用 menuCloseCallback 方法


    // 设置按钮位置，使其位于屏幕右上角
    float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
    float y = origin.y + closeItem->getContentSize().height / 2;
    closeItem->setPosition(Vec2(x, y));  // 设置按钮的位置



    // 创建菜单，将按钮添加到菜单中，并设置菜单的位置
    auto menu = Menu::create(closeItem, NULL);  // 创建菜单并添加按钮
    menu->setPosition(Vec2::ZERO);  // 设置菜单的位置为（0，0），即左下角
    this->addChild(menu, 10);  // 将菜单添加到当前场景中



    // 创建并初始化 Label 来显示角色的位置
    _positionLabel = Label::createWithTTF("Position: (0, 0)", "fonts/Marker Felt.ttf", 24);
    if (_positionLabel)
    {
        _positionLabel->setPosition(Vec2(origin.x + 150, origin.y + visibleSize.height - 50));  // 设置位置
        this->addChild(_positionLabel, 10);  
        _positionLabel->setScale(0.7f);
    }

    // 设置计时器标签
    _timerLabel = Label::createWithTTF("Timer: 60", "fonts/Marker Felt.ttf", 24);
    _timerLabel->setPosition(Vec2(origin.x + 150, origin.y + visibleSize.height - 90));
    this->addChild(_timerLabel, 10);

    // 设置任务领取处的标签
    In_gettask = Sprite::create("opendoor.png");
    this->addChild(In_gettask, 10);
    In_gettask->setScale(0.5f);
    In_gettask->setVisible(false);


    // 设置背景图片
    auto background_real = Sprite::create("Town/Town.png");  
    background_real->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(background_real,1);
    background_real->setScale(0.7f);

    auto background_up = Sprite::create("Town/Town_up.png");  
    background_up->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(background_up, 7);
    background_up->setScale(0.7f);
 
    auto background = Sprite::create("Town/Town_path.png");
    this->addChild(background, 5);
    background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    background->setScale(0.7f);
   

    Vec2 spritePosition = background->getPosition();   // 获取精灵的位置（中心点）
    CCLOG("spritePosition: (%f, %f)", spritePosition.x, spritePosition.y);
    Size spriteSize = background->getContentSize();    // 获取精灵的尺寸（宽度和高度）
    CCLOG("spriteSize: (%f, %f)", spriteSize.width, spriteSize.height);

    // 计算左下角的坐标
    Vec2 leftBottomPosition = Vec2(
        spritePosition.x - 0.7 * spriteSize.width / 2,   // 中心点 x 坐标减去宽度的一半
        spritePosition.y - 0.7 * spriteSize.height / 2   // 中心点 y 坐标减去高度的一半
    );
    CCLOG("leftBottomPosition: (%f, %f)", leftBottomPosition.x, leftBottomPosition.y);

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
                    float screenX = leftBottomPosition.x + x * 0.7;
                    float screenY = leftBottomPosition.y + (height - y - 1) * 0.7;  // 注意 Y 轴反向
                    CCLOG("Non-transparent pixel at: (%f, %f)", screenX, screenY);
                    nonTransparentPixels.push_back(Vec2(screenX, screenY));  // 记录屏幕坐标
                }
            }
        }
    }


    // 初始化角色并将其添加到场景
    auto player1 = Player::create();
    this->addChild(player1,5);
    player1->setPosition(Vec2(visibleSize.width / 2 + 43, visibleSize.height / 2 - 72));  // 设置玩家初始位置
    player1->setScale(0.7f);
    player1->setAnchorPoint(Vec2(0.5f, 0.2f));

    // 定期更新玩家状态
    schedule([this, player1](float dt) {
        this->checkPlayerPosition(player1);  // 检查玩家是否接近轮廓点
        }, 0.01f, "check_position_key");


    return true;
}

myhouse* myhouse::create()
{
    myhouse* scene = new myhouse();
    if (scene && scene->init())
    {
        scene->autorelease();
        return scene;
    }
    CC_SAFE_DELETE(scene);
    return nullptr;
}

// 检查玩家是否接近背景的轮廓点
void myhouse::checkPlayerPosition(Player* player)
{
    // 获取玩家的位置
    Vec2 playerPos = player->getPosition();
    
    // 更新位置标签的内容
    if (_positionLabel)
    {
        _positionLabel->setString("Position: (" + std::to_string(static_cast<int>(playerPos.x)) + ", " + std::to_string(static_cast<int>(playerPos.y)) + ")");
    }

    // 减少剩余时间
    remainingTime--;

    // 更新计时器显示
    _timerLabel->setString("Timer: " + std::to_string(remainingTime / 60));


    if (Get_Task.containsPoint(playerPos)) {
        In_gettask->setPosition(Vec2(playerPos.x + 35, playerPos.y + 10));
        In_gettask->setVisible(true);
    }
    else {
        In_gettask->setVisible(false);
    }


    // 遍历所有轮廓点，检查玩家是否接近某个轮廓点
    for (const auto& point : nonTransparentPixels)
    {
        // 计算玩家与轮廓点之间的距离
        float distance = 0;

        Vec2 temp = playerPos;
        temp.x -= player->speed;
        distance = temp.distance(point);
        if (distance <= 5) {
            player->moveLeft = true;
            CCLOG("Player is near the boundary! Moving is stopped.");
        }

        temp = playerPos;
        temp.y -= player->speed;
        distance = temp.distance(point);
        if (distance <= 5) {
            player->moveDown = true;
            CCLOG("Player is near the boundary! Moving is stopped.");
        }

        temp = playerPos;
        temp.y += player->speed;
        distance = temp.distance(point);
        if (distance <= 5) {
            player->moveUp = true;
            CCLOG("Player is near the boundary! Moving is stopped.");
        }

        temp = playerPos;
        temp.x += player->speed;
        distance = temp.distance(point);
        if (distance <= 5) {
            player->moveRight = true;
            CCLOG("Player is near the boundary! Moving is stopped.");
        }
       
    }
}







// 退出按钮的回调函数
void myhouse::menuCloseCallback(Ref* pSender)
{
    // 退出程序，结束当前游戏场景
    Director::getInstance()->end();

    /* 如果不希望退出整个应用，而是仅关闭当前场景，可以考虑使用以下代码：
       此部分代码用于在 iOS 上返回到原生屏幕，避免直接退出应用：

       EventCustom customEndEvent("game_scene_close_event");
       _eventDispatcher->dispatchEvent(&customEndEvent);
    */
}




