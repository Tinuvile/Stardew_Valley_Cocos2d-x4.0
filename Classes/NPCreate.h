  #include "cocos2d.h"  
#include <string>  
#include <vector>
#include <cstdlib>
#include "Town.h"

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

    // NPC 的行为逻辑  
    virtual void Talk () const;  // NPC 说话行为  

    // NPC移动
    void NPC::MoveToPosition ( const cocos2d::Vec2& targetPosition );

    void NPC::RandomMove ();

    bool NPC::IsPositionValid ( const cocos2d::Vec2& targetPosition , const cocos2d::Vec2& direction );

protected:
    std::string name;            // NPC 的名字  
    cocos2d::Vec2 position;      // NPC 的坐标位置  
    cocos2d::Sprite* sprite;     // NPC 的精灵  

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
};

// NPC 创建类  
class NPCreate {
public:
    // 静态方法，创建 NPC 实例  
    static NPC* CreateNPC ( const std::string& name , const cocos2d::Vec2& position , 
        const std::vector<std::vector<std::string>>& animationFrames , 
        const std::vector<cocos2d::Vec2>& validPositions );

    // 创建多个 NPC 的方法  
    static std::vector<NPC*> CreateMultipleNPCs ( const std::vector<std::pair<std::string , cocos2d::Vec2>>& npcData , 
        const std::vector<std::vector<std::vector<std::string>>>& allAnimationFrames ,
        const std::vector<cocos2d::Vec2>& validPositions );

    cocos2d::AnimationCache* animationCache; // 保存动画 
};
