//intimacy.h
#pragma once
#include "cocos2d.h"  
#include "Inventory.h"  
#include "AppDelegate.h"
class intimacyUI : public cocos2d::Layer {
public:
    virtual bool init ();
    static intimacyUI* create ();
    void backgroundcreate ();
    void Itemblock ();
    void updateDisplay (); // ������ʾ����  

private:
    Inventory* _inventory; // ָ�� Inventory ʵ����ָ��  

    cocos2d::Label* _itemLabel;  // ��ʾ��Ʒ��Ϣ�ı�ǩ 

    cocos2d::Vector<cocos2d::Sprite*> _itemSlots; // �洢��Ʒ�۵� Sprite  

    int _selectedSlot; // ��ǰѡ�еĲ�λ  

    void onItemSlotClicked ( cocos2d::Ref* sender ); // ��Ʒ�۵ĵ���¼�����  
};
                            