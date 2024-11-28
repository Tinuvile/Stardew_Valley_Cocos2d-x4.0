#include "GameBeginUI.h"  
#include "CreateCharacterUI.h"  
#include "Player.h"  
#include "Town.h"  

USING_NS_CC;
///////////////////////////////
//����ΪBeginScene��ʼ������ʵ�ֲ���
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
}

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
    sprite->setPosition(visibleSize.width / 2.5 + visibleSize.width * 0.139, visibleSize.height / 2 );
    this->addChild(sprite); // ��ӵ�����  

    // 4. ʹ�ö�������  
    auto animate = cocos2d::Animate::create(animation);
    // �ڶ�����ɺ��þ���͸��
    auto fadeOut = FadeOut::create(1.0f); // 1.0������ʧ
    auto sequence1 = Sequence::create(animate, fadeOut, nullptr); // ������ɺ�ִ��FadeOut
    auto animateSequence = Sequence::create(
        sequence1,
        CallFunc::create([this, sprite]() {
            // ȷ���ڶ����������Ա���������λ��  
            auto visibleSize = Director::getInstance()->getVisibleSize();
            sprite->setPosition(visibleSize.width / 2.5 + visibleSize.width * 0.139, visibleSize.height / 2); // ȷ������λ����ԭ��  
            onAnimationComplete();
            }),
        nullptr
    );
    sprite->setScale(3.0f);  // ������������������
    sprite->runAction(animateSequence); // ���Ŷ���   
}

void BeginScene::onAnimationComplete()
{
    //Director::getInstance()->replaceScene(GameBegin::createScene());
    Director::getInstance()->replaceScene(NextScene::create());
}

/////////////////////
//����ΪNextSceneʵ�ֲ��֣�����ʵ�ֽ����ϲ��֡��������˵��Ķ���Ч��
bool NextScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    // ��ʼ������������л��˶���
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto layer = cocos2d::LayerColor::create(cocos2d::Color4B(255, 255, 255, 255),
        visibleSize.width,
        visibleSize.height);
    this->addChild(layer, 5);
    // ʹ�� fadeIn ������ʹ���͸������ȫ��͸��
    layer->runAction(cocos2d::FadeTo::create(2.0f, 0)); // 2���ڴ�͸������ȫ��͸��
    addBackground(visibleSize, origin);
    addmoun_tree(visibleSize, origin);
    birdfly();
    return true;
}
void NextScene::addBackground(const Size& visibleSize, const Vec2& origin)
{
    //auto background = Sprite::create("Stardew Valley Unpacked Resources/LooseSprites/stardewPanorama.png");
    auto background = Sprite::create("UIresource/background1.png");
    if (background) {
        float scaleX = visibleSize.width / background->getContentSize().width;
        float scaleY = visibleSize.height / background->getContentSize().height;
        float scaleFactor = std::max(scaleX, scaleY);
        background->setScale(scaleFactor);
        background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        this->addChild(background, 0);
    }
    else {
        problemLoading("'background1.png'");
    }
}

void NextScene::addmoun_tree(const cocos2d::Size& visibleSize, const cocos2d::Vec2& origin)
{
    auto mountain1 = Sprite::create("UIresource/mountainfront.png");
    auto mountain2 = Sprite::create("UIresource/mountainbehind.png");
    auto treeleft  = Sprite::create("UIresource/treeleft.png");
    auto treeright = Sprite::create("UIresource/treeright.png");
    if (mountain1) {
        // ��ȡ�����ԭʼ�ߴ�
        Size spriteSize = mountain1->getContentSize();

        // �������ű���
        float scaleX = visibleSize.width / spriteSize.width; // ������Ļ��Ⱥ;����ȼ���ˮƽ���ű���
        float scaleY = scaleX; // ���ֳ���Ȳ��䣬���Y������ű�������X������ű���

        // ���ݼ�����ı������þ��������
        mountain1->setScale(2 * scaleX); // ����ʹ�� setScale(scaleX, scaleY);
        mountain1->setPosition(Vec2(visibleSize.width / 2 + origin.x, origin.y + visibleSize.height * 0.25));
        this->addChild(mountain1, 2);
    }
    else {
        problemLoading("'mountain1.png'");
    }
    if (mountain2) {
        Size spriteSize = mountain2->getContentSize();

        // �������ű���
        float scaleX = visibleSize.width / spriteSize.width; // ������Ļ��Ⱥ;����ȼ���ˮƽ���ű���
        float scaleY = scaleX; // ���ֳ���Ȳ��䣬���Y������ű�������X������ű���

        // ���ݼ�����ı������þ��������
        mountain2->setScale(2 * scaleX);
        mountain2->setPosition(Vec2(visibleSize.width / 2 + origin.x - visibleSize.width * 0.05, origin.y + visibleSize.height * 0.35));
        this->addChild(mountain2, 1);
    }
    else {
        problemLoading("'mountain2.png'");
    }
    if (treeleft) {
        Size spriteSize = treeleft->getContentSize();

        // �������ű���
        float maxWidth = visibleSize.width * 0.6f;
        float maxHeight = visibleSize.height * 0.6f;
        float scaleX = maxWidth / spriteSize.width;
        float scaleY = maxHeight / spriteSize.height;
        // ʹ�� setScale ������ͼƬ
        treeleft->setScale(std::min(scaleX, scaleY));  // ���ֿ�߱�
        // ����ê��Ϊ���½�
        treeleft->setAnchorPoint(Vec2(0, 0));
        // �������λ������Ϊ��Ļ���½�
        treeleft->setPosition(Vec2(0, 0));
        this->addChild(treeleft, 4);
    }
    else {
        problemLoading("'treeleft.png'");
    }
    if (treeright) {
        Size spriteSize = treeright->getContentSize();

        // �������ű���
        float maxWidth = visibleSize.width * 0.6f;
        float maxHeight = visibleSize.height * 0.6f;
        float scaleX = maxWidth / spriteSize.width;
        float scaleY = maxHeight / spriteSize.height;
        // ʹ�� setScale ������ͼƬ
        treeright->setScale(std::min(scaleX, scaleY));  // ���ֿ�߱�
        // ����ê��Ϊ���½�
        treeright->setAnchorPoint(Vec2(1, 0));
        // �������λ������Ϊ��Ļ���½�
        treeright->setPosition(Vec2(visibleSize.width, 0));
        this->addChild(treeright, 4);
    }
    else {
        problemLoading("'treeright.png'");
    }
}

void NextScene::birdfly()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    // ��������֡
    Vector<cocos2d::SpriteFrame*> animFrames;

    // ����4��ͼƬ
    animFrames.pushBack(cocos2d::SpriteFrame::create("UIresource/fly1.png", cocos2d::Rect(0, 0, 26, 26)));
    animFrames.pushBack(cocos2d::SpriteFrame::create("UIresource/fly2.png", cocos2d::Rect(0, 0, 26, 26)));
    animFrames.pushBack(cocos2d::SpriteFrame::create("UIresource/fly3.png", cocos2d::Rect(0, 0, 26, 26)));
    animFrames.pushBack(cocos2d::SpriteFrame::create("UIresource/fly4.png", cocos2d::Rect(0, 0, 26, 26)));

    // ��������
    auto animation1 = cocos2d::Animation::createWithSpriteFrames(animFrames, 0.2f);  // ÿ֡0.2��
    auto animation2 = cocos2d::Animation::createWithSpriteFrames(animFrames, 0.2f);  // ÿ֡0.2��
    // ������������
    auto animate1 = cocos2d::Animate::create(animation1);
    auto animate2 = cocos2d::Animate::create(animation2);
    // �����ظ��Ĵ�����ʹ��ʱ�����Ҫ��
    float totalDuration = 5.0f;  // �趨��ʱ��
    int repeatCount1 = totalDuration / animation1->getDuration();
    auto repeatedAction1 = Repeat::create(animate1, repeatCount1);
    int repeatCount2 = totalDuration / animation2->getDuration();
    auto repeatedAction2 = Repeat::create(animate2, repeatCount2);
    // �����ƶ�����
    auto moveAction1 = MoveBy::create(5.0f, Vec2(-visibleSize.width / 2, 0)); // 2������X���ƶ�
    auto moveAction2 = MoveBy::create(5.0f, Vec2(-visibleSize.width / 2, 0)); // 2������X���ƶ�
    // �������鲢���Ŷ���
     auto sprite1 = cocos2d::Sprite::createWithSpriteFrame(animFrames.at(0));
     auto sprite2 = cocos2d::Sprite::createWithSpriteFrame(animFrames.at(0));
     sprite1->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 3));  // ���þ���λ��
     sprite2->setPosition(cocos2d::Vec2(visibleSize.width / 1.8, visibleSize.height / 3.2));  // ���þ���λ��
     // ͬʱִ�ж������ƶ�
     auto spawnAction1 = Spawn::create(repeatedAction1, moveAction1, nullptr);
     auto spawnAction2 = Spawn::create(repeatedAction2, moveAction2, nullptr);
     auto sequence = Sequence::create(
         spawnAction1,
         CallFunc::create([this, sprite1]() {
         AnimationComplete(); }),
         nullptr);
     sprite1->runAction(sequence); // ѭ�����Ŷ���
     sprite2->runAction(spawnAction2);  // ѭ�����Ŷ���
    // ��������ӵ�������
    sprite1->setScale(2.0f);  // ������������������
    sprite2->setScale(2.0f);  // ������������������
    this->addChild(sprite1, 3);
    this->addChild(sprite2, 3);
}

void  NextScene::AnimationComplete()
{
    Director::getInstance()->replaceScene(TransitionFade::create(2.0f, GameBegin::createScene()));
}
/////////////////////
//����ΪGameBeginʵ�ֲ��֣�����ʵ�����˵�����
Scene* GameBegin::createScene()
{
    return GameBegin::create();
}


bool GameBegin::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    // ��ӱ�����logo  
    addBackground(visibleSize, origin);
    addLogo(visibleSize, origin);

    // �����˵���  
    auto BeginItem = createMenuItem("UIresource/start1.png", "UIresource/start1.png", CC_CALLBACK_1(GameBegin::menuNewCallback, this), origin, -visibleSize.width * 0.338);
    auto LoadItem = createMenuItem("UIresource/load1.png", "UIresource/load1.png", CC_CALLBACK_1(GameBegin::menuNewCallback, this), origin, -visibleSize.width * 0.113);
    auto coopItem = createMenuItem("UIresource/coop1.png", "UIresource/coop1.png", CC_CALLBACK_1(GameBegin::menuNewCallback, this),  origin, visibleSize.width * 0.113);
    auto closeItem = createMenuItem("UIresource/quit1.png", "UIresource/quit1.png", CC_CALLBACK_1(GameBegin::menuCloseCallback, this), origin, visibleSize.width * 0.338);

    // ʹ����ʱ��˳�򶯻�����ʾ�˵���
    auto delay1 = DelayTime::create(1.0f); // 1���ӳ�
    auto delay2 = DelayTime::create(1.0f); // 1���ӳ�
    auto delay3 = DelayTime::create(1.0f); // 1���ӳ�

    auto showBeginItem = FadeIn::create(1.0f);  // ��ʼ��ť����
    auto showLoadItem = FadeIn::create(1.0f);   // ���ذ�ť����
    auto showCoopItem = FadeIn::create(1.0f);   // ������ť����
    auto showCloseItem = FadeIn::create(1.0f);  // �˳���ť����

    auto sequence1 = Sequence::create(showBeginItem, nullptr);         // sprite1 ֱ�ӽ���
    auto sequence2 = Sequence::create(delay1, showLoadItem, nullptr);  // sprite2 �ڵȴ� 1 �����
    auto sequence3 = Sequence::create(delay1, delay2, showCoopItem, nullptr); // sprite3 �ڵȴ� 2 �����
    auto sequence4 = Sequence::create(delay1, delay2, delay3, showCloseItem, nullptr); // sprite3 �ڵȴ� 3 �����

    BeginItem->runAction(sequence1->clone());
    LoadItem->runAction(sequence2->clone());
    coopItem->runAction(sequence3->clone());
    closeItem->runAction(sequence4->clone());

    // �����˵�  
    auto menu = Menu::create(BeginItem, LoadItem, coopItem, closeItem, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // �����������  
    addMouseListener(BeginItem, LoadItem, coopItem, closeItem);

    return true;
}

MenuItemImage* GameBegin::createMenuItem(const std::string& normalImage, const std::string& selectedImage, const ccMenuCallback& callback, const Vec2& origin, float offsetX)
{
    auto item = MenuItemImage::create(normalImage, selectedImage, callback);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    if (item) {
        Size itemSize = item->getContentSize();
        // ��ȡ��Ļ��������Ĵ�С
        auto visibleSize = Director::getInstance()->getVisibleSize();
        // ����ͼ������ű���
        float maxWidth = visibleSize.width * 0.2f;
        float maxHeight = visibleSize.height * 0.2f;
        float scaleX = maxWidth / itemSize.width ;
        float scaleY = maxHeight / itemSize.height ;
        // ʹ�� setScale ������ͼƬ
        item->setScale(std::min(scaleX, scaleY));  // ���ֿ�߱�
        float x = origin.x + visibleSize.width / 2 + offsetX;
        float y = origin.y + visibleSize.height / 720 * 100;
        item->setPosition(Vec2(x, y));
        item->setOpacity(0);//��ʼ͸��
    }
    else {
        problemLoading(normalImage.c_str());
    }
    return item;
}

void GameBegin::addBackground(const Size& visibleSize, const Vec2& origin)
{
    auto background = Sprite::create("UIresource/background2.png");
    if (background) {
        float scaleX = visibleSize.width / background->getContentSize().width;
        float scaleY = visibleSize.height / background->getContentSize().height;
        float scaleFactor = std::max(scaleX, scaleY);
        background->setScale(scaleFactor);
        background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        this->addChild(background, 0);
    }
    else {
        problemLoading("'Cloudy_Ocean.png'");
    }
}

void GameBegin::addLogo(const Size& visibleSize, const Vec2& origin)
{
    auto logo = Sprite::create("UIresource/title.png");
    if (logo) {
        Size logoSize = logo->getContentSize();
        float maxWidth = visibleSize.width * 0.7f;
        float maxHeight = visibleSize.height * 0.7f;
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
    Size itemSize = item->getContentSize();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    // ����ͼ������ű���
    float maxWidth = visibleSize.width * 0.2f;
    float maxHeight = visibleSize.height * 0.2f;
    float scaleX = maxWidth / itemSize.width;
    float scaleY = maxHeight / itemSize.height;

    if (item->getBoundingBox().containsPoint(mousePos)) {
        item->setNormalImage(cocos2d::Sprite::create(selectedImage));
        item->setSelectedImage(cocos2d::Sprite::create(selectedImage));
        item->setScale(1.2* std::min(scaleX, scaleY));
    }
    else {
        item->setNormalImage(cocos2d::Sprite::create(normalImage));
        item->setSelectedImage(cocos2d::Sprite::create(normalImage));
        item->setScale(std::min(scaleX, scaleY));
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