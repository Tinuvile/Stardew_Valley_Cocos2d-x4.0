#include "ui/CocosGUI.h"  
#include "quitUI.h"

USING_NS_CC;

static void problemLoading ( const char* filename )
{
    printf ( "Error while loading: %s\n" , filename );
    printf ( "Depending on how you compiled you might have to add 'Resources/' in front of filenames in CreateCharacterScene.cpp\n" );
}

void quitUI::updateCoordinate ( float& x , float& y ) {
    Vec2 position = player1->getPosition ();
    float  Leftboundary = -10000.0f , rightboundary = 10000.0f , upperboundary = 10000.0f , lowerboundary = 10000.0f;
    if (SceneName == "Town") {
        Leftboundary = -170.0f;
        rightboundary = 1773.0f;
        upperboundary = 1498.0f;
        lowerboundary = -222.0f;
    }
    else if (SceneName == "Cave") {
        Leftboundary = 786.0f;
        rightboundary = 817.0f;
        upperboundary = 808.0f;
        lowerboundary = 460.0f;
    }
    else if (SceneName == "Beach") {
        Leftboundary = -315.0f;
        rightboundary = 20000.0f;
        upperboundary = 920.0f;
        lowerboundary = 360.0f;
    }
    else if (SceneName == "Forest") {
        Leftboundary = -600.0f;
        rightboundary = 2197.0f;
        upperboundary = 2200.0f;
        lowerboundary = -850.0f;
    }
    else if (SceneName == "farm") {
        Leftboundary = 637.0f;
        rightboundary = 960.0f;
        upperboundary = 777.0f;
        lowerboundary = 500.0f;
    }
    else if (SceneName == "Barn") {
        Leftboundary = 805.0f;
        rightboundary = 805.0f;
        upperboundary = 569.0f;
        lowerboundary = 569.0f;
    }
    else if (SceneName == "Myhouse") {
        Leftboundary = 800.0f;
        rightboundary = 800.0f;
        upperboundary = 580.0f;
        lowerboundary = 580.0f;
    }
    if (x <= Leftboundary) {
        x = Leftboundary;
    }
    else if (x >= rightboundary) {
        x = rightboundary;
    }
    else {
        x = position.x;
    }

    if (y >= upperboundary) {
        y = upperboundary;
    }
    else if (y <= lowerboundary) {
        y = lowerboundary;
    }
    else {
        y = position.y;
    }
}

void quitUI::backgroundcreate () {
    Vec2 position = player1->getPosition ();
    float currentx = position.x , currenty = position.y;
    updateCoordinate ( currentx , currenty );
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    // 创建一个半透明的黑色遮罩
    auto darkLayer = cocos2d::LayerColor::create ( cocos2d::Color4B ( 0 , 0 , 0 , 120 ) , 10 * visibleSize.width , 5 * visibleSize.height );  // 黑色，透明度为120
    darkLayer->setPosition ( Vec2 ( currentx , currenty ) - visibleSize );// 设置遮罩层的位置
    this->addChild ( darkLayer , 0 );
    //大框架
    auto quitFace = Sprite::create ( "UIresource/SkillTree/background.png" );
    if (quitFace == nullptr)
    {
        problemLoading ( "'background.png'" );
    }
    else
    {
        // 获取原始图片的宽高
        float originalWidth = quitFace->getContentSize ().width;
        float originalHeight = quitFace->getContentSize ().height;
        // 根据屏幕宽度和图片原始宽高计算比例
        float scaleX = visibleSize.width / originalWidth;
        float scaleY = visibleSize.height / originalHeight;
        // 选择最小的缩放比例，以保证图片完全显示在屏幕上且不变形
        float scale = std::min ( scaleX , scaleY );
        quitFace->setScale ( scale / 1.5 );
        quitFace->setPosition ( Vec2 ( currentx , currenty ) );

        this->addChild ( quitFace , 1 );
    }
}

void quitUI::Buttons_switching () {
    Vec2 position = player1->getPosition ();
    float currentx = position.x , currenty = position.y;
    updateCoordinate ( currentx , currenty );
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    //图标显示
    auto bagkey = Sprite::create ( "UIresource/beibao/bagkey.png" );
    auto Skillkey = Sprite::create ( "UIresource/beibao/Skillkey.png" );
    auto intimacykey = Sprite::create ( "UIresource/beibao/intimacykey.png" );
    auto quitkey = Sprite::create ( "UIresource/beibao/quit.png" );
    if (bagkey == nullptr)
    {
        problemLoading ( "'bagkey.png'" );
    }
    else
    {
        // 获取原始图片的宽高
        float originalWidth = bagkey->getContentSize ().width;
        float originalHeight = bagkey->getContentSize ().height;
        // 根据屏幕宽度和图片原始宽高计算比例
        float scaleX = visibleSize.width / originalWidth;
        float scaleY = visibleSize.height / originalHeight;
        // 选择最小的缩放比例，以保证图片完全显示在屏幕上且不变形
        float scale = std::min ( scaleX , scaleY );
        bagkey->setScale ( scale / 16.5 );
        bagkey->setPosition ( Vec2 ( currentx - visibleSize.width * 0.25 , currenty + visibleSize.height * 0.315 ) );//0.305是选中时位置
        Skillkey->setScale ( scale / 16.5 );
        Skillkey->setPosition ( Vec2 ( currentx - visibleSize.width * 0.19 , currenty + visibleSize.height * 0.315 ) );//0.315是未选中时位置
        intimacykey->setScale ( scale / 16.5 );
        intimacykey->setPosition ( Vec2 ( currentx - visibleSize.width * 0.13 , currenty + visibleSize.height * 0.315 ) );
        quitkey->setScale ( scale / 16.5 );
        quitkey->setPosition ( Vec2 ( currentx - visibleSize.width * 0.07 , currenty + visibleSize.height * 0.305 ) );
        this->addChild ( bagkey , 2 );
        this->addChild ( Skillkey , 2 );
        this->addChild ( intimacykey , 2 );
        this->addChild ( quitkey , 2 );
    }

    //动画以及切换Layer
    auto listener = EventListenerMouse::create ();
    listener->onMouseDown = [this , bagkey , Skillkey , intimacykey , quitkey]( EventMouse* event ) {
        Vec2 mousePos = Vec2 ( event->getCursorX () , event->getCursorY () );
        mousePos = this->convertToNodeSpace ( mousePos );
        //CCLOG ( "X:%f,Y:%f" , event->getCursorX () , event->getCursorY () );
        if (bagkey->getBoundingBox ().containsPoint ( mousePos )) {
            // 移除当前的Layer
            std::string nowScene = SceneName;
            this->removeFromParent ();
            Director::getInstance ()->getRunningScene ()->addChild ( InventoryUI::create ( inventory , nowScene ) , 20 );
        }
        else if (Skillkey->getBoundingBox ().containsPoint ( mousePos )) {
            std::string nowScene = SceneName;
            this->removeFromParent ();
            Director::getInstance ()->getRunningScene ()->addChild ( SkillTreeUI::create ( nowScene ) , 20 );
        }
        else if (intimacykey->getBoundingBox ().containsPoint ( mousePos )) {
            std::string nowScene = SceneName;
            this->removeFromParent ();
            Director::getInstance ()->getRunningScene ()->addChild ( intimacyUI::create ( nowScene ) , 20 );
        }
        else if (quitkey->getBoundingBox ().containsPoint ( mousePos )) {
        }
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority ( listener , this );
}

void quitUI::quitAndsetting () {
    Vec2 position = player1->getPosition ();
    float currentx = position.x , currenty = position.y;
    updateCoordinate ( currentx , currenty );
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    auto quit = Sprite::create ( "UIresource/quit.png" );
    if (quit == nullptr)
    {
        problemLoading ( "'quit.png'" );
    }
    else
    {
        // 获取原始图片的宽高
        float originalWidth = quit->getContentSize ().width;
        float originalHeight = quit->getContentSize ().height;
        // 根据屏幕宽度和图片原始宽高计算比例
        float scaleX = visibleSize.width / originalWidth;
        float scaleY = visibleSize.height / originalHeight;
        // 选择最小的缩放比例，以保证图片完全显示在屏幕上且不变形
        float scale = std::min ( scaleX , scaleY );
        quit->setScale ( scale / 5.5 );
        quit->setPosition ( Vec2 ( currentx , currenty ) );

        this->addChild ( quit , 1 );

        auto listener = EventListenerMouse::create ();
        listener->onMouseMove = [this , quit , scale]( EventMouse* event ) {
            Vec2 mousePos = Vec2 ( event->getCursorX () , event->getCursorY () );
            mousePos = this->convertToNodeSpace ( mousePos );
            if (quit->getBoundingBox ().containsPoint ( mousePos )) {
                quit->setScale ( scale / 5.5 * 1.2f );
            }
            else
                quit->setScale ( scale / 5.5 );
            };
        listener->onMouseDown = [this , quit]( EventMouse* event ) {
            Vec2 mousePos = Vec2 ( event->getCursorX () , event->getCursorY () );
            mousePos = this->convertToNodeSpace ( mousePos );
            if (quit->getBoundingBox ().containsPoint ( mousePos )) {
                Director::getInstance ()->end ();
            }
            };
        _eventDispatcher->addEventListenerWithSceneGraphPriority ( listener , quit );
    }
}

void quitUI::close () {
    // 设置键盘监听器  
    auto listenerClose = EventListenerKeyboard::create ();
    listenerClose->onKeyPressed = [this]( EventKeyboard::KeyCode keyCode , Event* event ) {
        if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
            this->removeFromParent ();
        }
        };
    // 将监听器添加到事件分发器中  
    _eventDispatcher->addEventListenerWithSceneGraphPriority ( listenerClose , this );
}

bool quitUI::init ( std::string sceneName ) {
    if (!Layer::init ()) {
        return false;
    }
    SceneName = sceneName;
    backgroundcreate ();
    quitAndsetting ();
    Buttons_switching ();
    close ();
    return true;
}

quitUI* quitUI::create ( std::string sceneName ) {
    quitUI* ret = new quitUI ();
    if (ret && ret->init ( sceneName )) {
        ret->autorelease ();
        return ret;
    }
    CC_SAFE_DELETE ( ret );
    return nullptr;
}