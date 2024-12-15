#include "cocos2d.h"  
#include "NPC.h"

// NPC ������  
class NPCreate {
public:
    // ��̬���������� NPC ʵ��  
    static NPC* CreateNPC ( const std::string& name , const cocos2d::Vec2& position , 
        const std::vector<std::vector<std::string>>& animationFrames , 
        const std::vector<cocos2d::Vec2>& validPositions );

    // ������� NPC �ķ���  
    static std::vector<NPC*> CreateMultipleNPCs ( const std::vector<std::pair<std::string , cocos2d::Vec2>>& npcData , 
        const std::vector<std::vector<std::vector<std::string>>>& allAnimationFrames ,
        const std::vector<cocos2d::Vec2>& validPositions );

    cocos2d::AnimationCache* animationCache; // ���涯�� 
};
