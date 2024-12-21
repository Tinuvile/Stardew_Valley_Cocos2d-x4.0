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

    // 判断角色的位置
    void checkPlayerPosition();

    // 返回作物序号
    int getRegionNumber(Vec2 pos);

    // 创建一个列表，用于保存所有非透明像素的坐标
    std::vector<cocos2d::Vec2> nonTransparentPixels;
  
    // 恢复种植
    void AllInitialize_ore(); 

    // 离开山洞
    Rect Out_cave = Rect(720, 1100, 150, 150);

private:

    /* 退出按钮 */
    Sprite* button;

    // 退出按钮
    cocos2d::MenuItemImage* closeItem;

    cocos2d::Menu* menu;

    bool isEnterKeyPressed = false;
    // 判断挖矿M键是否按下
    bool isMKeyPressed = false;


};

#endif 
