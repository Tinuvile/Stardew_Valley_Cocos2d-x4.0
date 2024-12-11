// NPCtalk.cpp  
#include "NPCtalk.h"  
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

// 底层图片
void NPCtalk::backgroundcreate () {
    // 获取可视区域的大小  
    auto visibleSize = Director::getInstance ()->getVisibleSize ();

    Vec2 position = player1->getPosition ();

    auto darkLayer = cocos2d::LayerColor::create ( cocos2d::Color4B ( 0 , 0 , 0 , 120 ) , 5 * visibleSize.width , 5 * visibleSize.height );  // 黑色，透明度为120
    darkLayer->setPosition ( position - visibleSize / 2 );// 设置遮罩层的位置
    this->addChild ( darkLayer , 0 );

    // 创建背景精灵  
    auto background = Sprite::create ( "npc/kuang.png" );
    background->setTag ( 101 );

    if (background == nullptr) {
        problemLoading ( "'kuang.png'" );
    }
    else {
        // 获取原始图片的宽高  
        float originalWidth = background->getContentSize ().width;
        float originalHeight = background->getContentSize ().height;

        // 根据屏幕宽度和图片原始宽高计算比例  
        float scaleX = visibleSize.width / originalWidth;
        float scaleY = visibleSize.height / originalHeight;

        // 选择最小的缩放比例，以保证图片完全显示在屏幕上且不变形  
        float scale = std::min ( scaleX , scaleY );
        background->setScale ( scale / 1.5 );

        // 设置背景位置为屏幕底部  
        background->setPosition ( Vec2 ( position.x , position.y - visibleSize.height / 3.4 ) ); // Y坐标调整为背景高度的1/2，确保底部对齐  

        // 添加背景到当前层  
        this->addChild ( background , 0 );
    }
}

// 初始化
bool NPCtalk::init ( Inventory* inventory , NPC* npc_name ) {
    if (!Layer::init ()) {
        return false;
    }

    // 初始化成员变量  
    _inventory = inventory;
    _npc = npc_name;

    backgroundcreate ();

    return true;
}

NPCtalk* NPCtalk::create ( Inventory* inventory , NPC* npc_name ) {
    NPCtalk* ret = new NPCtalk ();
    if (ret && ret->init ( inventory , npc_name )) {
        ret->autorelease ();
        return ret;
    }
    CC_SAFE_DELETE ( ret );
    return nullptr;
}