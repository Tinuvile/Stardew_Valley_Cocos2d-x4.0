// InventoryUI.cpp  
#include "intimacyUI.h"  
#include "ui/CocosGUI.h"  
#include "Item.h"  
#include "AppDelegate.h"

extern Player* player1;
extern Inventory* inventory;

USING_NS_CC;
static void problemLoading ( const char* filename )
{
    printf ( "Error while loading: %s\n" , filename );
    printf ( "Depending on how you compiled you might have to add 'Resources/' in front of filenames in CreateCharacterScene.cpp\n" );
}
void intimacyUI::backgroundcreate () {
    CCLOG ( "yes" );
    Vec2 position = player1->getPosition ();
    CCLOG ( "X%f Y%f" , position.x , position.y );
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    // ����һ����͸���ĺ�ɫ����
    auto darkLayer = cocos2d::LayerColor::create ( cocos2d::Color4B ( 0 , 0 , 0 , 120 ) , 5 * visibleSize.width , 5 * visibleSize.height );  // ��ɫ��͸����Ϊ120
    darkLayer->setPosition ( position - visibleSize / 2 );// �������ֲ��λ��
    this->addChild ( darkLayer , 0 );
    auto IntimacyFace = Sprite::create ( "UIresource/qinmidu/intimacy.png" );
    IntimacyFace->setTag ( 101 );
    if (IntimacyFace == nullptr)
    {
        problemLoading ( "'intimacy.png'" );
    }
    else
    {
        // ��ȡԭʼͼƬ�Ŀ��
        float originalWidth = IntimacyFace->getContentSize ().width;
        float originalHeight = IntimacyFace->getContentSize ().height;
        // ������Ļ��Ⱥ�ͼƬԭʼ��߼������
        float scaleX = visibleSize.width / originalWidth;
        float scaleY = visibleSize.height / originalHeight;
        // ѡ����С�����ű������Ա�֤ͼƬ��ȫ��ʾ����Ļ���Ҳ�����
        float scale = std::min ( scaleX , scaleY );
        IntimacyFace->setScale ( scale / 1.5 );
        IntimacyFace->setPosition ( position );
        this->addChild ( IntimacyFace , 15 );
    }
}

void intimacyUI::Buttons_switching () {
    Vec2 position = player1->getPosition ();
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    //ͼ����ʾ
    auto bagkey = Sprite::create ( "UIresource/beibao/bagkey.png" );
    auto Skillkey = Sprite::create ( "UIresource/beibao/Skillkey.png" );
    auto intimacykey = Sprite::create ( "UIresource/beibao/intimacykey.png" );
    if (bagkey == nullptr)
    {
        problemLoading ( "'bagkey.png'" );
    }
    else
    {
        // ��ȡԭʼͼƬ�Ŀ��
        float originalWidth = bagkey->getContentSize ().width;
        float originalHeight = bagkey->getContentSize ().height;
        // ������Ļ��Ⱥ�ͼƬԭʼ��߼������
        float scaleX = visibleSize.width / originalWidth;
        float scaleY = visibleSize.height / originalHeight;
        // ѡ����С�����ű������Ա�֤ͼƬ��ȫ��ʾ����Ļ���Ҳ�����
        float scale = std::min ( scaleX , scaleY );
        bagkey->setScale ( scale / 16.5 );
        bagkey->setPosition ( Vec2 ( position.x - visibleSize.width * 0.25 , position.y + visibleSize.height * 0.315 ) );//0.305��ѡ��ʱλ��
        Skillkey->setScale ( scale / 16.5 );
        Skillkey->setPosition ( Vec2 ( position.x - visibleSize.width * 0.19 , position.y + visibleSize.height * 0.315 ) );//0.315��δѡ��ʱλ��
        intimacykey->setScale ( scale / 16.5 );
        intimacykey->setPosition ( Vec2 ( position.x - visibleSize.width * 0.13 , position.y + visibleSize.height * 0.305 ) );//0.315��δѡ��ʱλ��
        this->addChild ( bagkey , 1 );
        this->addChild ( Skillkey , 1 );
        this->addChild ( intimacykey , 1 );
    }

    //�����Լ��л�Layer
    auto listener = EventListenerMouse::create ();
    listener->onMouseDown = [this , bagkey , Skillkey , intimacykey]( EventMouse* event ) {
        Vec2 mousePos = Vec2 ( event->getCursorX () , event->getCursorY () );
        mousePos = this->convertToNodeSpace ( mousePos );
        //CCLOG ( "X:%f,Y:%f" , event->getCursorX () , event->getCursorY () );
        if (bagkey->getBoundingBox ().containsPoint ( mousePos )) {
            // �Ƴ���ǰ��Layer
            this->removeFromParent ();
            Director::getInstance ()->getRunningScene ()->addChild ( InventoryUI::create ( inventory ) , 10 );
        }
        else if (Skillkey->getBoundingBox ().containsPoint ( mousePos )) {

        }
        else if (intimacykey->getBoundingBox ().containsPoint ( mousePos )) {
            // �Ƴ���ǰ��Layer
            this->removeFromParent ();
            Director::getInstance ()->getRunningScene ()->addChild ( intimacyUI::create () , 10 );
        }
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority ( listener , this );
}
bool intimacyUI::init () {
    if (!Layer::init ()) {
        return false;
    }
    backgroundcreate ();
    Buttons_switching ();
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


void intimacyUI::onItemSlotClicked ( cocos2d::Ref* sender ) {

}