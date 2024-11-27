/*
��UI������ͼ��ͬѧ�����޸�һ��GameBeginUI.cpp�ļ�200�еĳ�����ת����GameBegin::menuNewCallback(Ref* pSender)
*/


#include "GameBeginUI.h"
#include "CreateCharacterUI.h"
#include "Player.h"

USING_NS_CC;

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

// on "init" you need to initialize your instance
bool GameBegin::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto GameBegin = MenuItemImage::create(
        // ��ʱ����ͼ@̷����
        "Stardew Valley Unpacked Resources/LooseSprites/JunimoNoteMobile.png",
        "Stardew Valley Unpacked Resources/LooseSprites/JunimoNoteMobile.png",
        CC_CALLBACK_1(GameBegin::menuNewCallback, this));

    if (GameBegin == nullptr ||
        GameBegin->getContentSize().width <= 0 ||
        GameBegin->getContentSize().height <= 0)
    {
        problemLoading("'JunimoNoteMobile.png' and 'CloseSelected.png'");
    }
    else
    {
        // ��������ɸ��ݴ��ڴ�С��Ӧ����
        float scaleFactor = 0.6f;  // ����ͼ������ű���
        GameBegin->setScale(scaleFactor); // ��������

        float x = origin.x + (visibleSize.width - GameBegin->getContentSize().width * 2) / 3 + GameBegin->getContentSize().width / 2;
        float y = origin.y + GameBegin->getContentSize().height;
        GameBegin->setPosition(Vec2(x, y));
    }

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
        // ����һ��@̷����
        "Stardew Valley Unpacked Resources/LooseSprites/JunimoNoteMobile.png",
        "Stardew Valley Unpacked Resources/LooseSprites/JunimoNoteMobile.png",
        CC_CALLBACK_1(GameBegin::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'JunimoNoteMobile.png' and 'CloseSelected.png'");
    }
    else
    { 
        float scaleFactor = 0.6f;  // ����ͼ������ű���
        closeItem->setScale(scaleFactor); // ��������

        float x = origin.x + visibleSize.width - 
            (visibleSize.width - closeItem->getContentSize().width * 2) / 3 - GameBegin->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height;
        closeItem->setPosition(Vec2(x, y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(GameBegin, closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    // ����Ҳ�����о���һ��ʲô��@̷����
    auto NEW = Label::createWithTTF("NEW", "fonts/Marker Felt.ttf", 24);
    if (NEW == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the NEW on the center of the screen
        NEW->setPosition(Vec2(origin.x + (visibleSize.width - GameBegin->getContentSize().width * 2) / 3 
            + GameBegin->getContentSize().width / 2,
            origin.y + GameBegin->getContentSize().height));

        // add the NEW as a child to this layer
        this->addChild(NEW, 1);
    }

    auto EXIT = Label::createWithTTF("EXIT", "fonts/Marker Felt.ttf", 24);
    if (EXIT == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the EXIT on the center of the screen
        EXIT->setPosition(Vec2(origin.x + visibleSize.width -
            (visibleSize.width - closeItem->getContentSize().width * 2) / 3 - GameBegin->getContentSize().width / 2,
            origin.y + closeItem->getContentSize().height));

        // add the EXIT as a child to this layer
        this->addChild(EXIT, 1);
    }

    // add "GameBegin" splash screen"
    // ����·����build�ļ�����Resource��һ�㿪ʼ��ע��б�ܷ���
    auto background = Sprite::create("Stardew Valley Unpacked Resources/LooseSprites/stardewPanorama.png");
    if (background == nullptr)
    {
        problemLoading("'stardewPanorama.png'");
    }
    else
    {
        // ��ȡ���ڵĿ��Ӵ�С  
        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();

        // ������������ű���  
        float scaleX = visibleSize.width / background->getContentSize().width;
        float scaleY = visibleSize.height / background->getContentSize().height;

        // ѡ��ϴ���������ӽ��зŴ���ȷ������������ڣ�  
        float scaleFactor = std::max(scaleX, scaleY);
        background->setScale(scaleFactor);

        // position the background on the center of the screen
        background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        // add the background as a child to this layer
        this->addChild(background, 0);
    }

    auto Stardew_Valley_logo = Sprite::create("Stardew Valley Unpacked Resources/LooseSprites/logo.png");
    if (Stardew_Valley_logo == nullptr)
    {
        problemLoading("'stardewPanorama.png'");
    }
    else
    {
        // position the Stardew_Valley_logo on the center of the screen
        Stardew_Valley_logo->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 4 * 3 + origin.y));

        // add the Stardew_Valley_logo as a child to this layer
        this->addChild(Stardew_Valley_logo, 1);
    }

    auto listener = EventListenerMouse::create();
    listener->onMouseMove = [this, GameBegin, closeItem](EventMouse* event) {
        Vec2 mousePos = Vec2(event->getCursorX(), event->getCursorY());

        if (GameBegin->getBoundingBox().containsPoint(mousePos))
        {
            GameBegin->setScale(0.7f); // �����ͣ�Ŵ�  
        }
        else
        {
            GameBegin->setScale(0.6f); // �ָ�ԭ��С  
        }

        if (closeItem->getBoundingBox().containsPoint(mousePos))
        {
            closeItem->setScale(0.7f); // �����ͣ�Ŵ�  
        }
        else
        {
            closeItem->setScale(0.6f); // �ָ�ԭ��С  
        }
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

// ��ת���³���  
void GameBegin::menuNewCallback(Ref* pSender)
{
    // Director::getInstance()->replaceScene(CreateCharacter::createScene()); // ��ת�� CreateCharacterUI ����@̷
    // Director::getInstance()->replaceScene(myhouse::create()); // ���뵽����ͼ
}

void GameBegin::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}