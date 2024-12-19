#ifndef __Beach_H__
#define __Beach_H__

#include "cocos2d.h"
#include "farm.h"
#include "FishingGame.h"
#include "Myhouse.h"
#include "Player.h"
#include "AppDelegate.h"
#include "physics/CCPhysicsWorld.h"
#include "ui/CocosGUI.h"


USING_NS_CC;


class Beach : public cocos2d::Scene
{
public:

    Beach ();
    ~Beach ();

    virtual bool init ();

    static  Beach* create ();

    // 下雨效果
    void createRainEffect ();

    // 更改雨滴生命周期
    void updaterain ( float deltaTime );


    // 判断角色的位置
    void CheckPlayerPosition ();


    // 创建一个列表，用于保存所有非透明像素的坐标
    std::vector<cocos2d::Vec2> non_transparent_pixels;

    // 离开海滩的区域
    Rect Out_Beach = Rect ( 240 , 1300 , 150 , 200 );

    cocos2d::ParticleRain* emitter;

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