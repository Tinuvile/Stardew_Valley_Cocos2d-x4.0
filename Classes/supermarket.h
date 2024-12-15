#ifndef __supermarket_H__
#define __supermarket_H__

#include "cocos2d.h"
#include "Player.h"
#include "AppDelegate.h"
#include "physics/CCPhysicsWorld.h"
#include "ui/CocosGUI.h"
#include "Inventory.h"
#include "Generaltem.h"

class supermarket : public cocos2d::Scene
{
public:

    supermarket();
    ~supermarket();

    virtual bool init();

    static supermarket* create();

    // 判断角色的位置
    void checkPlayerPosition();
    
    // 创建一个列表，用于保存所有非透明像素的坐标
    std::vector<cocos2d::Vec2> nonTransparentPixels;

    cocos2d::Sprite* button;

    /* 开门按钮 */
    Sprite* opendoor;
    
    // 创建出口区域
    cocos2d::Rect Region_Out = Rect(1343, 818, 50, 868);
  

private:

    // 用于显示计时的标签
    cocos2d::Label* _timerLabel;  

    // 用于显示玩家位置的 Label
    cocos2d::Label* _positionLabel;

    // 退出按钮
    cocos2d::MenuItemImage* closeItem;

    cocos2d::Menu* menu;

    bool  isEnterKeyPressed = false;

    Inventory* StoreItem;

};

#endif // __BACKGROUND1_H__
