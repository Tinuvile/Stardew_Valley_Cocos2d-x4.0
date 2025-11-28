#include "PlayerMovementHandler.h"
#include "Player.h"

PlayerMovementHandler::PlayerMovementHandler() {
    // 构造函数
}

bool PlayerMovementHandler::handleKeyPressed(EventKeyboard::KeyCode keyCode, Event* event, const GameContext& context) {
    // 调试输出
    CCLOG("[PlayerMovementHandler] Key pressed: %d", static_cast<int>(keyCode));
    CCLOG("[PlayerMovementHandler] Player exists: %s", context.player ? "Yes" : "No");
    CCLOG("[PlayerMovementHandler] Can perform action: %s", context.canPerformGameAction() ? "Yes" : "No");
    
    // 如果玩家不能移动或者没有玩家对象，传递给下一个处理器
    if (!context.canPerformGameAction() || !context.player) {
        CCLOG("[PlayerMovementHandler] Cannot handle key - passing to next");
        return passToNext(keyCode, event, context);
    }
    
    // 检查是否为方向键
    if (!isDirectionKey(keyCode)) {
        CCLOG("[PlayerMovementHandler] Not a direction key, passing to next");
        return passToNext(keyCode, event, context);
    }
    CCLOG("[PlayerMovementHandler] Is direction key!");
    
    Player::MovementDirection direction = getDirectionFromKey(keyCode);
    if (direction == (Player::MovementDirection)-1) {
        return passToNext(keyCode, event, context);
    }
    
    // 设置玩家移动状态
    CCLOG("[PlayerMovementHandler] Setting movement state: direction=%d, pressed=true", static_cast<int>(direction));
    context.player->setMovementState(direction, true);
    
    logDebug("Direction key pressed: " + std::to_string(static_cast<int>(keyCode)));
    return true;
}

bool PlayerMovementHandler::handleKeyReleased(EventKeyboard::KeyCode keyCode, Event* event, const GameContext& context) {
    // 如果没有玩家对象，传递给下一个处理器
    if (!context.player) {
        return passReleaseToNext(keyCode, event, context);
    }
    
    // 检查是否为方向键
    if (!isDirectionKey(keyCode)) {
        return passReleaseToNext(keyCode, event, context);
    }
    
    Player::MovementDirection direction = getDirectionFromKey(keyCode);
    if (direction == (Player::MovementDirection)-1) {
        return passReleaseToNext(keyCode, event, context);
    }
    
    // 设置玩家移动状态为停止 - 会自动更新贴图
    context.player->setMovementState(direction, false);
    
    logDebug("Direction key released: " + std::to_string(static_cast<int>(keyCode)));
    return true;
}

// 这些方法已不需要，Player类现在直接处理这些逻辑

bool PlayerMovementHandler::isDirectionKey(EventKeyboard::KeyCode keyCode) {
    CCLOG("[PlayerMovementHandler] isDirectionKey check: keyCode=%d", static_cast<int>(keyCode));
    CCLOG("[PlayerMovementHandler] KEY_UP_ARROW=%d, KEY_DOWN_ARROW=%d, KEY_LEFT_ARROW=%d, KEY_RIGHT_ARROW=%d",
          static_cast<int>(EventKeyboard::KeyCode::KEY_UP_ARROW),
          static_cast<int>(EventKeyboard::KeyCode::KEY_DOWN_ARROW), 
          static_cast<int>(EventKeyboard::KeyCode::KEY_LEFT_ARROW),
          static_cast<int>(EventKeyboard::KeyCode::KEY_RIGHT_ARROW));
    
    bool isDirection = keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW ||
                      keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW ||
                      keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW ||
                      keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
    
    CCLOG("[PlayerMovementHandler] isDirectionKey result: %s", isDirection ? "true" : "false");
    return isDirection;
}

Player::MovementDirection PlayerMovementHandler::getDirectionFromKey(EventKeyboard::KeyCode keyCode) {
    switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
            return Player::DIRECTION_UP;
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            return Player::DIRECTION_DOWN;
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            return Player::DIRECTION_LEFT;
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            return Player::DIRECTION_RIGHT;
        default:
            return (Player::MovementDirection)-1; // 错误情况
    }
}
