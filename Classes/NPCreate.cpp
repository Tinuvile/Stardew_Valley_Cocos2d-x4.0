#include "NPCreate.h"  

NPC* NPCreate::CreateNPC ( const std::string& name , const cocos2d::Vec2& position ,
                          const std::vector<std::vector<std::string>>& animationFrames ,
                          const std::vector<cocos2d::Vec2>& validPositions ) {
    NPC* npc = new NPC ( name , position , animationFrames , validPositions ); // 修改为传递 validPositions  
    return npc;
}

// 更新 CreateMultipleNPCs 方法  
std::vector<NPC*> NPCreate::CreateMultipleNPCs ( const std::vector<std::pair<std::string , 
    cocos2d::Vec2>>& npcData , 
    const std::vector<std::vector<std::vector<std::string>>>& allAnimationFrames ,
    const std::vector<cocos2d::Vec2>& validPositions ) {
    std::vector<NPC*> npcs; // 用于存储创建的 NPC  
    for (size_t i = 0; i < npcData.size (); ++i) {
        npcs.push_back ( CreateNPC ( npcData[i].first , npcData[i].second , allAnimationFrames[i] , validPositions) ); // 扩展使用allAnimationFrames  
    }
    return npcs; // 返回创建的 NPC 列表  
}