#pragma once
#include"cocos2d.h"
#include"AppDelegate.h"
#include"Fish.h"

const float kBackgroundWidth = 39.0f;
const float kBackgroundHeight = 149.0f;
const float kBackgroundScale = 3.0f;

const float kIconBeginX = 17.0f;
const float kIconBeginY = 5.0f;
const float kIconHeight = kBackgroundHeight - kIconBeginY;

const float kFishBasicScale = 0.5f;

const float kGreeenBarBasicScaleY = 5.0f;

const float kProgressBarBeginX = 33.0f;
const float kProgressBarBeginY = 3.0f;

const float kProgressBarBasicScaleX = 3.0f;
const float kProgressBarBasicScaleY = 143.0f / 5.0f;


// 钓鱼游戏类，继承自cocos2d::Layer。
// 包含钓鱼游戏的所有主要元素和逻辑，包括鱼图标、绿色浮标、进度条和背景。
class FishingGame : public cocos2d::Layer {
private:
    //鱼图标
    cocos2d::Sprite* fish;
    //绿色浮标
    cocos2d::Sprite* green_bar;
    //进度条
    cocos2d::ProgressTimer* progress_bar;
    
    //背景
    cocos2d::Sprite* background;

    // 鱼的垂直位置
    float fishlike_icon_height = 0;
    // 绿色浮标的垂直位置
    float green_bar_height = 0;
    // 玩家是否按住鼠标
    bool is_pressing = false; 

    //本次钓鱼的品种
    int fish_type;

    //钓鱼游戏的位置
    cocos2d::Vec2 position; 

public:
    // 默认构造函数。
    FishingGame () {};

    // 带玩家位置参数的构造函数。
    // player_pos 玩家位置。
    FishingGame ( const cocos2d::Vec2& player_pos )
        :position ( player_pos ) {};

    // 创建钓鱼游戏实例的静态方法。
    // param player_position 玩家位置。
    // 返回创建的FishingGame实例指针。
    static FishingGame* create ( const cocos2d::Vec2& player_position );

    // 初始化钓鱼游戏。
    // 返回初始化是否成功。
    virtual bool init ();

    // 创建钓鱼游戏实例的宏定义。
    CREATE_FUNC ( FishingGame );

    // 添加鼠标监听器。
    void AddMouseListener ();

    // 更新游戏状态。
    // deltaTime 距离上次更新的时间。
    void UpdateGame (float deltaTime);

    // 检查鱼是否在浮标范围内。
    void CheckFishInBar ();

    // 结束游戏。
    // succeed 游戏是否成功。
    void EndGame (bool succeed);
};
