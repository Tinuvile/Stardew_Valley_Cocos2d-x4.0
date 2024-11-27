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

    // 退出按钮的回调函数，点击退出按钮时执行的操作
    virtual void menuCloseCallback(cocos2d::Ref* pSender);

    void checkPlayerPosition(Player* player);
    
    // 创建一个列表，用于保存所有非透明像素的坐标
    std::vector<cocos2d::Vec2> nonTransparentPixels;

private:

    // 用于显示玩家位置的 Label
    cocos2d::Label* _positionLabel;

    // 用于显示计时的标签
    cocos2d::Label* _timerLabel;  

    int remainingTime = 600000;


    cocos2d::PhysicsWorld* _physicsWorld;

};

#endif // __BACKGROUND1_H__
