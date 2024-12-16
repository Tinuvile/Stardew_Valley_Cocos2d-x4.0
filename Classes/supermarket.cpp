#include "AppDelegate.h"
#include "supermarket.h"
#include "Town.h"
#include "Player.h"
#include "physics/CCPhysicsWorld.h"
#include "ui/CocosGUI.h"
#include "StoreUI.h"

USING_NS_CC;

extern int remainingTime;
extern Player* player1;
extern Town* town;
extern supermarket* seedshop;
extern Inventory* inventory;

supermarket::supermarket() {}

supermarket::~supermarket() {}

bool supermarket::init()
{
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    button = cocos2d::Sprite::create("CloseNormal.png");
    this->addChild(button, 11);

    StoreItem = new Inventory ();

    // 动物  
    StoreItem->AddItem ( Golden_Chicken );
    StoreItem->SetSelectedItem ( 1 );

    StoreItem->AddItem ( Duck );
    StoreItem->SetSelectedItem ( 2 );

    StoreItem->AddItem ( Goat );
    StoreItem->SetSelectedItem ( 3 );

    StoreItem->AddItem ( Pig );
    StoreItem->SetSelectedItem ( 4 );

    StoreItem->AddItem ( Rabbit );
    StoreItem->SetSelectedItem ( 5 );

    StoreItem->AddItem ( Sheep );
    StoreItem->SetSelectedItem ( 6 );

    StoreItem->AddItem ( White_Chicken );
    StoreItem->SetSelectedItem ( 7 );

    // 春季种子物品列表  
    StoreItem->AddItem ( Bean_Starter );
    StoreItem->SetSelectedItem ( 8 );

    StoreItem->AddItem ( Carrot_Seeds );
    StoreItem->SetSelectedItem ( 9 );

    StoreItem->AddItem ( Cauliflower_Seeds );
    StoreItem->SetSelectedItem ( 10 );

    StoreItem->AddItem ( Coffee_Bean );
    StoreItem->SetSelectedItem ( 11 );

    StoreItem->AddItem ( Garlic_Seeds );
    StoreItem->SetSelectedItem ( 12 );

    StoreItem->AddItem ( Jazz_Seeds );
    StoreItem->SetSelectedItem ( 13 );

    StoreItem->AddItem ( Kale_Seeds );
    StoreItem->SetSelectedItem ( 14 );

    StoreItem->AddItem ( Parsnip_Seeds );
    StoreItem->SetSelectedItem ( 15 );

    StoreItem->AddItem ( Potato_Seeds );
    StoreItem->SetSelectedItem ( 16 );

    StoreItem->AddItem ( Rhubarb_Seeds );
    StoreItem->SetSelectedItem ( 17 );

    StoreItem->AddItem ( Rice_Shoot );
    StoreItem->SetSelectedItem ( 18 );

    StoreItem->AddItem ( Strawberry_Seeds );
    StoreItem->SetSelectedItem ( 19 );

    StoreItem->AddItem ( Tulip_Bulb );
    StoreItem->SetSelectedItem ( 20 );

    // 夏季种子物品列表  
    StoreItem->AddItem ( Amaranth_Seeds );
    StoreItem->SetSelectedItem ( 21 );

    StoreItem->AddItem ( Artichoke_Seeds );
    StoreItem->SetSelectedItem ( 22 );

    StoreItem->AddItem ( Beet_Seeds );
    StoreItem->SetSelectedItem ( 23 );

    StoreItem->AddItem ( Blueberry_Seeds );
    StoreItem->SetSelectedItem ( 24 );

    StoreItem->AddItem ( Bok_Choy_Seeds );
    StoreItem->SetSelectedItem ( 25 );

    StoreItem->AddItem ( Broccoli_Seeds );
    StoreItem->SetSelectedItem ( 26 );

    StoreItem->AddItem ( Corn_Seeds );
    StoreItem->SetSelectedItem ( 27 );

    StoreItem->AddItem ( Cranberry_Seeds );
    StoreItem->SetSelectedItem ( 28 );

    StoreItem->AddItem ( Eggplant_Seeds );
    StoreItem->SetSelectedItem ( 29 );

    StoreItem->AddItem ( Fairy_Seeds );
    StoreItem->SetSelectedItem ( 30 );

    StoreItem->AddItem ( Grape_Starter );
    StoreItem->SetSelectedItem ( 31 );

    StoreItem->AddItem ( Hops_Starter );
    StoreItem->SetSelectedItem ( 32 );

    StoreItem->AddItem ( Melon_Seeds );
    StoreItem->SetSelectedItem ( 33 );

    StoreItem->AddItem ( Pepper_Seeds );
    StoreItem->SetSelectedItem ( 34 );

    StoreItem->AddItem ( Poppy_Seeds );
    StoreItem->SetSelectedItem ( 35 );

    StoreItem->AddItem ( Pumpkin_Seeds );
    StoreItem->SetSelectedItem ( 36 );

    StoreItem->AddItem ( Radish_Seeds );
    StoreItem->SetSelectedItem ( 37 );

    StoreItem->AddItem ( Red_Cabbage_Seeds );
    StoreItem->SetSelectedItem ( 38 );

    StoreItem->AddItem ( Spangle_Seeds );
    StoreItem->SetSelectedItem ( 39 );

    StoreItem->AddItem ( Starfruit_Seeds );
    StoreItem->SetSelectedItem ( 40 );

    StoreItem->AddItem ( Summer_Squash_Seeds );
    StoreItem->SetSelectedItem ( 41 );

    StoreItem->AddItem ( Sunflower_Seeds );
    StoreItem->SetSelectedItem ( 42 );

    StoreItem->AddItem ( Tomato_Seeds );
    StoreItem->SetSelectedItem ( 43 );

    StoreItem->AddItem ( Wheat_Seeds );
    StoreItem->SetSelectedItem ( 44 );

    StoreItem->AddItem ( Yam_Seeds );
    StoreItem->SetSelectedItem ( 45 );

    // 冬季种子物品列表  
    StoreItem->AddItem ( Powdermelon_Seeds );
    StoreItem->SetSelectedItem ( 46 );

    // 工具列表  
    StoreItem->AddItem ( Backpack_36 );
    StoreItem->SetSelectedItem ( 47 );

    StoreItem->AddItem ( Backpack );
    StoreItem->SetSelectedItem ( 48 );

    StoreItem->AddItem ( Advanced_Iridium_Rod );
    StoreItem->SetSelectedItem ( 49 );

    StoreItem->AddItem ( Axe );
    StoreItem->SetSelectedItem ( 50 );

    StoreItem->AddItem ( Bamboo_Pole );
    StoreItem->SetSelectedItem ( 51 );

    StoreItem->AddItem ( Copper_Axe );
    StoreItem->SetSelectedItem ( 52 );

    StoreItem->AddItem ( Copper_Hoe );
    StoreItem->SetSelectedItem ( 53 );

    StoreItem->AddItem ( Copper_Pan );
    StoreItem->SetSelectedItem ( 54 );

    StoreItem->AddItem ( Copper_Pickaxe );
    StoreItem->SetSelectedItem ( 55 );

    StoreItem->AddItem ( Copper_Watering );
    StoreItem->SetSelectedItem ( 56 );

    StoreItem->AddItem ( Fiberglass_Rod );
    StoreItem->SetSelectedItem ( 57 );

    StoreItem->AddItem ( Gold_Axe );
    StoreItem->SetSelectedItem ( 58 );

    StoreItem->AddItem ( Gold_Hoe );
    StoreItem->SetSelectedItem ( 59 );

    StoreItem->AddItem ( Gold_Pan );
    StoreItem->SetSelectedItem ( 60 );

    StoreItem->AddItem ( Gold_Pickaxe );
    StoreItem->SetSelectedItem ( 61 );

    StoreItem->AddItem ( Gold_Watering_Can );
    StoreItem->SetSelectedItem ( 62 );

    StoreItem->AddItem ( Golden_Scythe );
    StoreItem->SetSelectedItem ( 63 );

    StoreItem->AddItem ( Hoe );
    StoreItem->SetSelectedItem ( 64 );

    StoreItem->AddItem ( Pickaxe );
    StoreItem->SetSelectedItem ( 65 );

    StoreItem->AddItem ( Milk_Pail );
    StoreItem->SetSelectedItem ( 66 );

    StoreItem->AddItem ( Scythe );
    StoreItem->SetSelectedItem ( 67 );

    StoreItem->AddItem ( Steel_Axe );
    StoreItem->SetSelectedItem ( 68 );

    StoreItem->AddItem ( Steel_Hoe );
    StoreItem->SetSelectedItem ( 69 );

    StoreItem->AddItem ( Steel_Pan );
    StoreItem->SetSelectedItem ( 70 );

    StoreItem->AddItem ( Steel_Pickaxe );
    StoreItem->SetSelectedItem ( 71 );

    StoreItem->AddItem ( Steel_Watering );
    StoreItem->SetSelectedItem ( 72 );

    StoreItem->AddItem ( Trash_Can_Copper );
    StoreItem->SetSelectedItem ( 73 );

    StoreItem->AddItem ( Watering_Can );
    StoreItem->SetSelectedItem ( 74 );

    StoreItem->AddItem ( Trash_Can_Steel );
    StoreItem->SetSelectedItem ( 75 );

    // 树苗列表  
    StoreItem->AddItem ( Apple_Sapling );
    StoreItem->SetSelectedItem ( 76 );

    StoreItem->AddItem ( Apricot_Sapling );
    StoreItem->SetSelectedItem ( 77 );

    StoreItem->AddItem ( Banana_Sapling );
    StoreItem->SetSelectedItem ( 78 );

    StoreItem->AddItem ( Cherry_Sapling );
    StoreItem->SetSelectedItem ( 79 );

    StoreItem->AddItem ( Mango_Sapling );
    StoreItem->SetSelectedItem ( 80 );

    StoreItem->AddItem ( Orange_Sapling );
    StoreItem->SetSelectedItem ( 81 );

    StoreItem->AddItem ( Peach_Sapling );
    StoreItem->SetSelectedItem ( 82 );

    StoreItem->AddItem ( Pomegranate_Sapling );
    StoreItem->SetSelectedItem ( 83 );



    // 设置计时器标签
    _timerLabel = Label::createWithTTF("Timer: 60", "fonts/Marker Felt.ttf", 24);
    this->addChild(_timerLabel, 10);
    _timerLabel->setPosition(Vec2(0, Director::getInstance()->getVisibleSize().height));
    _timerLabel->setScale(2.3f);

    // 创建并初始化 Label 来显示角色的位置
    _positionLabel = Label::createWithTTF("Position: (0, 0)", "fonts/Marker Felt.ttf", 24);
    if (_positionLabel)
    {
        this->addChild(_positionLabel, 10);
        _positionLabel->setScale(2.3f);
    }

    // 初始化开门键
    opendoor = Sprite::create("opendoor.png");
    this->addChild(opendoor, 11);
    opendoor->setVisible(false);

    // 设置背景图片
    auto background_real = Sprite::create("supermarket/supermarket.png");
    background_real->setPosition(Vec2(visibleSize.width / 2 + 1700, visibleSize.height / 2 + 370));
    this->addChild(background_real, 1);
    background_real->setScale(6.7f);

    auto background_up = Sprite::create("supermarket/supermarket_up.png");
    background_up->setPosition(Vec2(visibleSize.width / 2 + 1700, visibleSize.height / 2 + 370));
    this->addChild(background_up, 7);
    background_up->setScale(6.7f);

    auto background = Sprite::create("supermarket/supermarket_path.png");
    this->addChild(background, 5);
    background->setPosition(Vec2(visibleSize.width / 2 + 1700, visibleSize.height / 2 + 370));
    background->setScale(6.7f);


    Vec2 spritePosition = background->getPosition();   // 获取精灵的位置（中心点）
    Size spriteSize = background->getContentSize();    // 获取精灵的尺寸（宽度和高度）
  

    // 计算左下角的坐标
    Vec2 leftBottomPosition = Vec2(
        spritePosition.x - background->getScaleX() * spriteSize.width / 2,   // 中心点 x 坐标减去宽度的一半
        spritePosition.y - background->getScaleY() * spriteSize.height / 2   // 中心点 y 坐标减去高度的一半
    );
   

    Image img;
    if (img.initWithImageFile("supermarket/supermarket_path.png"))
    {
        int width = img.getWidth();
        int height = img.getHeight();

        // 获取像素数据
        unsigned char* data = img.getData();

        // 遍历所有像素，检查是否有内容（透明度大于0）
        for (int y = 0; y < height; y = y + 4)
        {
            for (int x = 0; x < width; x = x + 4)
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
    this->addChild(player1, 5);
    player1->schedule([=](float dt) {
        player1->player1_move();
        }, 0.05f, "player1_move");

    player1->schedule([=](float dt) {
        player1->player_change();
        }, 0.3f, "player_change");
    player1->setPosition(Vec2(visibleSize.width / 2 + 43, visibleSize.height / 2 - 101));  // 设置玩家初始位置
    player1->setScale(3.1f);
    player1->setAnchorPoint(Vec2(0.5f, 0.2f));
    player1->speed = 4.7f;

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
        // 调试输出鼠标位置
        CCLOG("Mouse Position: (%f, %f)", clickPos.x, clickPos.y);

        // 判断点击位置是否在精灵范围内
        if (button != nullptr && button->getBoundingBox().containsPoint(clickPos)) {
            CCLOG("Button clicked!");
            Director::getInstance()->end();
        }
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, button);

    // 设置键盘监听器
    auto listenerWithPlayer = EventListenerKeyboard::create();
    listenerWithPlayer->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event)
        {
            // 记录 Enter 键被按下
            if (keyCode == EventKeyboard::KeyCode::KEY_ENTER || keyCode == EventKeyboard::KeyCode::KEY_KP_ENTER) {
                isEnterKeyPressed = true;
                CCLOG("Enter key pressed.");
            }
            // 处理其他按键  
            if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
                static StoreUI* currentStoreUI = nullptr;  // 保存当前显示的 StoreUI  
                // 如果当前没有打开 StoreUI，则打开它  
                if (currentStoreUI == nullptr) {
                    CCLOG ( "Opening inventory." );
                    currentStoreUI = StoreUI::create ( inventory , StoreItem );
                    this->addChild ( currentStoreUI , 11 );
                } 
                else {
                    CCLOG ( "Closing inventory." );
                    this->removeChild ( currentStoreUI , true );
                    currentStoreUI = nullptr;  // 重置指针  
                }
            }
        };

    listenerWithPlayer->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event* event)
        {
            // 释放 Enter 键时，设置为 false
            if (keyCode == EventKeyboard::KeyCode::KEY_ENTER || keyCode == EventKeyboard::KeyCode::KEY_KP_ENTER) {
                isEnterKeyPressed = false;
                CCLOG("Enter key released.");
            }
        };

    // 将监听器添加到事件分发器中
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerWithPlayer, this);


    return true;
}


supermarket* supermarket::create()
{
    supermarket* scene = new supermarket();
    if (scene && scene->init())
    {
        scene->autorelease();
        return scene;
    }
    CC_SAFE_DELETE(scene);
    return nullptr;
}

// 检查玩家是否接近背景的轮廓点
void supermarket::checkPlayerPosition()
{
    // 获取玩家的位置
    Vec2 playerPos = player1->getPosition();

    // 更新位置标签的内容
    if (_positionLabel)
    {
        _positionLabel->setString("Position: (" + std::to_string(static_cast<int>(playerPos.x)) + ", " + std::to_string(static_cast<int>(playerPos.y)) + ")");
    
    }


    // 减少剩余时间
    remainingTime--;

    // 更新计时器显示
    remainingTime--;
    _timerLabel->setString("Timer: " + std::to_string(remainingTime / 600));


    // 更新标签位置
    float currentx = 0, currenty = 0;
    if (playerPos.x <= 743) {
        currentx = 743;
    }
    else if (playerPos.x >= 1773) {
        currentx = 1773;
    }
    else {
        currentx = playerPos.x;
    }

    if (playerPos.y <= -82) {
        currenty = -82;
    }
    else {
        currenty = playerPos.y;
    }


    _timerLabel->setPosition(currentx - 590, currenty + 570);
    _positionLabel->setPosition(currentx - 530, currenty + 490);
    button->setPosition(currentx + 690, currenty - 590);
   
    // 检查玩家是否进入目标区域，并且按下 Enter 键
    if (Region_Out.containsPoint(playerPos)) {
        // 玩家进入目标区域
        opendoor->setVisible(true);
        opendoor->setPosition(playerPos.x + 110, playerPos.y + 30);


        if (isEnterKeyPressed) {
            // 打印调试信息，检查 Enter 键的状态
            CCLOG("Player in target area, isEnterKeyPressed: %d", isEnterKeyPressed);
            // 调用场景切换逻辑
            player1->removeFromParent();
            auto nextscene = Town::create();
            Director::getInstance()->replaceScene(nextscene);
          
        }

    }
    else {
        opendoor->setVisible(false);
    }

    for (const auto& point : nonTransparentPixels)
    {
        // 计算玩家与轮廓点之间的距离
        float distance = 0;

        Vec2 temp;
        temp = playerPos;
        temp.x -= player1->speed;
        distance = temp.distance(point);
        if (distance <= 55) {
            player1->moveLeft = false;
           
        }
        else {
            if (player1->leftpressed == false) {
                player1->moveLeft = true;
            }
        }



        temp = playerPos;
        temp.y -= player1->speed;
        distance = temp.distance(point);
        if (distance <= 25) {
            player1->moveDown = false;
        }
        else {
            if (player1->downpressed == false) {
                player1->moveDown = true;
            }
        }

        temp = playerPos;
        temp.y += player1->speed;
        distance = temp.distance(point);
        if (distance <= 45) {
            player1->moveUp = false;
        }
        else {
            if (player1->uppressed == false) {
                player1->moveUp = true;
            }
        }

        temp = playerPos;
        temp.x += player1->speed;
        distance = temp.distance(point);
        if (distance <= 55) {
            player1->moveRight = false;
        }
        else {
            if (player1->rightpressed == false) {
                player1->moveRight = true;
            }
        }

    }



}




