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

    void updateDisplay (); // ������ʾ����  

    void updateCoordinate ( float& x , float& y);

private:
    Inventory* _inventory; // ָ�� Inventory ʵ����ָ��  

    cocos2d::Label* _itemLabel;  // ��ʾ��Ʒ��Ϣ�ı�ǩ 

    cocos2d::Vector<cocos2d::Sprite*> _itemSlots; // �洢��Ʒ�۵� Sprite  

    int _selectedSlot; // ��ǰѡ�еĲ�λ 

    void onItemSlotClicked ( cocos2d::Ref* sender ); // ��Ʒ�۵ĵ���¼�����  

    bool isClick = false;  // ��־����ʾ�Ƿ񱻵��

    cocos2d::Sprite* currentItemSprite = nullptr; // ��ʶ��ǰѡ�����Ʒ

    std::string whichScene;
};
