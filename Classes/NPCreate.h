#ifndef __NPCREATE_H_  
#define __NPCREATE_H_  

#include <string>  
#include <vector>
#include <cstdlib>
#include "cocos2d.h"
#include "NPC.h"

class NPCreate {
public:

	static NPC* CreateNPC ( const std::string& name , const cocos2d::Vec2& position ,
		const std::vector<std::vector<std::string>>& animationFrames ,
		const std::vector<cocos2d::Vec2>& validPositions );

	static std::vector<NPC*> CreateMultipleNPCs ( const std::vector<std::pair<std::string , cocos2d::Vec2>>& npcData ,
		const std::vector<std::vector<std::vector<std::string>>>& allAnimationFrames ,
		const std::vector<cocos2d::Vec2>& validPositions );

	cocos2d::AnimationCache* animationCache;
};

#endif // __NPCREATE_H_ 