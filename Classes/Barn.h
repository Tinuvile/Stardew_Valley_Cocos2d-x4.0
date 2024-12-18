#ifndef __Barn_H__
#define __Barn_H__

#include "cocos2d.h"
//#include "farm.h"
//#include "Myhouse.h"
#include "Player.h"
#include "AppDelegate.h"
#include "Sheep.h"
#include "physics/CCPhysicsWorld.h"
#include "ui/CocosGUI.h"



USING_NS_CC;

const int kMaxLivestock = 12;

class Barn : public cocos2d::Scene
{
public:

    Barn();
    ~Barn();

    virtual bool init();

    static  Barn* create();

    // �жϽ�ɫ��λ��
    void checkPlayerPosition();


    // ����һ���б����ڱ������з�͸�����ص�����
    std::vector<cocos2d::Vec2> nonTransparentPixels;

    //// �뿪���������
    Rect Out_Barn = Rect(915, 70, 150, 90);

    void GetProduction ( cocos2d::EventMouse* event );


private:

    // ������ʾ���λ�õ� Label
    cocos2d::Label* _positionLabel;

    /* �˳���ť */
    cocos2d::Sprite* button;

    // �˳���ť
    cocos2d::MenuItemImage* closeItem;

    cocos2d::Menu* menu;

    bool isEnterKeyPressed = false;
    
    

};

#endif 