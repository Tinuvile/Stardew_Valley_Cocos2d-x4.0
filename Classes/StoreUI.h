#pragma once
// StoreUI.h    
#include "cocos2d.h"  
#include "Inventory.h"  
#include "AppDelegate.h"
#include "EconomicSystem.h"

USING_NS_CC;

class StoreUI : public cocos2d::Layer {
public:
    virtual bool init ( Inventory* mybag , Inventory* goods );
    static StoreUI* create ( Inventory* mybag , Inventory* goods );
    //背景图展示
    void backgroundcreate ();
    //商品展示
    void ProductDisplay ( Inventory* mybag , Inventory* goods );

    void Itemblock ( Inventory* mybag , Inventory* goods );

    void updateDisplay (); // 更新显示内容  

    void moneyDisplay ();

    void SliderDisplay ();

    void updateCoordinate ( float& x , float& y );
private:
    Inventory* _mybag; // 指向自己背包实例的指针  

    Inventory* _goods; // 指向商品实例的指针  

    cocos2d::Label* _itemLabel;  // 显示物品信息的标签 

    cocos2d::Vector<cocos2d::Sprite*> _itemSlots; // 存储物品槽的 Sprite  

    int _selectedSlot; // 当前选中的槽位  

    void onItemSlotClicked ( cocos2d::Ref* sender ); // 物品槽的点击事件处理 

    bool isClick = false;

    shared_ptr<Item> chosen_Item = nullptr;

    std::shared_ptr<EconomicSystem> economicSystem;
};
