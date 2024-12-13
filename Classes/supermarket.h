#ifndef __supermarket_H_
#define __supermarket_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Player.h"
#include "Inventory.h"

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
    cocos2d::Sprite* opendoor;

    // 创建出口区域
    cocos2d::Rect Region_Out = cocos2d::Rect(1343, 818, 50, 868);

private:

    // 用于显示计时的标签
    cocos2d::Label* _timerLabelD;
    cocos2d::Label* _timerLabelH;
    cocos2d::Label* _timerLabelS;

    // 用于显示玩家位置的 Label
    cocos2d::Label* _positionLabel;

    // 退出按钮
    cocos2d::MenuItemImage* closeItem;

    cocos2d::Menu* menu;

    bool  isEnterKeyPressed = false;

    Inventory* StoreItem;

};

#endif // __supermarket_H_
