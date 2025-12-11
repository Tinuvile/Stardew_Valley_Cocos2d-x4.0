#ifndef __Barn_H__
#define __Barn_H__

#include "cocos2d.h"
//#include "farm.h"
//#include "Myhouse.h"
#include "../Entities/Player.h"
#include "../Core/AppDelegate.h"
#include "../Entities/Sheep.h"
#include "physics/CCPhysicsWorld.h"
#include "ui/CocosGUI.h"
#include "../Commands/KeyCommand.h"
#include "../Core/InputManager.h"
#include "../Commands/SceneInteractionCommand.h"
#include "../Commands/UICommand.h"
#include <memory>
#include <vector>



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

    // 设置输入命令绑定
    void setupInputCommands();
    
    // 清理输入命令绑定
    void cleanupInputCommands();


    // 创建一个列表，用于保存所有非透明像素的坐标
    std::vector<cocos2d::Vec2> nonTransparentPixels;

    //// 离开畜棚的区域
    Rect Out_Barn = Rect(915, 70, 150, 90);

    void GetProduction ( cocos2d::EventMouse* event );


private:

    /* 退出按钮 */
    cocos2d::Sprite* button;

    // 退出按钮
    cocos2d::MenuItemImage* closeItem;

    cocos2d::Menu* menu;

    // Command Pattern相关的成员变量
    std::vector<std::shared_ptr<KeyCommand>> boundCommands;
    

};

#endif 