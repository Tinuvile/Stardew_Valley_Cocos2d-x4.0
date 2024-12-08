// InventoryUI.cpp  
#include "InventoryUI.h"  
#include "ui/CocosGUI.h"  
#include "Item.h"  

USING_NS_CC;

bool InventoryUI::init ( Inventory* inventory ) {
    if (!Layer::init ()) {
        return false;
    }

    _inventory = inventory;
    _selectedSlot = 1; // Ĭ��ѡ�е�һ����λ  

    // ��������ʼ����Ʒ��ʾ��ǩ  
    _itemLabel = Label::createWithTTF ( "" , "fonts/Marker Felt.ttf" , 20 );
    _itemLabel->setPosition ( 200 , 400 );
    this->addChild ( _itemLabel );

    // ��ʼ����Ʒ�� Sprite  
    for (int i = 0; i < kRowSize; ++i) {
        auto slot = Sprite::create ( "item_slot.png" );
        slot->setPosition ( 100 + i * 50 , 300 ); // �����λλ��  
        slot->setTag ( i + 1 ); // ���ò�λ�ı�ǩ  
        this->addChild ( slot );
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