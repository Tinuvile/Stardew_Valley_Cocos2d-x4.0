#ifndef __supermarket_H_
#define __supermarket_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Player.h"
#include "Inventory.h"

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
    cocos2d::Sprite* opendoor;

    // ������������
    cocos2d::Rect Region_Out = cocos2d::Rect(1343, 818, 50, 868);

private:

    // ������ʾ��ʱ�ı�ǩ
    cocos2d::Label* _timerLabelD;
    cocos2d::Label* _timerLabelH;
    cocos2d::Label* _timerLabelS;

    // ������ʾ���λ�õ� Label
    cocos2d::Label* _positionLabel;

    // �˳���ť
    cocos2d::MenuItemImage* closeItem;

    cocos2d::Menu* menu;

    bool  isEnterKeyPressed = false;

    Inventory* StoreItem;

};

#endif // __supermarket_H_
