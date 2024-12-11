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

// �ײ�ͼƬ
void NPCtalk::backgroundcreate () {
    // ��ȡ��������Ĵ�С  
    auto visibleSize = Director::getInstance ()->getVisibleSize ();

    Vec2 position = player1->getPosition ();

    auto darkLayer = cocos2d::LayerColor::create ( cocos2d::Color4B ( 0 , 0 , 0 , 120 ) , 5 * visibleSize.width , 5 * visibleSize.height );  // ��ɫ��͸����Ϊ120
    darkLayer->setPosition ( position - visibleSize / 2 );// �������ֲ��λ��
    this->addChild ( darkLayer , 0 );

    // ������������  
    auto background = Sprite::create ( "npc/kuang.png" );
    background->setTag ( 101 );

    if (background == nullptr) {
        problemLoading ( "'kuang.png'" );
    }
    else {
        // ��ȡԭʼͼƬ�Ŀ��  
        float originalWidth = background->getContentSize ().width;
        float originalHeight = background->getContentSize ().height;

        // ������Ļ��Ⱥ�ͼƬԭʼ��߼������  
        float scaleX = visibleSize.width / originalWidth;
        float scaleY = visibleSize.height / originalHeight;

        // ѡ����С�����ű������Ա�֤ͼƬ��ȫ��ʾ����Ļ���Ҳ�����  
        float scale = std::min ( scaleX , scaleY );
        background->setScale ( scale / 1.5 );

        // ���ñ���λ��Ϊ��Ļ�ײ�  
        background->setPosition ( Vec2 ( position.x , position.y - visibleSize.height / 3.4 ) ); // Y�������Ϊ�����߶ȵ�1/2��ȷ���ײ�����  

        // ��ӱ�������ǰ��  
        this->addChild ( background , 0 );
    }
}

// ��ʼ��
bool NPCtalk::init ( Inventory* inventory , NPC* npc_name ) {
    if (!Layer::init ()) {
        return false;
    }

    // ��ʼ����Ա����  
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