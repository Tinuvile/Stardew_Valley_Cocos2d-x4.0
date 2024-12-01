#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "AppDelegate.h"

USING_NS_CC;

class Player : public cocos2d::Sprite
{
public:
    Player();
    ~Player();

    // 创建 Player 对象的方法
    static Player* create();

    // 按键按下时触发的回调函数
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // 按键释放时触发的回调函数
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);


    bool moveLeft, moveDown, moveUp, moveRight;

    bool leftpressed = false, downpressed = false, uppressed = false, rightpressed = false;

    // 角色的移动速度
    float speed;

    int look_state = 0;

    void player1_move();

    void player_change();


private:
    // 初始化角色
    bool init();

};

#endif // __PLAYER_H__
