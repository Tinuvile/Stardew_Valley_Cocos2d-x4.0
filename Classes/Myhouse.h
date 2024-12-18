#ifndef __Myhouse_H__
#define __Myhouse_H__

#include "cocos2d.h"
#include "Player.h"
#include "AppDelegate.h"
#include "farm.h"
#include "physics/CCPhysicsWorld.h"
#include "ui/CocosGUI.h"

USING_NS_CC;


class Myhouse : public cocos2d::Scene
{
public:

    Myhouse();
    ~Myhouse();

    virtual bool init();

    static Myhouse* create();

    // �жϽ�ɫ��λ��
    void checkPlayerPosition();

    // ����һ���б����ڱ������з�͸�����ص�����
    std::vector<cocos2d::Vec2> nonTransparentPixels;

    // ��������
    Rect OutDoor = Rect(510, 210, 150, 70);
    // ˯������
    Rect GoBed = Rect(1035, 385, 245, 390);


private:

    // ������ʾ���λ�õ� Label
    cocos2d::Label* _positionLabel;

    /* �˳���ť */
    Sprite* button;

    // �˳���ť
    cocos2d::MenuItemImage* closeItem;

    cocos2d::Menu* menu;

    bool isEnterKeyPressed = false;

};

#endif 
