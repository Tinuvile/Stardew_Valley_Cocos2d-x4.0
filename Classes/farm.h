#ifndef __farm_H__
#define __farm_H__

#include "cocos2d.h"
#include "Barn.h"
#include "Player.h"
#include "Crop.h"
#include "AppDelegate.h"
#include "physics/CCPhysicsWorld.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class farm : public cocos2d::Scene
{
public:

    farm ();
    ~farm ();

    virtual bool init ();

    static farm* create ();

    // 判断角色的位置
    void checkPlayerPosition ();

    // 下雨效果
    void createRainEffect();

    // 更改雨滴生命周期
    void updaterain(float deltaTime);



    // 返回作物序号
    int getRegionNumber ( Vec2 pos );

    // 创建一个列表，用于保存所有非透明像素的坐标
    std::vector<cocos2d::Vec2> nonTransparentPixels;

    // 离开农场的区域
    Rect Out_Farm = Rect ( 792 , 1187 , 36 , 153 );

    // 可种植区域(单块面积为 48 * 48 )
    Rect plant_area = Rect ( 474 , 467 , 864 , 510 );

    // 可以进入家的区域
    Rect myhouse_area = Rect ( 70 , 920 , 75 , 30 );

    // 可以进入畜棚的区域
    Rect barn_area = Rect ( 20 , 170 , 70 , 70 );

    // 可以进入山洞的区域
    Rect cave_area = Rect ( 635 , 1185 , 90 , 40 );

    // 可以进入森林的区域
    Rect forest_area = Rect ( 750 , -70 , 100 , 50 );

    cocos2d::ParticleRain* emitter;

    // 恢复种植
    void AllInitialize_crop ();

private:

    // 用于显示玩家位置的 Label
    cocos2d::Label* _positionLabel;

    /* 退出按钮 */
    Sprite* button;


    // 退出按钮
    cocos2d::MenuItemImage* closeItem;

    cocos2d::Menu* menu;

    bool isEnterKeyPressed = false;
    // 判断种植P键是否按下
    bool isPKeyPressed = false;
    // 判断浇水W键是否按下
    bool isWKeyPressed = false;
    // 判断收割G键是否按下
    bool isGKeyPressed = false;



};

#endif 