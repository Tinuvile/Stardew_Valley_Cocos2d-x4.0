#ifndef __Town_H__
#define __Town_H__

#include "cocos2d.h"
#include "Player.h"
#include "AppDelegate.h"
#include "mini_bag.h"
#include "physics/CCPhysicsWorld.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class Town : public cocos2d::Scene
{
public:

    Town();
    ~Town();

    virtual bool init();

    static Town* create();

    // �жϽ�ɫ��λ��
    void checkPlayerPosition();
    
    // ����һ���б����ڱ������з�͸�����ص�����
    std::vector<cocos2d::Vec2> nonTransparentPixels;

    // �������ӵ�����
    cocos2d::Rect Region_supermarket = Rect(163, 518, 130, 60);
    cocos2d::Rect Region_forest = Rect(-940, -400, 200, 110);
    cocos2d::Rect Region_beach = Rect(490, -750, 50, 100);


private:

  
    // ������ʾ��ʱ�ı�ǩ
    cocos2d::Label* _timerLabelD;
    cocos2d::Label* _timerLabelH;
    cocos2d::Label* _timerLabelS;

    // ������ʾ���λ�õ� Label
    cocos2d::Label* _positionLabel;

    /* �˳���ť */
    Sprite* button;

    /* ���Ű�ť */
    Sprite* opendoor;

    // �˳���ť
    cocos2d::MenuItemImage* closeItem;

    cocos2d::Menu* menu;

    cocos2d::Sprite* In_gettask;

    bool isEnterKeyPressed = false;


};

#endif // __BACKGROUND1_H__
