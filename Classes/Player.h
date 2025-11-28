#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "Inventory.h"
#include "Crop.h"
#include "AppDelegate.h"

const int kDefaultEnergy = 100;

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

    // 移动方向枚举
    enum MovementDirection {
        DIRECTION_UP = 0,
        DIRECTION_DOWN = 1,
        DIRECTION_LEFT = 2,
        DIRECTION_RIGHT = 3
    };
    
    // 设置移动状态（由输入处理器调用）
    void setMovementState(MovementDirection direction, bool isPressed);
    
    // 获取移动状态
    bool getMovementState(int direction) const;

    // 移动逻辑（每帧调用）
    void player1_move();

    // 动画切换逻辑（定时调用）
    void player_change();
    
    // 更新玩家贴图
    void updateTexture(int direction);


    bool moveLeft, moveDown, moveUp, moveRight;

    bool leftpressed = false, downpressed = false, uppressed = false, rightpressed = false;

    // 角色的移动速度
    float speed;

    int look_state = 0;

    std::string pic_path;

    //int energy_limit = kDefaultEnergy;
    //int current_energy = kDefaultEnergy;

};

#endif // __PLAYER_H__
