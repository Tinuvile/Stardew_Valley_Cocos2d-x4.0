//intimacyUI.h
//�������ܶȽ���
#pragma once
#include "cocos2d.h"  
#include "NpcRelationship.h"  
#include "AppDelegate.h"
#include "InventoryUI.h"

extern Inventory* inventory;

class intimacyUI : public cocos2d::Layer
{
public:
    virtual bool init ();

    static intimacyUI* create ();

    void backgroundcreate ();

    void Buttons_switching ();


    //���������
    void charactersSlider ();

private:  
    void onItemSlotClicked ( cocos2d::Ref* sender ); // ��Ʒ�۵ĵ���¼�����  
};
                       