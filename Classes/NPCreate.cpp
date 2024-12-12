#include "cocos2d.h"
#include "NPCreate.h"  
#include "NPC.h"   

NPC* NPCreate::CreateNPC ( const std::string& name , const cocos2d::Vec2& position ,
                         const std::vector<std::vector<std::string>>& animationFrames ,
                         const std::vector<cocos2d::Vec2>& validPositions ) {
    NPC* npc = new NPC ( name , position , animationFrames , validPositions );
    return npc; // �ǵü�� npc �Ƿ���ȷ����������  
}

// ���� CreateMultipleNPCs ����  
std::vector<NPC*> NPCreate::CreateMultipleNPCs ( const std::vector<std::pair<std::string , 
    cocos2d::Vec2>>& npcData , 
    const std::vector<std::vector<std::vector<std::string>>>& allAnimationFrames ,
    const std::vector<cocos2d::Vec2>& validPositions ) {
    std::vector<NPC*> npcs; // ���ڴ洢������ NPC  
    for (size_t i = 0; i < npcData.size (); ++i) {
        npcs.push_back ( CreateNPC ( npcData[i].first , npcData[i].second , allAnimationFrames[i] , validPositions) ); // ��չʹ��allAnimationFrames  
    }
    return npcs; // ���ش����� NPC �б�  
}