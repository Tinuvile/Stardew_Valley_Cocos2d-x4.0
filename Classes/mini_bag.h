// mini_bag.h
#pragma once  
#include "cocos2d.h"  
#include "Inventory.h"  
#include "AppDelegate.h"
class mini_bag : public cocos2d::Layer {
public:
    virtual bool init ( Inventory* inventory);

    static mini_bag* create ( Inventory* inventory);

    void backgroundcreate ();

    void Itemblock ( Inventory* inventory );

    void updateDisplay (); // 更新显示内容  

    int getSelectedSlot () { return _selectedSlot; }

    void getSelectBack ();

    std::shared_ptr<Item> getSelectedItem();

private:
    Inventory* _inventory; // 指向 Inventory 实例的指针  

    cocos2d::Label* _itemLabel;  // 显示物品信息的标签 

    cocos2d::Vector<cocos2d::Sprite*> _itemSlots; // 存储物品槽的 Sprite  

    int _selectedSlot = 0; // 当前选中的槽位 

    bool isClick = false;  // 标志，表示是否被点击

	bool is_key_e_pressed = false; // 标志，表示是否按下了 E 键

    cocos2d::Sprite* currentItemSprite = nullptr; // 标识当前选择的物品

};
