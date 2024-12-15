// mini_bag.h
#pragma once  
#include "cocos2d.h"  
#include "Inventory.h"  
#include "AppDelegate.h"
class mini_bag : public cocos2d::Layer {
public:

 

    virtual bool init ( Inventory* inventory,std::string& WhichScene );

    static mini_bag* create ( Inventory* inventory,std::string& WhichScene );

    void backgroundcreate ();

    void Itemblock ( Inventory* inventory );

    void updateDisplay (); // 更新显示内容  

    void updateCoordinate ( float& x , float& y);

private:
    Inventory* _inventory; // 指向 Inventory 实例的指针  

    cocos2d::Label* _itemLabel;  // 显示物品信息的标签 

    cocos2d::Vector<cocos2d::Sprite*> _itemSlots; // 存储物品槽的 Sprite  

    int _selectedSlot; // 当前选中的槽位 

    void onItemSlotClicked ( cocos2d::Ref* sender ); // 物品槽的点击事件处理  

    bool isClick = false;  // 标志，表示是否被点击

    cocos2d::Sprite* currentItemSprite = nullptr; // 标识当前选择的物品

    std::string whichScene;
};
