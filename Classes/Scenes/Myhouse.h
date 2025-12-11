#ifndef __Myhouse_H__
#define __Myhouse_H__

#include "cocos2d.h"
#include "../Entities/Player.h"
#include "../Core/AppDelegate.h"
#include "farm.h"
#include "physics/CCPhysicsWorld.h"
#include "ui/CocosGUI.h"
#include "../Core/InputManager.h"
#include "../Commands/SceneInteractionCommand.h"
#include "../Commands/UICommand.h"

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

    // 设置输入命令绑定
    void setupInputCommands();

    // 清理输入命令绑定
    void cleanupInputCommands();

    // 创建一个列表，用于保存所有非透明像素的坐标
    std::vector<cocos2d::Vec2> nonTransparentPixels;

    // 出门区域
    Rect OutDoor = Rect(510, 210, 150, 70);
    // 睡觉区域
    Rect GoBed = Rect(1035, 385, 245, 390);


private:

  
    /* 退出按钮 */
    Sprite* button;

    // 退出按钮
    cocos2d::MenuItemImage* closeItem;

    cocos2d::Menu* menu;

    // Command Pattern相关的成员变量
    std::vector<std::shared_ptr<KeyCommand>> boundCommands;

};

#endif 
