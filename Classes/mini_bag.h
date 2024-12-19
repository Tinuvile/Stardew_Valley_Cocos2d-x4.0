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

    void updateDisplay (); // ������ʾ����  

    int getSelectedSlot () { return _selectedSlot; }

    void getSelectBack ();

    std::shared_ptr<Item> getSelectedItem();

private:
    Inventory* _inventory; // ָ�� Inventory ʵ����ָ��  

    cocos2d::Label* _itemLabel;  // ��ʾ��Ʒ��Ϣ�ı�ǩ 

    cocos2d::Vector<cocos2d::Sprite*> _itemSlots; // �洢��Ʒ�۵� Sprite  

    int _selectedSlot = 0; // ��ǰѡ�еĲ�λ 

    bool isClick = false;  // ��־����ʾ�Ƿ񱻵��

	bool is_key_e_pressed = false; // ��־����ʾ�Ƿ����� E ��

    cocos2d::Sprite* currentItemSprite = nullptr; // ��ʶ��ǰѡ�����Ʒ

};
