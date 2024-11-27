/*
做UI和做地图的同学自行修改一下GameBeginUI.cpp文件200行的场景跳转函数GameBegin::menuNewCallback(Ref* pSender)
*/


#include "GameBeginUI.h"
#include "CreateCharacterUI.h"
#include "Player.h"
#include "Town.h"

USING_NS_CC;

bool BeginScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    auto layer = cocos2d::LayerColor::create(cocos2d::Color4B(255, 255, 255, 255)); // 设置背景颜色为白色
    this->addChild(layer);

    // 播放开场动画
    playSplashAnimation();

    // 动画播放完后，切换到主菜单，并带过渡效果
    onAnimationComplete();
    return true;
}
void BeginScene::playSplashAnimation()
{
    // 1. 加载精灵帧
    cocos2d::Vector<cocos2d::SpriteFrame*> animationFrames;
    for (int i = 1; i <= 7; ++i) {
        std::string frameName = "UIresource/some/fircat" + std::to_string(i) + ".png";
        animationFrames.pushBack(cocos2d::SpriteFrame::create(frameName, cocos2d::Rect(0, 0, 83, 67)));
    }

    // 2. 创建动画对象
    Animation* animation = cocos2d::Animation::createWithSpriteFrames(animationFrames, 0.1f); // 0.1秒为每帧的持续时间

    // 3. 创建动画并播放
    Animate* animate = cocos2d::Animate::create(animation);

    // 4. 创建精灵并播放动画
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto sprite = cocos2d::Sprite::create("UIresource/some/fircat1.png"); // 初始帧
    sprite->setPosition(cocos2d::Vec2(500, 500)); // 设置位置
    //sprite->setPosition(cocos2d::Vec2(visibleSize.width / 2 , visibleSize.height / 2 )); // 设置位置
    this->addChild(sprite); // 添加到场景

    sprite->runAction(animate); // 播放动画
}
void BeginScene::onAnimationComplete()
{
    // 动画播放完后，切换到主菜单，并带过渡效果
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, GameBegin::createScene()));
}

Scene* GameBegin::createScene()
{
    return GameBegin::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GameBeginScene.cpp\n");
}

bool GameBegin::init()
{
    //////////////////////////////
    // 1. 添加“创建游戏”
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto BeginItem = MenuItemImage::create(
        "UIresource/start1.png",
        "UIresource/start1.png",
        CC_CALLBACK_1(GameBegin::menuNewCallback, this));

    if (BeginItem == nullptr ||
        BeginItem->getContentSize().width <= 0 ||
        BeginItem->getContentSize().height <= 0)
    {
        problemLoading("'UIresource/start1.png'");
    }
    else
    {
        //这里是不改变大小，更符合原游戏
        float scaleFactor = 3.0f;
        BeginItem->setScale(scaleFactor);

        //这里是自适应整个屏幕大小，不改变位置，原游戏中部分方块不会随着屏幕大小而变化大小,下面三个相同不再重复
        ///////////////////////////////////////////
        /*
        //获取图片原始尺寸
        Size BeginSize = BeginItem->getContentSize();
        // 设置图标的缩放比率
        float scaleX = visibleSize.width / BeginSize.width / 8;
        float scaleY = visibleSize.height / BeginSize.height / 8;
        // 使用 setScale 来缩放图片
        BeginItem->setScale(std::min(scaleX, scaleY));  // 保持宽高比
        */
        //float x = origin.x + (visibleSize.width - BeginItem->getContentSize().width * 2) / 3 + BeginItem->getContentSize().width / 2;
        float x = origin.x + visibleSize.width / 2 - BeginItem->getContentSize().width * 2.5 - 180.0f;
        float y = origin.y + 100.0f;
        BeginItem->setPosition(Vec2(x, y));
    }
    //2.添加“加载”，该功能不知道最后是否需要实现
    auto LoadItem = MenuItemImage::create(
        "UIresource/load1.png",
        "UIresource/load1.png",
        CC_CALLBACK_1(GameBegin::menuNewCallback, this));

    if (LoadItem == nullptr ||
        LoadItem->getContentSize().width <= 0 ||
        LoadItem->getContentSize().height <= 0)
    {
        problemLoading("'UIresource/load1.png'");
    }
    else
    {
        float scaleFactor = 3.0f;
        LoadItem->setScale(scaleFactor);
        float x = origin.x + visibleSize.width / 2 - BeginItem->getContentSize().width * 0.5 - 85;
        float y = origin.y + 100.0f;
        LoadItem->setPosition(Vec2(x, y));
    }
    //3.添加“合作”，该功能也不知道最后是否需要实现
    auto coopItem = MenuItemImage::create(
        "UIresource/coop1.png",
        "UIresource/coop1.png",
        CC_CALLBACK_1(GameBegin::menuNewCallback, this));

    if (coopItem == nullptr ||
        coopItem->getContentSize().width <= 0 ||
        coopItem->getContentSize().height <= 0)
    {
        problemLoading("'UIresource/coop1.png'");
    }
    else
    {
        float scaleFactor = 3.0f;
        coopItem->setScale(scaleFactor);
        float x = origin.x + visibleSize.width / 2 + BeginItem->getContentSize().width * 0.5 + 85;
        float y = origin.y + 100.0f;
        coopItem->setPosition(Vec2(x, y));
    }
    //4. 添加“关闭”图标以退出进度
    auto closeItem = MenuItemImage::create(
        // 这里一样@谭鹏翀
        "UIresource/quit1.png",
        "UIresource/quit1.png",
        CC_CALLBACK_1(GameBegin::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'UIresource/quit1.png'");
    }
    else
    { 
        float scaleFactor = 3.0f;
        closeItem->setScale(scaleFactor);
        float x = origin.x + visibleSize.width / 2 + BeginItem->getContentSize().width * 2.5 + 180.0f;
        float y = origin.y + 100.0f;
        closeItem->setPosition(Vec2(x, y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(BeginItem, LoadItem, coopItem, closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    /////////////////////////////
    // 3. 背景
    // add "GameBegin" splash screen"
    auto background = Sprite::create("Stardew Valley Unpacked Resources/LooseSprites/stardewPanorama.png");
    if (background == nullptr)
    {
        problemLoading("'stardewPanorama.png'");
    }
    else
    {
        // 计算所需的缩放比例  
        float scaleX = visibleSize.width / background->getContentSize().width;
        float scaleY = visibleSize.height / background->getContentSize().height;

        // 选择较大的缩放因子进行放大（以确保填充整个窗口）  
        float scaleFactor = std::max(scaleX, scaleY);
        background->setScale(scaleFactor);

        // position the background on the center of the screen
        background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        // add the background as a child to this layer
        this->addChild(background, 0);
    }

    auto Stardew_Valley_logo = Sprite::create("UIresource/title.png");
    if (Stardew_Valley_logo == nullptr)
    {
        problemLoading("'title.png'");
    }
    else
    {
        // position the Stardew_Valley_logo on the center of the screen
        //获取图片原始尺寸
        Size logoSize = Stardew_Valley_logo->getContentSize();
        // 设置图标的缩放比率
        float maxWidth = visibleSize.width * 0.6f; // 设定最大宽度为屏幕宽度的 60%
        float maxHeight = visibleSize.height * 0.6f; // 设定最大高度为屏幕高度的 60%
        float scaleX = maxWidth / logoSize.width;
        float scaleY = maxHeight / logoSize.height;
        // 使用 setScale 来缩放图片
        Stardew_Valley_logo->setScale(std::min(scaleX, scaleY));  // 保持宽高比
        Stardew_Valley_logo->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 4 * 2.5 + origin.y));

        // add the Stardew_Valley_logo as a child to this layer
        this->addChild(Stardew_Valley_logo, 1);
    }
    auto listener = EventListenerMouse::create();
    listener->onMouseMove = [this, BeginItem,LoadItem,coopItem , closeItem](EventMouse* event) {
        Vec2 mousePos = Vec2(event->getCursorX(), event->getCursorY());

        if (BeginItem->getBoundingBox().containsPoint(mousePos))
        {
            BeginItem->setNormalImage(cocos2d::Sprite::create("UIresource/start2.png"));
            BeginItem->setSelectedImage(cocos2d::Sprite::create("UIresource/start2.png"));
            BeginItem->setScale(3.2f);
        }
        else
        {
            BeginItem->setNormalImage(cocos2d::Sprite::create("UIresource/start1.png"));
            BeginItem->setSelectedImage(cocos2d::Sprite::create("UIresource/start1.png"));
            BeginItem->setScale(3.0f);
        }

        if (LoadItem->getBoundingBox().containsPoint(mousePos))
        {
            LoadItem->setNormalImage(cocos2d::Sprite::create("UIresource/load2.png"));
            LoadItem->setSelectedImage(cocos2d::Sprite::create("UIresource/load2.png"));
            LoadItem->setScale(3.2f);
        }
        else
        {
            LoadItem->setNormalImage(cocos2d::Sprite::create("UIresource/load1.png"));
            LoadItem->setSelectedImage(cocos2d::Sprite::create("UIresource/load1.png"));
            LoadItem->setScale(3.0f);
        }

        if (coopItem->getBoundingBox().containsPoint(mousePos))
        {
            coopItem->setNormalImage(cocos2d::Sprite::create("UIresource/coop2.png"));
            coopItem->setSelectedImage(cocos2d::Sprite::create("UIresource/coop2.png"));
            coopItem->setScale(3.2f);
        }
        else
        {
            coopItem->setNormalImage(cocos2d::Sprite::create("UIresource/coop1.png"));
            coopItem->setSelectedImage(cocos2d::Sprite::create("UIresource/coop1.png"));
            coopItem->setScale(3.0f);
        }

        if (closeItem->getBoundingBox().containsPoint(mousePos))
        {
            closeItem->setNormalImage(cocos2d::Sprite::create("UIresource/quit2.png"));
            closeItem->setSelectedImage(cocos2d::Sprite::create("UIresource/quit2.png"));
            closeItem->setScale(3.2f);
        }
        else
        {
            closeItem->setNormalImage(cocos2d::Sprite::create("UIresource/quit1.png"));
            closeItem->setSelectedImage(cocos2d::Sprite::create("UIresource/quit1.png"));
            closeItem->setScale(3.0f);
        }
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}

// 跳转到新场景  
void GameBegin::menuNewCallback(Ref* pSender)
{
    //Director::getInstance()->replaceScene(CreateCharacter::createScene()); // 跳转到 CreateCharacterUI 场景@谭
    Director::getInstance()->replaceScene(myhouse::create()); // 进入到主地图
}

void GameBegin::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
