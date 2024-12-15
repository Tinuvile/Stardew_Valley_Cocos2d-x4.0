#ifndef __supermarket_H__
#define __supermarket_H__

#include "cocos2d.h"
#include "Player.h"
#include "AppDelegate.h"
#include "physics/CCPhysicsWorld.h"
#include "ui/CocosGUI.h"
#include "Inventory.h"
#include "Generaltem.h"

class supermarket : public cocos2d::Scene
{
public:

    supermarket();
    ~supermarket();

    virtual bool init();

    static supermarket* create();

    // �жϽ�ɫ��λ��
    void checkPlayerPosition();
    
    // ����һ���б����ڱ������з�͸�����ص�����
    std::vector<cocos2d::Vec2> nonTransparentPixels;

    cocos2d::Sprite* button;

    /* ���Ű�ť */
    Sprite* opendoor;
    
    // ������������
    cocos2d::Rect Region_Out = Rect(1343, 818, 50, 868);
  

private:

    // ������ʾ��ʱ�ı�ǩ
    cocos2d::Label* _timerLabel;  

    // ������ʾ���λ�õ� Label
    cocos2d::Label* _positionLabel;

    // �˳���ť
    cocos2d::MenuItemImage* closeItem;

    cocos2d::Menu* menu;

    bool  isEnterKeyPressed = false;

    Inventory* StoreItem;

};

#endif // __BACKGROUND1_H__
