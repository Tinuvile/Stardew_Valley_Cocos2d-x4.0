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
    auto layer = cocos2d::LayerColor::create(cocos2d::Color4B(255, 255, 255, 255)); // ���ñ�����ɫΪ��ɫ  
    this->addChild(layer);

    // ���ſ�������  
    playSplashAnimation();

    return true;
}

void BeginScene::playSplashAnimation()
{
    // 1. ���ؾ���֡
    cocos2d::Vector<cocos2d::SpriteFrame* >animationFrames1;
    for (int i = 2; i <= 7; ++i) {
        std::string frameName = "UIresource/some/fircat" + std::to_string(i) + ".png";
        auto frame = cocos2d::SpriteFrame::create(frameName, cocos2d::Rect(0, 0, 83, 67));
        if (frame) {
            animationFrames1.pushBack(frame);
        }
        else {
            CCLOG("Error loading frame: %s", frameName.c_str());
        }
    }

    // 2. ������������  
    auto animation1 = cocos2d::Animation::createWithSpriteFrames(animationFrames1, 0.3f); // 0.3��Ϊÿ֡�ĳ���ʱ��  

    // 3. �������鲢���Ŷ���  
    auto visibleSize = Director::getInstance()->getVisibleSize();

    // ʹ�õ�һ֡��������  
    auto sprite1 = cocos2d::Sprite::createWithSpriteFrame(animationFrames1.at(0));

    // �趨ê��Ϊ����λ��  
    sprite1->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));

    // ȷ����ʼλ��  
    sprite1->setPosition(visibleSize.width / 2.5 - 170, visibleSize.height / 2.5);
    this->addChild(sprite1); // ��ӵ�����  


    //�ڶ����ֶ������������Ƶ�һ����

    cocos2d::Vector<cocos2d::SpriteFrame*> animationFrames2;
    std::string frameName1 = "UIresource/some/fircon2.png";
    auto frame1 = SpriteFrame::create("UIresource/some/fircon2.png", Rect(0, 0, 110, 57));
    auto frame2 = SpriteFrame::create("UIresource/some/fircon1.png", Rect(0, 0, 107, 54));

    animationFrames2.pushBack(frame1);
    animationFrames2.pushBack(frame2);
    auto animation2 = cocos2d::Animation::createWithSpriteFrames(animationFrames2, 0.3f); // 0.3��Ϊÿ֡�ĳ���ʱ��  

    auto sprite2 = cocos2d::Sprite::createWithSpriteFrame(animationFrames2.at(0));

    sprite2->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));

    sprite2->setPosition(visibleSize.width / 2.5 + 250, visibleSize.height / 2 + 30);
    this->addChild(sprite2); // ��ӵ�����  



    // 4. ʹ�ö�������  
    auto animate1 = cocos2d::Animate::create(animation1);
    auto animateSequence1 = Sequence::create(
        animate1,
        CallFunc::create([this, sprite1]() {
            // ȷ���ڶ����������Ա���������λ��  
            auto visibleSize = Director::getInstance()->getVisibleSize();
            sprite1->setPosition(visibleSize.width / 2.5 - 170, visibleSize.height / 2.5); // ȷ������λ����ԭ��  
            onAnimationComplete();
            }),
        nullptr
    );
    auto animate2 = cocos2d::Animate::create(animation2);
    auto repeatAnimate2 = Repeat::create(animate2, 3);

    sprite1->setScale(3.0f);  // ������������������
    sprite2->setScale(3.0f);  // ������������������
    sprite1->runAction(animateSequence1); // ���Ŷ���  
    sprite2->runAction(repeatAnimate2); // ���Ŷ���  
    // �����־�Ը���λ��  
    sprite1->runAction(RepeatForever::create(Sequence::create(
        DelayTime::create(0.1),
        CallFunc::create([sprite1]() {
            CCLOG("Current Position: %f, %f", sprite1->getPositionX(), sprite1->getPositionY());
            }),
        nullptr
    )));
}


void BeginScene::onAnimationComplete()
{
    // ������������л������˵�����������Ч��  
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

    // �����˵���  
    auto BeginItem = createMenuItem("UIresource/start1.png", "UIresource/start1.png", CC_CALLBACK_1(GameBegin::menuNewCallback, this), visibleSize.width, origin, -180.0f, -185.0f);
    auto LoadItem = createMenuItem("UIresource/load1.png", "UIresource/load1.png", CC_CALLBACK_1(GameBegin::menuNewCallback, this), visibleSize.width, origin, -85.0f, -37.0f);
    auto coopItem = createMenuItem("UIresource/coop1.png", "UIresource/coop1.png", CC_CALLBACK_1(GameBegin::menuNewCallback, this), visibleSize.width, origin, 85.0f, 37.0f);
    auto closeItem = createMenuItem("UIresource/quit1.png", "UIresource/quit1.png", CC_CALLBACK_1(GameBegin::menuCloseCallback, this), visibleSize.width, origin, 180.0f, 185.0f);

    // �����˵�  
    auto menu = Menu::create(BeginItem, LoadItem, coopItem, closeItem, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // ��ӱ���  
    addBackground(visibleSize, origin);
    addLogo(visibleSize, origin);

    // �����������  
    addMouseListener(BeginItem, LoadItem, coopItem, closeItem);

    return true;
}

MenuItemImage* GameBegin::createMenuItem(const std::string& normalImage, const std::string& selectedImage, const ccMenuCallback& callback, const float& Width, const Vec2& origin, float offsetX, const float& n_itemWidth)
{
    auto item = MenuItemImage::create(normalImage, selectedImage, callback);
    /*
    //�����дһ������Ӧ��С��д����Ŀǰд��Ӧ�ò��������������ڹ�С���ص���
    //��ȡͼƬԭʼ�ߴ�
    Size itemSize = item->getContentSize();
    // ��ȡ��Ļ��������Ĵ�С
    auto visibleSize = Director::getInstance()->getVisibleSize();
    // ����ͼ������ű���
    float scaleX = visibleSize.width / itemSize.width / 8;
    float scaleY = visibleSize.height / itemSize.height / 8;
    // ʹ�� setScale ������ͼƬ
    item->setScale(std::min(scaleX, scaleY));  // ���ֿ�߱�
    */
    if (item) {
        item->setScale(3.0f);
        float x = origin.x + Width / 2 + offsetX + n_itemWidth;
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

// ��ת���³���  
void GameBegin::menuNewCallback(Ref* pSender)
{
    Director::getInstance()->replaceScene(Town::create()); // ���뵽����ͼ  
}

void GameBegin::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}