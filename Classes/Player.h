#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "Inventory.h"
#include "Crop.h"
#include "AppDelegate.h"

USING_NS_CC;

class Player : public cocos2d::Sprite
{
public:
    Player();
    ~Player();

    // 创建 Player 对象的方法
    static Player* create();

    // 初始化角色
    bool init();

    // 按键按下时触发的回调函数
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // 按键释放时触发的回调函数
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    void player1_move();

    void player_change();


    bool moveLeft, moveDown, moveUp, moveRight;

    bool leftpressed = false, downpressed = false, uppressed = false, rightpressed = false;

    // 角色的移动速度
    float speed;

    int look_state = 0;

    std::string pic_path;



};

#endif // __PLAYER_H__
