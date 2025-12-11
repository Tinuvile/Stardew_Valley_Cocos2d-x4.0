#ifndef __supermarket_H__
#define __supermarket_H__

#include "cocos2d.h"
#include "../Entities/Player.h"
#include "../Core/AppDelegate.h"
#include "physics/CCPhysicsWorld.h"
#include "ui/CocosGUI.h"
#include "../Systems/Inventory.h"
#include "../Items/Generaltem.h"
#include "../Commands/KeyCommand.h"
#include "../Core/InputManager.h"
#include "../Commands/SceneInteractionCommand.h"
#include "../Commands/UICommand.h"

class supermarket : public cocos2d::Scene
{
public:

    supermarket();
    ~supermarket();

    virtual bool init();

    // Command Pattern methods
    void setupInputCommands();
    void cleanupInputCommands();

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

    // 退出按钮
    cocos2d::MenuItemImage* closeItem;

    cocos2d::Menu* menu;

    Inventory* StoreItem;

    // Command Pattern members
    std::vector<std::shared_ptr<KeyCommand>> boundCommands;

};

#endif // __BACKGROUND1_H__
