// InventoryUI.cpp  
#include "intimacyUI.h"  
#include "ui/CocosGUI.h"  
#include "Item.h"  

extern Player* player1;
extern Inventory* inventory;

const int characternum = 5;

USING_NS_CC;

static void problemLoading ( const char* filename )
{
    printf ( "Error while loading: %s\n" , filename );
    printf ( "Depending on how you compiled you might have to add 'Resources/' in front of filenames in CreateCharacterScene.cpp\n" );
}

void intimacyUI::updateCoordinate ( float& x , float& y ) {
    Vec2 position = player1->getPosition ();
    if (x <= -117) {
        x = -117;
    }
    else if (x >= 1773) {
        x = 1773;
    }
    else {
        x = position.x;
    }

    if (y >= 1498) {
        y = 1498;
    }
    else if (y <= -222) {
        y = -222;
    }
    else {
        y = position.y;
    }
}

void intimacyUI::backgroundcreate () {
    Vec2 position = player1->getPosition ();
    float currentx = position.x , currenty = position.y;
    updateCoordinate ( currentx , currenty );
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    // 创建一个半透明的黑色遮罩
    auto darkLayer = cocos2d::LayerColor::create ( cocos2d::Color4B ( 0 , 0 , 0 , 120 ) , 5 * visibleSize.width , 5 * visibleSize.height );  // 黑色，透明度为120
    darkLayer->setPosition ( Vec2 ( currentx , currenty ) - visibleSize / 2 );// 设置遮罩层的位置
    this->addChild ( darkLayer , 0 );
    //大框架
    auto IntimacyFace = Sprite::create ( "UIresource/qinmidu/intimacyDisplay.png" );
    IntimacyFace->setTag ( 101 );
    if (IntimacyFace == nullptr)
    {
        problemLoading ( "'intimacyDisplay.png'" );
    }
    else
    {
        // 获取原始图片的宽高
        float originalWidth = IntimacyFace->getContentSize ().width;
        float originalHeight = IntimacyFace->getContentSize ().height;
        // 根据屏幕宽度和图片原始宽高计算比例
        float scaleX = visibleSize.width / originalWidth;
        float scaleY = visibleSize.height / originalHeight;
        // 选择最小的缩放比例，以保证图片完全显示在屏幕上且不变形
        float scale = std::min ( scaleX , scaleY );
        IntimacyFace->setScale ( scale / 1.5 );
        IntimacyFace->setPosition ( Vec2 ( currentx , currenty + 13 ) );
       
        this->addChild ( IntimacyFace , 1 );
        for (int i = 0; i < characternum; i++) {
            auto oneframe = Sprite::create ( "UIresource/qinmidu/weixuanzhong.png" );
            oneframe->setTag ( i + 1 );
            float originalframeHeight = oneframe->getContentSize ().height;
            oneframe->setScale ( scale / 1.5 );
            oneframe->setPosition ( currentx - 2 , currenty + 280 - i * (originalframeHeight * scale / 1.5 + 12) );
            oneframe->setTag ( i + 1 );
            this->addChild ( oneframe , 2 );
            auto listener = EventListenerMouse::create ();
            listener->onMouseMove = [this , oneframe]( EventMouse* event ) {
                Vec2 mousePos = Vec2 ( event->getCursorX () , event->getCursorY () );
                mousePos = this->convertToNodeSpace ( mousePos );
                if (oneframe->getBoundingBox ().containsPoint ( mousePos ))
                    oneframe->setTexture ( "UIresource/qinmidu/xuanzhong.png" );
                else
                    oneframe->setTexture ( "UIresource/qinmidu/weixuanzhong.png" );
                };
            _eventDispatcher->addEventListenerWithSceneGraphPriority ( listener , oneframe );

        }
    }
    characterInfo ( "Abigail" , "Normal" , Vec2 ( currentx - visibleSize.width * 0.27 , currenty + visibleSize.height * 0.2215 ) );
    characterInfo ( "Alex" , "Normal" , Vec2 ( currentx - visibleSize.width * 0.27 , currenty + visibleSize.height * 0.1165 ) );
    characterInfo ( "Caroline" , "Normal" , Vec2 ( currentx - visibleSize.width * 0.27 , currenty + visibleSize.height * 0.0115 ) );
    characterInfo ( "Elliott" , "Normal" , Vec2 ( currentx - visibleSize.width * 0.27 , currenty - visibleSize.height * 0.0935 ) );
    characterInfo ( "Emily" , "Normal" , Vec2 ( currentx - visibleSize.width * 0.27 , currenty - visibleSize.height * 0.1985 ) );
}

void intimacyUI::characterInfo ( const string& name , const string& status , Vec2 Pos_photo) {
    Vec2 position = player1->getPosition ();
    float currentx = position.x , currenty = position.y;
    updateCoordinate ( currentx , currenty );
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    //人物头像
    std::string photo = getNPCportraits ( name , status );
    auto characterPhoto = Sprite::create ( photo );
    cocos2d::log("%s", photo.c_str());
    if (characterPhoto == NULL) {
        cocos2d::log("failed");
    }
    else {
        float originalWidth = characterPhoto->getContentSize().width;
        float originalHeight = characterPhoto->getContentSize().height;
        float scaleX = visibleSize.width / originalWidth;
        float scaleY = visibleSize.height / originalHeight;
        float scale = std::min(scaleX, scaleY);
        characterPhoto->setScale(scale * 0.1);
        characterPhoto->setPosition(Pos_photo);
        this->addChild(characterPhoto, 2);
    }
    //姓名
    auto NameLabel = Label::createWithSystemFont ( name , "fonts/Comic Sans MS.ttf" , 35 );
    NameLabel->setTextColor ( cocos2d::Color4B::BLACK );
    NameLabel->setPosition ( Vec2 ( Pos_photo.x + visibleSize.width * 0.1 , Pos_photo.y ) );
    this->addChild ( NameLabel , 2 );
}
void intimacyUI::Buttons_switching () {
    Vec2 position = player1->getPosition ();
    float currentx = position.x , currenty = position.y;
    updateCoordinate ( currentx , currenty );
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    //图标显示
    auto bagkey = Sprite::create ( "UIresource/beibao/bagkey.png" );
    auto Skillkey = Sprite::create ( "UIresource/beibao/Skillkey.png" );
    auto intimacykey = Sprite::create ( "UIresource/beibao/intimacykey.png" );
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
        intimacykey->setPosition ( Vec2 ( currentx - visibleSize.width * 0.13 , currenty + visibleSize.height * 0.305 ) );//0.315是未选中时位置
        this->addChild ( bagkey , 2 );
        this->addChild ( Skillkey , 2 );
        this->addChild ( intimacykey , 2 );
    }

    //动画以及切换Layer
    auto listener = EventListenerMouse::create ();
    listener->onMouseDown = [this , bagkey , Skillkey , intimacykey]( EventMouse* event ) {
        Vec2 mousePos = Vec2 ( event->getCursorX () , event->getCursorY () );
        mousePos = this->convertToNodeSpace ( mousePos );
        //CCLOG ( "X:%f,Y:%f" , event->getCursorX () , event->getCursorY () );
        if (bagkey->getBoundingBox ().containsPoint ( mousePos )) {
            // 移除当前的Layer
            this->removeFromParent ();
            Director::getInstance ()->getRunningScene ()->addChild ( InventoryUI::create ( inventory ) , 10 );
        }
        else if (Skillkey->getBoundingBox ().containsPoint ( mousePos )) {

        }
        else if (intimacykey->getBoundingBox ().containsPoint ( mousePos )) {
        }
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority ( listener , this );
}

void intimacyUI::close () {
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

bool intimacyUI::init () {
    if (!Layer::init ()) {
        return false;
    }
    backgroundcreate ();
    Buttons_switching ();
    close ();
    return true;
}

intimacyUI* intimacyUI::create () {
    intimacyUI* ret = new intimacyUI ();
    if (ret && ret->init ()) {
        ret->autorelease ();
        return ret;
    }
    CC_SAFE_DELETE ( ret );
    return nullptr;
}

