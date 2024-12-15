#include "cocos2d.h"  
#include "NPC.h"

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
