// InventoryUI.cpp  
#include "InventoryUI.h"  
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
void InventoryUI::backgroundcreate(){
    Vec2 position = player1->getPosition ();
    // ����һ����͸���ĺ�ɫ����
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    auto darkLayer = cocos2d::LayerColor::create ( cocos2d::Color4B ( 0 , 0 , 0 , 120 ) , 5 * visibleSize.width , 5 * visibleSize.height );  // ��ɫ��͸����Ϊ120
    darkLayer->setPosition ( position - visibleSize / 2 );// �������ֲ��λ��
    this->addChild ( darkLayer , 0 );
    auto bag = Sprite::create ( "UIresource/beibao/newbag1.png" );
    bag->setTag ( 101 );
    if (bag == nullptr)
    {
        problemLoading ( "'newbag1.png'" );
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
        bag->setPosition ( position );
        this->addChild ( bag , 0 );
    }
}
void InventoryUI::Itemblock ( Inventory* inventory ) {
    Vec2 position = player1->getPosition ();
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    Vec2 origin = Director::getInstance ()->getVisibleOrigin ();
    _inventory = inventory;
    _selectedSlot = 1; // Ĭ��ѡ�е�һ����λ  


    // ��ʼ����Ʒ�� Sprite 
    for (int m = 0; m < 3; m++)
    {
        for (int i = 0; i < kRowSize; ++i) {
            auto slot = Sprite::create ( "UIresource/beibao/itemblock.png" );
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
            slot->setPosition ( position.x - bagWidth * 0.545 + (originalWidth * scale / 16.5 + 5) * i , position.y + bagHeight * 1.73 / 3.643 - m * (originalHeight * scale / 16.5 + 10) ); // �����λλ��  
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

    auto visibleSize = Director::getInstance ()->getVisibleSize ();

    // ��ʼ����Ʒ��Ϣ��ǩ�����ڵ��ԣ�  
    _itemLabel = Label::createWithSystemFont ( "Selected: None" , "Arial" , 24 );
    if (_itemLabel) {
        _itemLabel->setPosition ( visibleSize.width / 2 , visibleSize.height / 4 );
        this->addChild ( _itemLabel , 10 ); // ��ӵ��㼶��  
    }
    else {
        CCLOG ( "Failed to create _itemLabel" );
    }

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
    Vec2 position = player1->getPosition ();
    if (!_inventory) {
        CCLOG ( "Warning: _inventory is nullptr" );
        return; // �˳�����  
    }

    // ��ȡ��ǰѡ�����Ʒ�Ĳ�λ  
    for (int i = 0; i < kRowSize; ++i) {
        auto slot = _itemSlots.at ( i );
        slot->setVisible ( true ); // ȷ����ʾ���в�λ  

        // ��ȡ��λ��Ʒ  
        auto item = _inventory->GetItemAt ( i + 1 ); // ��ȡ�ض���λ����Ʒ��ע���λ��1��ʼ 

        // ��ȡ��Ʒ����   
        int itemCount = _inventory->GetItemCountAt(i + 1); // ��ȡ�ò�λ����Ʒ����  

        if (item) {
            CCLOG ( "Item in slot %d: %s" , i + 1 , item->GetName ().c_str () );
        }
        else {
            CCLOG ( "No item in slot %d" , i + 1 );
        }

        // �����Ҫ��ȡ�ض���λ����Ʒ��ʹ�� GetItemAt(int position) �����º���  

        // ���²�λ�Ӿ�����  
        if (item) {
            // ���֮ǰ���ӽڵ�  
            slot->removeAllChildren ();

            // ͼƬ·��  
            auto itemSprite = Sprite::create ( item->initial_pic );
            if (itemSprite) {
                itemSprite->setPosition ( slot->getContentSize () / 2 );
                itemSprite->setScale ( 0.7f );
                slot->addChild ( itemSprite , 3 );
                CCLOG ( "Loading item sprite: %s" , item->initial_pic.c_str () );
            }
            else {
                CCLOG ( "Error loading item sprite: %s" , item->initial_pic.c_str () );
            }

            // ���� item �������������������ǩ�������Ҫ����  
            // ���������ﴴ��һ�� Label ��ʾ����  
            auto countLabel = static_cast<Label*>(slot->getChildByTag ( 200 + i )); // ʹ�ò�λ�ı�ǩ����������ǩ��ΨһID  
            if (!countLabel) {
                // �����ǩ�����ڣ������µı�ǩ  
                countLabel = Label::createWithSystemFont ( std::to_string ( itemCount ) , "fonts/Comic Sans MS.ttf" , 20 );
                countLabel->setTextColor ( Color4B ( 255 , 153 , 0 , 255 ) );
                countLabel->setPosition ( slot->getContentSize ().width * 0.8 ,  slot->getContentSize ().height * 0.2 ); // ����λ���ڲ�λ���·�  
                countLabel->setTag ( 200 + i ); // ���ñ�ǩ  
                slot->addChild ( countLabel , 4 ); // ��ӵ��㼶��  
            }
            else {
                // �����ǩ���ڣ���������  
                countLabel->setString ( std::to_string ( itemCount ) );
            }
        }
        else {
            slot->removeAllChildren (); // ��ղ�λ  

            // ���������ǩ  
            auto countLabel = static_cast<Label*>(slot->getChildByTag ( 200 + i ));
            if (countLabel) {
                countLabel->removeFromParent (); // �Ƴ�������ǩ  
            }
        }
    }

    // ������Ʒ��Ϣ��ǩ�����ڵ��ԣ�  
    if (_itemLabel) { // ��� _itemLabel �Ƿ�Ϊ nullptr  
        if (auto selectedItem = _inventory->GetSelectedItem ()) {
            _itemLabel->setString ( "Selected: " + selectedItem->GetName () );
        }
        else {
            _itemLabel->setString ( "No item selected." );
        }
    }
    else {
        CCLOG ( "Warning: _itemLabel is nullptr" );
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