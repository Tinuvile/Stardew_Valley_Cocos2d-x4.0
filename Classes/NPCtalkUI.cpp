// InventoryUI.cpp  
#include "NPCtalkUI.h"  
#include "ui/CocosGUI.h"  
#include "Item.h"  
#include "AppDelegate.h"

extern Player* player1;

USING_NS_CC;

static void problemLoading ( const char* filename )
{
    printf ( "Error while loading: %s\n" , filename );
    printf ( "Depending on how you compiled you might have to add 'Resources/' in front of filenames in CreateCharacterScene.cpp\n" );
}

void NPCtalkUI::backgroundcreate () {
    Vec2 position = player1->getPosition ();
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    // 创建一个半透明的黑色遮罩
    auto darkLayer = cocos2d::LayerColor::create ( cocos2d::Color4B ( 0 , 0 , 0 , 120 ) , 5 * visibleSize.width , 5 * visibleSize.height );  // 黑色，透明度为120
    darkLayer->setPosition ( position - visibleSize / 2 );// 设置遮罩层的位置
    this->addChild ( darkLayer , 0 );
    auto dialogBox = Sprite::create ( "npc/kuang.png" );
    if (dialogBox == nullptr)
    {
        problemLoading ( "'npc/kuang.png'" );
    }
    else
    {
        float originalWidth = dialogBox->getContentSize ().width;
        float originalHeight = dialogBox->getContentSize ().height;
        float scaleX = visibleSize.width / originalWidth;
        float scaleY = visibleSize.height / originalHeight;
        float scale = std::min ( scaleX , scaleY );
        dialogBox->setScale ( scale * 0.9 );
        dialogBox->setPosition ( Vec2 ( position.x , position.y - visibleSize.height * 0.27 ) );

        this->addChild ( dialogBox , 1 );
    }
}

void NPCtalkUI::close () {
    Vec2 position = player1->getPosition ();
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
        closeIcon->setPosition ( Vec2 ( position.x + visibleSize.width * 0.0644 , position.y - visibleSize.height * 0.409 ) );

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

bool NPCtalkUI::init () {
    if (!Layer::init ()) {
        return false;
    }
    backgroundcreate ();
    close ();
    return true;
}

NPCtalkUI* NPCtalkUI::create () {
    NPCtalkUI* ret = new NPCtalkUI ();
    if (ret && ret->init ()) {
        ret->autorelease ();
        return ret;
    }
    CC_SAFE_DELETE ( ret );
    return nullptr;
}
