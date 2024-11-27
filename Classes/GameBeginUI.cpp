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

    return true;
}

void BeginScene::playSplashAnimation()
{
    // 1. 加载精灵帧  
    cocos2d::Vector<cocos2d::SpriteFrame*> animationFrames;
    for (int i = 2; i <= 7; ++i) {
        std::string frameName = "UIresource/some/fircat" + std::to_string(i) + ".png";
        auto frame = cocos2d::SpriteFrame::create(frameName, cocos2d::Rect(0, 0, 83, 67));
        if (frame) {
            animationFrames.pushBack(frame);
        }
        else {
            CCLOG("Error loading frame: %s", frameName.c_str());
        }
    }

    // 2. 创建动画对象  
    auto animation = cocos2d::Animation::createWithSpriteFrames(animationFrames, 0.1f); // 0.1秒为每帧的持续时间  

    // 3. 创建精灵并播放动画  
    auto visibleSize = Director::getInstance()->getVisibleSize();

    // 使用第一帧创建精灵  
    auto sprite = cocos2d::Sprite::createWithSpriteFrame(animationFrames.at(0));

    // 设定锚点为中心位置  
    sprite->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));

    // 确保初始位置在中心  
    sprite->setPosition(visibleSize / 2);
    this->addChild(sprite); // 添加到场景  

    // 4. 使用动画播放  
    auto animate = cocos2d::Animate::create(animation);
    auto animateSequence = Sequence::create(
        animate,
        CallFunc::create([this, sprite]() {
            // 确保在动画结束后仍保持在中心位置  
            auto visibleSize = Director::getInstance()->getVisibleSize();
            sprite->setPosition(visibleSize / 2); // 确保精灵位置在屏幕中心  
            onAnimationComplete();
            }),
        nullptr
    );

    sprite->runAction(animateSequence); // 播放动画  

    // 添加日志以跟踪位置  
    sprite->runAction(RepeatForever::create(Sequence::create(
        DelayTime::create(0.1),
        CallFunc::create([sprite]() {
            CCLOG("Current Position: %f, %f", sprite->getPositionX(), sprite->getPositionY());
            }),
        nullptr
    )));
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

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
}

bool GameBegin::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 创建菜单项  
    auto BeginItem = createMenuItem("UIresource/start1.png", "UIresource/start1.png", CC_CALLBACK_1(GameBegin::menuNewCallback, this), visibleSize, origin, -180.0f);
    auto LoadItem = createMenuItem("UIresource/load1.png", "UIresource/load1.png", CC_CALLBACK_1(GameBegin::menuNewCallback, this), visibleSize, origin, -85.0f);
    auto coopItem = createMenuItem("UIresource/coop1.png", "UIresource/coop1.png", CC_CALLBACK_1(GameBegin::menuNewCallback, this), visibleSize, origin, 85.0f);
    auto closeItem = createMenuItem("UIresource/quit1.png", "UIresource/quit1.png", CC_CALLBACK_1(GameBegin::menuCloseCallback, this), visibleSize, origin, 180.0f);

    // 创建菜单  
    auto menu = Menu::create(BeginItem, LoadItem, coopItem, closeItem, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // 添加背景  
    addBackground(visibleSize, origin);
    addLogo(visibleSize, origin);

    // 添加鼠标监听器  
    addMouseListener(BeginItem, LoadItem, coopItem, closeItem);

    return true;
}

MenuItemImage* GameBegin::createMenuItem(const std::string& normalImage, const std::string& selectedImage, const ccMenuCallback& callback, const Size& visibleSize, const Vec2& origin, float offsetX)
{
    auto item = MenuItemImage::create(normalImage, selectedImage, callback);
    if (item) {
        item->setScale(3.0f);
        float x = origin.x + visibleSize.width / 2 + offsetX;
        float y = origin.y + 100.0f;
        item->setPosition(Vec2(x, y));
    }
    else {
        problemLoading(normalImage.c_str());
    }
    return item;
}

void GameBegin::addBackground(const Size& visibleSize, const Vec2& origin)
{
    auto background = Sprite::create("Stardew Valley Unpacked Resources/LooseSprites/stardewPanorama.png");
    if (background) {
        float scaleX = visibleSize.width / background->getContentSize().width;
        float scaleY = visibleSize.height / background->getContentSize().height;
        float scaleFactor = std::max(scaleX, scaleY);
        background->setScale(scaleFactor);
        background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        this->addChild(background, 0);
    }
    else {
        problemLoading("'stardewPanorama.png'");
    }
}

void GameBegin::addLogo(const Size& visibleSize, const Vec2& origin)
{
    auto logo = Sprite::create("UIresource/title.png");
    if (logo) {
        Size logoSize = logo->getContentSize();
        float maxWidth = visibleSize.width * 0.6f;
        float maxHeight = visibleSize.height * 0.6f;
        float scaleX = maxWidth / logoSize.width;
        float scaleY = maxHeight / logoSize.height;
        logo->setScale(std::min(scaleX, scaleY));
        logo->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 4 * 2.5 + origin.y));
        this->addChild(logo, 1);
    }
    else {
        problemLoading("'title.png'");
    }
}

void GameBegin::addMouseListener(MenuItemImage* BeginItem, MenuItemImage* LoadItem, MenuItemImage* coopItem, MenuItemImage* closeItem)
{
    auto listener = EventListenerMouse::create();
    listener->onMouseMove = [this, BeginItem, LoadItem, coopItem, closeItem](EventMouse* event) {
        Vec2 mousePos = Vec2(event->getCursorX(), event->getCursorY());

        updateMenuItem(BeginItem, mousePos, "UIresource/start1.png", "UIresource/start2.png");
        updateMenuItem(LoadItem, mousePos, "UIresource/load1.png", "UIresource/load2.png");
        updateMenuItem(coopItem, mousePos, "UIresource/coop1.png", "UIresource/coop2.png");
        updateMenuItem(closeItem, mousePos, "UIresource/quit1.png", "UIresource/quit2.png");
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void GameBegin::updateMenuItem(MenuItemImage* item, const Vec2& mousePos, const std::string& normalImage, const std::string& selectedImage)
{
    if (item->getBoundingBox().containsPoint(mousePos)) {
        item->setNormalImage(cocos2d::Sprite::create(selectedImage));
        item->setSelectedImage(cocos2d::Sprite::create(selectedImage));
        item->setScale(3.2f);
    }
    else {
        item->setNormalImage(cocos2d::Sprite::create(normalImage));
        item->setSelectedImage(cocos2d::Sprite::create(normalImage));
        item->setScale(3.0f);
    }
}

// 跳转到新场景  
void GameBegin::menuNewCallback(Ref* pSender)
{
    Director::getInstance()->replaceScene(Town::create()); // 进入到主地图  
}

void GameBegin::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}