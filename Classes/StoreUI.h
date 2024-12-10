// StoreUI.h  
#pragma once  
#include "cocos2d.h"  
#include "Inventory.h"  
#include "AppDelegate.h"

class StoreUI : public cocos2d::Layer {
public:
    virtual bool init ( Inventory* mybag , Inventory* goods );
    static StoreUI* create ( Inventory* mybag , Inventory* goods );
    //����ͼչʾ
    void backgroundcreate ();
    //��Ʒչʾ
    void ProductDisplay ( Inventory* mybag , Inventory* goods );

    void Itemblock ( Inventory* mybag , Inventory* goods );

    void updateDisplay (); // ������ʾ����  

    void moneyDisplay ();

private:
    Inventory* _mybag; // ָ���Լ�����ʵ����ָ��  

    Inventory* _goods; // ָ����Ʒʵ����ָ��  

    cocos2d::Label* _itemLabel;  // ��ʾ��Ʒ��Ϣ�ı�ǩ 

    cocos2d::Vector<cocos2d::Sprite*> _itemSlots; // �洢��Ʒ�۵� Sprite  

    int _selectedSlot; // ��ǰѡ�еĲ�λ  

    void onItemSlotClicked ( cocos2d::Ref* sender ); // ��Ʒ�۵ĵ���¼�����  
};
