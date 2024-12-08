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
    _selectedSlot = 1; // 默认选中第一个槽位  

    // 创建并初始化物品显示标签  
    _itemLabel = Label::createWithTTF ( "" , "fonts/Marker Felt.ttf" , 20 );
    _itemLabel->setPosition ( 200 , 400 );
    this->addChild ( _itemLabel );

    // 初始化物品槽 Sprite  
    for (int i = 0; i < kRowSize; ++i) {
        auto slot = Sprite::create ( "item_slot.png" );
        slot->setPosition ( 100 + i * 50 , 300 ); // 计算槽位位置  
        slot->setTag ( i + 1 ); // 设置槽位的标签  
        this->addChild ( slot );
        _itemSlots.pushBack ( slot );

        // 添加触摸事件  
        auto listener = EventListenerTouchOneByOne::create ();
        listener->onTouchBegan = [this , slot]( Touch* touch , Event* event ) {
            Vec2 location = touch->getLocation ();
            if (slot->getBoundingBox ().containsPoint ( location )) {
                onItemSlotClicked ( slot );
                return true; // 处理这个事件  
            }
            return false; // 不处理这个事件  
            };
        _eventDispatcher->addEventListenerWithSceneGraphPriority ( listener , slot );
    }

    updateDisplay (); // 更新显示内容  

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
        slot->setVisible ( true ); // 确保显示所有槽位  

        // 获取槽位物品  
        auto item = _inventory->GetSelectedItem (); // 或者使用 `_inventory->package[i + 1]`  

        // 更新槽位视觉表现  
        if (item) {
            // 假设 Item 有一个方法可以返回它的图片路径  
            auto itemSprite = Sprite::create ( item->initial_pic );
            itemSprite->setPosition ( slot->getContentSize () / 2 );
            slot->addChild ( itemSprite );
        }
        else {
            slot->removeAllChildren (); // 清空槽位  
        }
    }
    // 更新物品信息标签  
    if (auto selectedItem = _inventory->GetSelectedItem ()) {
        _itemLabel->setString ( "Selected: " + selectedItem->GetName () );
    }
    else {
        _itemLabel->setString ( "No item selected." );
    }
}

void InventoryUI::onItemSlotClicked ( cocos2d::Ref* sender ) {
    auto slot = static_cast<Sprite*>(sender);
    int position = slot->getTag (); // 获取槽位位置  

    // 设置为选中状态并更新 Inventory 数据  
    _inventory->SetSelectedItem ( position );
    _selectedSlot = position;

    // 更新显示  
    updateDisplay ();
}