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

    // 判断角色的位置
    void checkPlayerPosition();
    
    // 创建一个列表，用于保存所有非透明像素的坐标
    std::vector<cocos2d::Vec2> nonTransparentPixels;

    // 创建房子的区域
    cocos2d::Rect Region_supermarket = Rect(163, 518, 130, 60);
    cocos2d::Rect Region_forest = Rect(-940, -400, 200, 110);
    cocos2d::Rect Region_beach = Rect(490, -750, 50, 100);


private:

  
    // 用于显示计时的标签
    cocos2d::Label* _timerLabelD;
    cocos2d::Label* _timerLabelH;
    cocos2d::Label* _timerLabelS;

    // 用于显示玩家位置的 Label
    cocos2d::Label* _positionLabel;

    /* 退出按钮 */
    Sprite* button;

    /* 开门按钮 */
    Sprite* opendoor;

    // 退出按钮
    cocos2d::MenuItemImage* closeItem;

    cocos2d::Menu* menu;

    cocos2d::Sprite* In_gettask;

    bool isEnterKeyPressed = false;


};

#endif // __BACKGROUND1_H__
