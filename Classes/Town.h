
#ifndef __myhouse_H__
#define __myhouse_H__

#include "cocos2d.h"
#include "Player.h"
#include "AppDelegate.h"
#include "physics/CCPhysicsWorld.h"

class Town : public cocos2d::Scene
{
public:

    Town();
    ~Town();

    virtual bool init();

    static Town* create();

    Player* player1;

    // �˳���ť�Ļص�����������˳���ťʱִ�еĲ���
    virtual void menuCloseCallback(cocos2d::Ref* pSender);

    // �жϽ�ɫ��λ��
    void checkPlayerPosition(Player* player);
    
    // ����һ���б������ڱ������з�͸�����ص�����
    std::vector<cocos2d::Vec2> nonTransparentPixels;

        // �������ӵ�����
    cocos2d::Rect Get_Task = cocos2d::Rect(473, 578, 120, 30);  // ��ȡ��������


private:

    // ������ʾ���λ�õ� Label
    cocos2d::Label* _positionLabel;

    // ������ʾ��ʱ�ı�ǩ
    cocos2d::Label* _timerLabel;  

    int remainingTime = 600000;

    cocos2d::Sprite* In_gettask;

    cocos2d::PhysicsWorld* _physicsWorld;

};

#endif // __BACKGROUND1_H__