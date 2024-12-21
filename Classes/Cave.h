#ifndef __Cave_H__
#define __Cave_H__

#include "cocos2d.h"
#include "Player.h"
#include "Ore.h"
#include "AppDelegate.h"
#include "physics/CCPhysicsWorld.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class Cave : public cocos2d::Scene
{
public:

    Cave();
    ~Cave();

    virtual bool init();

    static Cave* create();

    // �жϽ�ɫ��λ��
    void checkPlayerPosition();

    // �����������
    int getRegionNumber(Vec2 pos);

    // ����һ���б����ڱ������з�͸�����ص�����
    std::vector<cocos2d::Vec2> nonTransparentPixels;
  
    // �ָ���ֲ
    void AllInitialize_ore(); 

    // �뿪ɽ��
    Rect Out_cave = Rect(720, 1100, 150, 150);

private:

    /* �˳���ť */
    Sprite* button;

    // �˳���ť
    cocos2d::MenuItemImage* closeItem;

    cocos2d::Menu* menu;

    bool isEnterKeyPressed = false;
    // �ж��ڿ�M���Ƿ���
    bool isMKeyPressed = false;


};

#endif 
