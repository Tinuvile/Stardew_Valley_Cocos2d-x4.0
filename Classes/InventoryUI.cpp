// InventoryUI.cpp  
#include "InventoryUI.h"  
#include "ui/CocosGUI.h"  
#include "Item.h"  

USING_NS_CC;
static void problemLoading ( const char* filename )
{
    printf ( "Error while loading: %s\n" , filename );
    printf ( "Depending on how you compiled you might have to add 'Resources/' in front of filenames in CreateCharacterScene.cpp\n" );
}
void InventoryUI::backgroundcreate(){
    // ����һ����͸���ĺ�ɫ����
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    auto darkLayer = cocos2d::LayerColor::create ( cocos2d::Color4B ( 0 , 0 , 0 , 120 ) , 5 * visibleSize.width , 5 * visibleSize.height );  // ��ɫ��͸����Ϊ180
    darkLayer->setPosition ( cocos2d::Vec2 ( -visibleSize.width / 2 , -visibleSize.height / 3 ) ); // �����������ֲ��λ��
    this->addChild ( darkLayer , 0 );
    Vec2 origin = Director::getInstance ()->getVisibleOrigin ();
    auto bag = Sprite::create ( "UIresource/beibao/bag.png" );
    bag->setTag ( 101 );
    if (bag == nullptr)
    {
        problemLoading ( "'bag.png'" );
    }
    else
    {
        // ��ȡԭʼͼƬ�Ŀ��
        float originalWidth = bag->getContentSize ().width;
        float originalHeight = bag->getContentSize ().height;

        // ������Ļ��Ⱥ�ͼƬԭʼ��߼������
        float scaleX = visibleSize.width / originalWidth;
        float scaleY = visibleSize.height / originalHeight;

        // ѡ����С�����ű������Ա�֤ͼƬ��ȫ��ʾ����Ļ���Ҳ�����
        float scale = std::min ( scaleX , scaleY );
        bag->setScale ( scale / 1.5 );
        Vec2 Pos = Vec2 ( visibleSize.width / 4.5 + origin.x , visibleSize.height / 3 + origin.y );
        bag->setPosition ( Pos );

        // add the sprite as a child to this layer
        this->addChild ( bag , 1 );
    }
}
void InventoryUI::Itemblock ( Inventory* inventory ) {
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    Vec2 origin = Director::getInstance ()->getVisibleOrigin ();
    _inventory = inventory;
    _selectedSlot = 1; // Ĭ��ѡ�е�һ����λ  

    // ��������ʼ����Ʒ��ʾ��ǩ  
    _itemLabel = Label::createWithTTF ( "" , "fonts/Marker Felt.ttf" , 20 );
    _itemLabel->setPosition ( 200 , 400 );
    this->addChild ( _itemLabel );

    // ��ʼ����Ʒ�� Sprite 
    for (int m = 0; m < 3; m++)
    {
        for (int i = 0; i < kRowSize; ++i) {
            auto slot = Sprite::create ( "UIresource/beibao/wupincao.png" );
            auto bag = getChildByTag ( 101 );
            // ��ȡԭʼͼƬ�Ŀ��
            float originalWidth = slot->getContentSize ().width;
            float originalHeight = slot->getContentSize ().height;
            // ������Ļ��Ⱥ�ͼƬԭʼ��߼������
            float scaleX = visibleSize.width / originalWidth;
            float scaleY = visibleSize.height / originalHeight;
            // ѡ����С�����ű������Ա�֤ͼƬ��ȫ��ʾ����Ļ���Ҳ�����
            float scale = std::min ( scaleX , scaleY );
            slot->setScale ( scale / 16.5 );
            float bagWidth = bag->getContentSize ().width;
            float bagHeight = bag->getContentSize ().height;
            slot->setPosition ( visibleSize.width / 4.5 + origin.x - bagWidth * 2.086 + (originalWidth * scale / 16.5 + 5) * i , visibleSize.height / 1.8 + origin.y - m * (originalHeight * scale / 16.5 + 10) ); // �����λλ��  
            slot->setTag ( i + 1 ); // ���ò�λ�ı�ǩ  
            this->addChild ( slot , 2 );
            _itemSlots.pushBack ( slot );

            // ��Ӵ����¼�  
            auto listener = EventListenerTouchOneByOne::create ();
            listener->onTouchBegan = [this , slot]( Touch* touch , Event* event ) {
                Vec2 location = touch->getLocation ();
                if (slot->getBoundingBox ().containsPoint ( location )) {
                    onItemSlotClicked ( slot );
                    return true; // ��������¼�  
                }
                return false; // ����������¼�  
                };
            _eventDispatcher->addEventListenerWithSceneGraphPriority ( listener , slot );
        }
    }
}
bool InventoryUI::init ( Inventory* inventory ) {
    if (!Layer::init ()) {
        return false;
    }
    backgroundcreate ();
    Itemblock ( inventory );
    updateDisplay (); // ������ʾ����  

    return true;
}

InventoryUI* InventoryUI::create ( Inventory* inventory ) {
    InventoryUI* ret = new InventoryUI ();
    if (ret && ret->init ( inventory )) {
        ret->autorelease ();
        return ret;
    }
    CC_SAFE_DELETE ( ret );
    return nullptr;
}

void InventoryUI::updateDisplay () {
    for (int i = 0; i < kRowSize; ++i) {
        auto slot = _itemSlots.at ( i );
        slot->setVisible ( true ); // ȷ����ʾ���в�λ  

        // ��ȡ��λ��Ʒ  
        auto item = _inventory->GetSelectedItem (); // ����ʹ�� `_inventory->package[i + 1]`  

        // ���²�λ�Ӿ�����  
        if (item) {
            // ���� Item ��һ���������Է�������ͼƬ·��  
            auto itemSprite = Sprite::create ( item->initial_pic );
            itemSprite->setPosition ( slot->getContentSize () / 2 );
            slot->addChild ( itemSprite );
        }
        else {
            slot->removeAllChildren (); // ��ղ�λ  
        }
    }
    // ������Ʒ��Ϣ��ǩ  
    if (auto selectedItem = _inventory->GetSelectedItem ()) {
        _itemLabel->setString ( "Selected: " + selectedItem->GetName () );
    }
    else {
        _itemLabel->setString ( "No item selected." );
    }
}

void InventoryUI::onItemSlotClicked ( cocos2d::Ref* sender ) {
    auto slot = static_cast<Sprite*>(sender);
    int position = slot->getTag (); // ��ȡ��λλ��  

    // ����Ϊѡ��״̬������ Inventory ����  
    _inventory->SetSelectedItem ( position );
    _selectedSlot = position;

    // ������ʾ  
    updateDisplay ();
}