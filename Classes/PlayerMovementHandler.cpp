#include "PlayerMovementHandler.h"
#include "Player.h"

PlayerMovementHandler::PlayerMovementHandler() {
    // 构造函数
}

bool PlayerMovementHandler::handleKeyPressed(EventKeyboard::KeyCode keyCode, Event* event, const GameContext& context) {
    // 如果玩家不能移动或者没有玩家对象，传递给下一个处理器
    if (!context.canPerformGameAction() || !context.player) {
        return passToNext(keyCode, event, context);
    }
    
    // 检查是否为方向键
    if (!isDirectionKey(keyCode)) {
        return passToNext(keyCode, event, context);
    }
    
    int direction = getDirectionFromKey(keyCode);
    if (direction == -1) {
        return passToNext(keyCode, event, context);
    }
    
    // 设置玩家移动状态
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
    
    int direction = getDirectionFromKey(keyCode);
    if (direction == -1) {
        return passReleaseToNext(keyCode, event, context);
    }
    
    // 设置玩家移动状态为停止
    context.player->setMovementState(direction, false);
    
    logDebug("Direction key released: " + std::to_string(static_cast<int>(keyCode)));
    return true;
}

// 这些方法已不需要，Player类现在直接处理这些逻辑

bool PlayerMovementHandler::isDirectionKey(EventKeyboard::KeyCode keyCode) {
    return keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW ||
           keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW ||
           keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW ||
           keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
}

int PlayerMovementHandler::getDirectionFromKey(EventKeyboard::KeyCode keyCode) {
    switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
            return UP;
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            return DOWN;
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            return LEFT;
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            return RIGHT;
        default:
            return -1;
    }
}
