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

    // 判断角色的位置
    void checkPlayerPosition();


    // 创建一个列表，用于保存所有非透明像素的坐标
    std::vector<cocos2d::Vec2> nonTransparentPixels;

    //// 离开畜棚的区域
    Rect Out_Barn = Rect(915, 70, 150, 90);

    void GetProduction ( cocos2d::EventMouse* event );


private:

    // 用于显示玩家位置的 Label
    cocos2d::Label* _positionLabel;

    /* 退出按钮 */
    cocos2d::Sprite* button;

    // 退出按钮
    cocos2d::MenuItemImage* closeItem;

    cocos2d::Menu* menu;

    bool isEnterKeyPressed = false;
    
    

};

#endif 