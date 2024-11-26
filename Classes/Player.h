#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "AppDelegate.h"


class Player : public cocos2d::Sprite
{
public:
    Player();
    ~Player();

    // 创建 Player 对象的工厂方法
    static Player* create();

    // 按键按下时触发的回调函数
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // 按键释放时触发的回调函数
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);


    bool moveLeft, moveDown, moveUp, moveRight;

    Player* player;

    // 角色的移动速度
    float speed;


private:
    // 初始化角色
    bool init();

};

#endif // __PLAYER_H__
