#pragma once
#include "cocos2d.h" 

// NPC 角色类  
class NPC : public cocos2d::Node {
public:
    NPC ( const std::string& name , const cocos2d::Vec2& position ,
        const std::vector<std::vector<std::string>>& animationFrames ,
        const std::vector<cocos2d::Vec2>& validPositions );

    // 获取 NPC 的精灵  
    cocos2d::Sprite* GetSprite () const { return sprite; }

    // NPC 的名称
    const std::string& GetName () const { return name; }

    // NPC 的位置  
    const cocos2d::Vec2& GetPosition () const { return position; }

    // 设定 NPC 的位置  
    void SetPosition ( const cocos2d::Vec2& pos ) { position = pos; }

    // NPC移动
    void MoveToPosition ( const cocos2d::Vec2& targetPosition );

    void RandomMove ();

    bool IsPositionValid ( const cocos2d::Vec2& targetPosition , const cocos2d::Vec2& direction );

    int GetGiftTime () { return GiftTime; }

    int AddGiftTime () { GiftTime++; }

protected:
    std::string name;            // NPC 的名字  
    cocos2d::Vec2 position;      // NPC 的坐标位置  
    cocos2d::Sprite* sprite;     // NPC 的精灵

    int GiftTime = 0;                // NPC 是否送过礼物

    std::vector<cocos2d::Vec2> nonTransparentPixels;

    // 创建动画  
    void CreateAnimation ( const std::string& animationName , const std::vector<std::string>& framePaths , float delay );

    // 播放动画  
    void PlayAnimation ( const std::string& animationName , bool loop = true );

    // 动画帧  
    std::vector<std::string> upFrames;
    std::vector<std::string> downFrames;
    std::vector<std::string> leftFrames;
    std::vector<std::string> rightFrames;

    // 动画帧路径  
    std::vector<std::vector<std::string>> animations; // [0]: up, [1]: down, [2]: left, [3]: right 

    std::string currentAnimationName; // 跟踪当前动画名称

    cocos2d::Vec2 currentDirection; // 当前移动方向
};


std::vector<std::vector<std::string>> getAbigailAnimations ();

std::vector<std::vector<std::string>> getDialog ( std::string npc , std::string relation_ship );

std::string getNPCportraits ( std::string name , std::string status );

std::vector<std::vector<std::string>> getAlexAnimations ();

std::vector<std::vector<std::string>> getCarolineAnimations ();

std::vector<std::vector<std::string>> getElliottAnimations ();

std::vector<std::vector<std::string>> getEmilyAnimations ();