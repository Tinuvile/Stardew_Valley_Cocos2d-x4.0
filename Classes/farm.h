#ifndef __farm_H__
#define __farm_H__

#include "cocos2d.h"
#include "Player.h"
#include "Crop.h"
#include "AppDelegate.h"
#include "physics/CCPhysicsWorld.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class farm : public cocos2d::Scene
{
public:

    farm();
    ~farm();

    virtual bool init();

    static farm* create();

    // �жϽ�ɫ��λ��
    void checkPlayerPosition();

    // ��ֲ����
    void plant_seed(Vec2 pos);

    // �����������
    int getRegionNumber(Vec2 pos);

    // ����һ���б����ڱ������з�͸�����ص�����
    std::vector<cocos2d::Vec2> nonTransparentPixels;

    // �뿪ũ��������
    Rect Out_Farm = Rect(792, 1187, 36, 153);

    // ����ֲ����(�������Ϊ 48 * 48 )
    Rect plant_area = Rect(474, 467, 864, 510);
  
    // �ָ���ֲ
    // void AllInitialize_crop();

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
    // �ж���ֲP���Ƿ���
    bool isPKeyPressed = false;
    // �жϽ�ˮW���Ƿ���
    bool isWKeyPressed = false;
    // �ж��ո�G���Ƿ���
    bool isGKeyPressed = false;
    bool isSpaceKeyPressed = false;


};

#endif // __BACKGROUND1_H__
