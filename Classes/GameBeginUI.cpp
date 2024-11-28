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
    //��������

    cocos2d::Vector<cocos2d::SpriteFrame*> animationFrames;
    std::string frameName1 = "UIresource/hebing1.png";
    auto frame1 = SpriteFrame::create("UIresource/hebing1.png", Rect(0, 0, 214, 67));
    auto frame2 = SpriteFrame::create("UIresource/hebing2.png", Rect(0, 0, 220, 69));
    auto frame3 = SpriteFrame::create("UIresource/hebing3.png", Rect(0, 0, 214, 67));
    auto frame4 = SpriteFrame::create("UIresource/hebing4.png", Rect(0, 0, 220, 69));
    auto frame5 = SpriteFrame::create("UIresource/hebing5.png", Rect(0, 0, 214, 67));
    auto frame6 = SpriteFrame::create("UIresource/hebing6.png", Rect(0, 0, 220, 69));
    animationFrames.pushBack(frame1);
    animationFrames.pushBack(frame2);
    animationFrames.pushBack(frame3);
    animationFrames.pushBack(frame4);
    animationFrames.pushBack(frame5);
    animationFrames.pushBack(frame6);
    auto animation = cocos2d::Animation::createWithSpriteFrames(animationFrames, 0.2f); // 0.2��Ϊÿ֡�ĳ���ʱ��  

    auto sprite = cocos2d::Sprite::createWithSpriteFrame(animationFrames.at(0));

    sprite->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));

    auto visibleSize = Director::getInstance()->getVisibleSize();
    sprite->setPosition(visibleSize.width / 2.5 + 150.0f , visibleSize.height / 2 );
    this->addChild(sprite); // ��ӵ�����  

    // 4. ʹ�ö�������  
    auto animate = cocos2d::Animate::create(animation);
    // �ڶ�����ɺ��þ���͸��
    auto fadeOut = FadeOut::create(1.0f); // 1������ʧ
    auto sequence1 = Sequence::create(animate, fadeOut, nullptr); // ������ɺ�ִ��FadeOut
    auto animateSequence = Sequence::create(
        sequence1,
        CallFunc::create([this, sprite]() {
            // ȷ���ڶ����������Ա���������λ��  
            auto visibleSize = Director::getInstance()->getVisibleSize();
            sprite->setPosition(visibleSize.width / 2.5 + 150.0f, visibleSize.height / 2); // ȷ������λ����ԭ��  
            onAnimationComplete();
            }),
        nullptr
    );
    sprite->setScale(3.0f);  // ������������������
    sprite->runAction(animateSequence); // ���Ŷ���   
}


void BeginScene::onAnimationComplete()
{
    Director::getInstance()->replaceScene(GameBegin::createScene());
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

    // ������������л������˵�
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto layer = cocos2d::LayerColor::create(cocos2d::Color4B(255, 255, 255, 255),
        visibleSize.width,
        visibleSize.height);
    this->addChild(layer, 5);
    // ʹ�� fadeIn ������ʹ���͸������ȫ��͸��
    layer->runAction(cocos2d::FadeTo::create(2.0f, 0)); // 2���ڴ�͸������ȫ��͸��
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