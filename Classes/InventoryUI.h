// InventoryUI.h  
#pragma once  
#include "cocos2d.h"  
#include "Inventory.h"  
#include "AppDelegate.h"
#include "intimacyUI.h"
class InventoryUI : public cocos2d::Layer {
public:
    virtual bool init ( Inventory* inventory );

    static InventoryUI* create ( Inventory* inventory );

    void backgroundcreate ();

    void Itemblock ( Inventory* inventory );

    void updateDisplay (); // ������ʾ����  

    void Buttons_switching ();

private:
    Inventory* _inventory; // ָ�� Inventory ʵ����ָ��  

    cocos2d::Label* _itemLabel;  // ��ʾ��Ʒ��Ϣ�ı�ǩ 

    cocos2d::Vector<cocos2d::Sprite*> _itemSlots; // �洢��Ʒ�۵� Sprite  

    int _selectedSlot; // ��ǰѡ�еĲ�λ 

    void onItemSlotClicked ( cocos2d::Ref* sender ); // ��Ʒ�۵ĵ���¼�����  

    bool isClick = false;  // ��־����ʾ�Ƿ񱻵��

    Sprite* currentItemSprite = nullptr; // ��ʶ��ǰѡ�����Ʒ

};
