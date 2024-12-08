// InventoryUI.h  
#pragma once  
#include "cocos2d.h"  
#include "Inventory.h"  

class InventoryUI : public cocos2d::Layer {
public:
    virtual bool init ( Inventory* inventory );
    static InventoryUI* create ( Inventory* inventory );

    void updateDisplay (); // 更新显示内容  

private:
    Inventory* _inventory; // 指向 Inventory 实例的指针  

    cocos2d::Label* _itemLabel;  // 显示物品信息的标签  
    cocos2d::Vector<cocos2d::Sprite*> _itemSlots; // 存储物品槽的 Sprite  
    int _selectedSlot; // 当前选中的槽位  

    void onItemSlotClicked ( cocos2d::Ref* sender ); // 物品槽的点击事件处理  
};
