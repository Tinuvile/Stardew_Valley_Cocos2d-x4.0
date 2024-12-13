#ifndef __Beach_H__
#define __Beach_H__

#include "cocos2d.h"
#include "farm.h"
#include "FishingGame.h"
#include "Myhouse.h"
#include "Player.h"
#include "AppDelegate.h"
#include "physics/CCPhysicsWorld.h"
#include "ui/CocosGUI.h"



USING_NS_CC;


class Beach : public cocos2d::Scene
{
public:

    Beach ();
    ~Beach ();

    virtual bool init ();

    static  Beach* create ();

    // �жϽ�ɫ��λ��
    void CheckPlayerPosition ();


    // ����һ���б����ڱ������з�͸�����ص�����
    std::vector<cocos2d::Vec2> non_transparent_pixels;

    // �뿪��̲������
    Rect Out_Beach = Rect ( 915 , 70 , 150 , 90 );


private:


    // ������ʾ��ʱ�ı�ǩ
    cocos2d::Label* _timerLabelD;
    cocos2d::Label* _timerLabelH;
    cocos2d::Label* _timerLabelS;

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