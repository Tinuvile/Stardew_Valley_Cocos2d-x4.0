 #include "ui/CocosGUI.h"  
#include "mailBoxUI.h"

USING_NS_CC;

static void problemLoading ( const char* filename )
{
    printf ( "Error while loading: %s\n" , filename );
    printf ( "Depending on how you compiled you might have to add 'Resources/' in front of filenames in CreateCharacterScene.cpp\n" );
}

void mailBoxUI::updateCoordinate ( float& x , float& y ) {
    Vec2 position = player1->getPosition ();
    float  Leftboundary = -10000.0f , rightboundary = 10000.0f , upperboundary = 10000.0f , lowerboundary = 10000.0f;
    Leftboundary = 637.0f;
    rightboundary = 960.0f;
    upperboundary = 777.0f;
    lowerboundary = 500.0f;
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

void mailBoxUI::backgroundcreate () {
    Vec2 position = player1->getPosition ();
    float currentx = position.x , currenty = position.y;
    updateCoordinate ( currentx , currenty );
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    // 创建一个半透明的黑色遮罩
    auto darkLayer = cocos2d::LayerColor::create ( cocos2d::Color4B ( 0 , 0 , 0 , 120 ) , 10 * visibleSize.width , 5 * visibleSize.height );  // 黑色，透明度为120
    darkLayer->setPosition ( Vec2 ( currentx , currenty ) - visibleSize / 2 );// 设置遮罩层的位置
    this->addChild ( darkLayer , 0 );
    //大框架
    auto mail = Sprite::create ( "UIresource/xinxiang/renwu2.png" );
    if (mail == nullptr)
    {
        problemLoading ( "'renwu2.png'" );
    }
    else
    {
        // 获取原始图片的宽高
        float originalWidth = mail->getContentSize ().width;
        float originalHeight = mail->getContentSize ().height;
        // 根据屏幕宽度和图片原始宽高计算比例
        float scaleX = visibleSize.width / originalWidth;
        float scaleY = visibleSize.height / originalHeight;
        // 选择最小的缩放比例，以保证图片完全显示在屏幕上且不变形
        float scale = std::min ( scaleX , scaleY );
        mail->setScale ( scale);
        mail->setPosition ( Vec2 ( currentx , currenty ) );

        this->addChild ( mail , 1 );
    }
}

void mailBoxUI::close () {
    Vec2 position = player1->getPosition ();
    float currentx = position.x , currenty = position.y;
    updateCoordinate ( currentx , currenty );
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    auto closeIcon = Sprite::create ( "npc/bacha.png" );
    if (closeIcon == nullptr)
    {
        problemLoading ( "'npc/bacha.png'" );
    }
    else
    {
        float originalWidth = closeIcon->getContentSize ().width;
        float originalHeight = closeIcon->getContentSize ().height;
        float scaleX = visibleSize.width / originalWidth;
        float scaleY = visibleSize.height / originalHeight;
        float scale = std::min ( scaleX , scaleY );
        closeIcon->setScale ( scale / 20.5 );
        closeIcon->setPosition ( Vec2 ( currentx + visibleSize.width * 0.45 , currenty + visibleSize.height * 0.4 ) );

        this->addChild ( closeIcon , 1 );
        auto listener = EventListenerMouse::create ();
        listener->onMouseMove = [this , closeIcon , scale]( EventMouse* event ) {
            Vec2 mousePos = Vec2 ( event->getCursorX () , event->getCursorY () );
            mousePos = this->convertToNodeSpace ( mousePos );
            if (closeIcon->getBoundingBox ().containsPoint ( mousePos ))
            {
                closeIcon->setScale ( scale / 20.5 * 1.2 );
            }
            else
                closeIcon->setScale ( scale / 20.5 );
            };
        listener->onMouseDown = [this , closeIcon]( EventMouse* event ) {
            Vec2 mousePos = Vec2 ( event->getCursorX () , event->getCursorY () );
            mousePos = this->convertToNodeSpace ( mousePos );
            CCLOG ( "%f %f" , mousePos.x , mousePos.y );
            if (closeIcon->getBoundingBox ().containsPoint ( mousePos )) {
                this->removeFromParent ();
            }
            };
        _eventDispatcher->addEventListenerWithSceneGraphPriority ( listener , closeIcon );
    }
}

bool mailBoxUI::init () {
    if (!Layer::init ()) {
        return false;
    }
    backgroundcreate ();

    close ();
    return true;
}

mailBoxUI* mailBoxUI::create () {
    mailBoxUI* ret = new mailBoxUI ();
    if (ret && ret->init ()) {
        ret->autorelease ();
        return ret;
    }
    CC_SAFE_DELETE ( ret );
    return nullptr;
}

