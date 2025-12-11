#include "../Core/AppDelegate.h"
#include "Barn.h"
#include "farm.h"
#include "../Entities/Player.h"
#include "../Core/InputManager.h"
#include "../Commands/SceneInteractionCommand.h"
#include "../Commands/UICommand.h"



Barn::Barn() {}

Barn::~Barn() {
    cleanupInputCommands();
}

bool Barn::init ()
{

    if (!livestocks.empty ()) {
        for (auto livestock : livestocks) {
            if (livestock != nullptr) {
                this->addChild ( livestock , 10 );
            }
        }
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //button = cocos2d::Sprite::create("CloseNormal.png");
    //this->addChild(button, 11);

    // 设置计时器标签
    // 设置计时器标签
   
    TimeUI = Timesystem::create("Barn");
    this->addChild(TimeUI, 17);

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
        // 在添加到场景后设置输入绑定
        player1->setupInputBindings();
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

    // 设置Command Pattern输入命令
    setupInputCommands();

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


    // 移除更新物品栏轮询，交给Observer

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
    // 设置碰撞上下文
    player1->setCollisionContext(nonTransparentPixels);
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    TimeUI->setPosition(visibleSize.width / 2, visibleSize.height / 2);

    // 获取玩家的位置
    Vec2 playerPos = player1->getPosition();

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

            if (day == 1) {
                crop->watered = true;
            }
            if ((day - 1) % 3 == 1) {
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

        //恢复为能够生产产品
        for (auto livestock : livestocks) {
            livestock->SetCanProduce ( true );
        }

        IsSleep = false;
        frombed = true;
        remainingTime = 10800;
        player1->removeFromParent();
        auto nextday = Myhouse::create();
        Director::getInstance()->replaceScene(nextday);

    }

    // 碰撞检测逻辑已移到Player类的updateMovementPermissions方法中
    // 通过setCollisionContext设置碰撞点即可
    // 碰撞权限会在Player的player1_move()中自动更新


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

void Barn::setupInputCommands() {
    auto inputManager = InputManager::getInstance();

    // 创建背包切换命令 (ESC键)
    auto toggleInventoryCommand = std::make_shared<ToggleInventoryCommand>(
        this, inventory, "Barn"
    );

    // 创建场景切换命令 (ENTER键) - 离开畜棚回到农场
    auto exitBarnCommand = std::make_shared<ConditionalSceneTransitionCommand>(
        player1,
        []() -> cocos2d::Scene* { return farm::create(); },
        [this]() -> bool {
            Vec2 playerPos = player1->getPosition();
            return Out_Barn.containsPoint(playerPos);
        },
        [this]() -> void {
            // 设置位置状态
            for (auto& pair : F_lastplace) {
                if (pair.first.first == "farm") {
                    pair.second = true;
                }
            }
            player1->removeFromParent();
        },
        "barn_to_farm"
    );

    // 绑定命令到键盘
    inputManager->bindPressCommand(EventKeyboard::KeyCode::KEY_ESCAPE, toggleInventoryCommand);
    inputManager->bindPressCommand(EventKeyboard::KeyCode::KEY_ENTER, exitBarnCommand);
    inputManager->bindPressCommand(EventKeyboard::KeyCode::KEY_KP_ENTER, exitBarnCommand);

    // 保存命令引用以便清理
    boundCommands.push_back(toggleInventoryCommand);
    boundCommands.push_back(exitBarnCommand);
}

void Barn::cleanupInputCommands() {
    auto inputManager = InputManager::getInstance();
    
    // 逐一解绑命令
    for (auto& command : boundCommands) {
        inputManager->unbindCommand(EventKeyboard::KeyCode::KEY_ESCAPE, command);
        inputManager->unbindCommand(EventKeyboard::KeyCode::KEY_ENTER, command);
        inputManager->unbindCommand(EventKeyboard::KeyCode::KEY_KP_ENTER, command);
    }
    
    // 清理命令引用
    boundCommands.clear();
}
