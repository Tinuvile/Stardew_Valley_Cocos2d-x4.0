#include "AppDelegate.h"
#include "Town.h"
#include "supermarket.h"
#include "Player.h"
#include "physics/CCPhysicsWorld.h"
#include "ui/CocosGUI.h"

#include"Inventory.h"
#include"Item.h"
#include"Crop.h"
#include "InventoryUI.h"
#include "NPCreate.h"

USING_NS_CC;

extern int remainingTime;
extern Player* player1;
extern Town* town;
extern supermarket* seedshop;
extern std::map <std::pair<std::string, Vec2>, bool> T_lastplace;


Town::Town() {}

Town::~Town() {}

bool Town::init()
{


    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    button = cocos2d::Sprite::create("CloseNormal.png");
    this->addChild(button, 11);

    
    // 创建 Inventory 实例  
    inventory = new Inventory ();

    // 添加物品到库存  
    Item Grass ( "Grass" , "Item/Grass/grass-0.png" , 1 , 99 );
    Item Tools ( "Tools" , "Item/Tools/tools-16.png" , 1 , 99 );

    bool addedSuccessfully = inventory->AddItem ( Grass );
    if (addedSuccessfully) {
        inventory->SetSelectedItem ( 1 ); // 假设您想选择第一个槽位
        CCLOG ( "Item 'Grass' added successfully." );
    }
    else {
        CCLOG ( "Failed to add item 'Grass'. Inventory might be full." );
    }

    addedSuccessfully = inventory->AddItem ( Tools );
    if (addedSuccessfully) {
        inventory->SetSelectedItem ( 2 ); // 假设您想选择第一个槽位
        CCLOG ( "Item 'Grass' added successfully." );
    }
    else {
        CCLOG ( "Failed to add item 'Grass'. Inventory might be full." );
    }
    

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
        player1->speed = 1.5f;
    }

    // 初始化角色并将其添加到场景
    if (player1->getParent() == NULL) {
        this->addChild(player1, 5);
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


    /*
    // 创建 NPC  
    NPC* npc1 = NPCreate::CreateNPC ( "NPC1" , Vec2 ( 300 , 400 ) , "npc/Abigail/Abigail-0.png" ); // NPC 1  
    NPC* npc2 = NPCreate::CreateNPC ( "NPC2" , Vec2 ( 500 , 600 ) , "npc/Abigail/Abigail-1.png" ); // NPC 2  
    NPC* npc3 = NPCreate::CreateNPC ( "NPC3" , Vec2 ( 700 , 300 ) , "npc/Abigail/Abigail-2.png" ); // NPC 3  
  
    npc1->GetSprite ()->setScale ( player1->getScale () * 2.2 );
    npc2->GetSprite ()->setScale ( player1->getScale () * 2.2 );
    npc3->GetSprite ()->setScale ( player1->getScale () * 2.2 );

    this->addChild ( npc1->GetSprite () , 5 ); // 添加 NPC 1 到场景  
    this->addChild ( npc2->GetSprite () , 5 ); // 添加 NPC 2 到场景  
    this->addChild ( npc3->GetSprite () , 5 ); // 添加 NPC 3 到场景 
    */  


    // 设置键盘监听器
    auto listenerWithPlayer = EventListenerKeyboard::create();
    listenerWithPlayer->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event)
        {
            // 记录 Enter 键被按下
            if (keyCode == EventKeyboard::KeyCode::KEY_ENTER || keyCode == EventKeyboard::KeyCode::KEY_KP_ENTER) {
                isEnterKeyPressed = true;
                CCLOG("Enter key pressed. ");
            }
        };

    listenerWithPlayer->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event* event)
        {
            // 释放 Enter 键时，设置为 false
            if (keyCode == EventKeyboard::KeyCode::KEY_ENTER || keyCode == EventKeyboard::KeyCode::KEY_KP_ENTER) {
                isEnterKeyPressed = false;
                CCLOG("Enter key released. ");
            }
        };
    listenerWithPlayer->onKeyPressed = [this]( EventKeyboard::KeyCode keyCode , Event* event ) {
        // 其他键的处理  

        if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
            static InventoryUI* currentInventoryUI = nullptr;  // 保存当前显示的 InventoryUI
            // 如果当前没有打开 InventoryUI，则打开它
            if (currentInventoryUI == nullptr) {
                CCLOG ( "Opening inventory." );
                currentInventoryUI = InventoryUI::create ( inventory );
                this->addChild ( currentInventoryUI , 11 );  // 将 InventoryUI 添加到 Town 的上层
            }
            // 如果已经打开 InventoryUI，则关闭它
            else {
                CCLOG ( "Closing inventory." );
                this->removeChild ( currentInventoryUI , true );  // 从当前场景中移除 InventoryUI
                currentInventoryUI = nullptr;  // 重置指针
            }
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


    // 减少剩余时间
    remainingTime = remainingTime--;

    // 更新计时器显示
    remainingTime--;
    _timerLabel->setString("Timer: " + std::to_string(remainingTime / 60));

    // 更新标签位置
    float currentx = 0, currenty = 0;
    if (playerPos.x <= -117) {
        currentx = -117;
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

    
    _timerLabel->setPosition(currentx - 630, currenty + 570);
    _positionLabel->setPosition(currentx - 570, currenty + 490);
    button->setPosition(currentx + 730, currenty - 590);
   
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
            seedshop = supermarket::create();
            Director::getInstance()->replaceScene(seedshop);
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






