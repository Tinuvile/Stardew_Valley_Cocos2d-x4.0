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

    // 判断角色的位置
    void checkPlayerPosition();

    // 创建一个列表，用于保存所有非透明像素的坐标
    std::vector<cocos2d::Vec2> nonTransparentPixels;

    // 出门区域
    Rect OutDoor = Rect(510, 210, 150, 70);
    // 睡觉区域
    Rect GoBed = Rect(1035, 385, 245, 390);


private:

    // 用于显示玩家位置的 Label
    cocos2d::Label* _positionLabel;

    /* 退出按钮 */
    Sprite* button;

    // 退出按钮
    cocos2d::MenuItemImage* closeItem;

    cocos2d::Menu* menu;

    bool isEnterKeyPressed = false;

};

#endif 
