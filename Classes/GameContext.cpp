#include "GameContext.h"
#include "Player.h"

// 更新玩家位置的实现
void GameContext::updatePlayerPosition() {
    if (player != nullptr) {
        playerPos = player->getPosition();
    } else {
        // 如果没有玩家对象，设置默认位置
        playerPos = cocos2d::Vec2::ZERO;
    }
}
