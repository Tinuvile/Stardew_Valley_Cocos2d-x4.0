#include "SceneActionHandler.h"
#include "Player.h"
#include "farm.h"
#include "Beach.h"
#include "Cave.h"
#include "Town.h"
#include "Myhouse.h"
#include "Forest.h"
#include "Barn.h"
#include "FishingGame.h"
#include "EnergySystem.h"
#include "AppDelegate.h"

SceneActionHandler::SceneActionHandler() {
    // 构造函数
}

bool SceneActionHandler::handleKeyPressed(EventKeyboard::KeyCode keyCode, Event* event, const GameContext& context) {
    // 如果有UI打开，不处理场景动作
    if (context.isUIOpen) {
        return passToNext(keyCode, event, context);
    }
    
    // 根据当前场景分派到对应的处理函数
    if (context.currentScene == "farm") {
        return handleFarmActions(keyCode, context);
    } else if (context.currentScene == "Beach") {
        return handleBeachActions(keyCode, context);
    } else if (context.currentScene == "Cave") {
        return handleCaveActions(keyCode, context);
    } else if (context.currentScene == "Town") {
        return handleTownActions(keyCode, context);
    } else if (context.currentScene == "Myhouse") {
        return handleHouseActions(keyCode, context);
    } else if (context.currentScene == "Forest") {
        return handleForestActions(keyCode, context);
    } else if (context.currentScene == "Barn") {
        return handleBarnActions(keyCode, context);
    }
    
    // 未知场景，传递给下一个处理器
    return passToNext(keyCode, event, context);
}

bool SceneActionHandler::handleKeyReleased(EventKeyboard::KeyCode keyCode, Event* event, const GameContext& context) {
    // 大部分场景动作在按键释放时不需要特殊处理
    return passReleaseToNext(keyCode, event, context);
}

bool SceneActionHandler::handleFarmActions(EventKeyboard::KeyCode keyCode, const GameContext& context) {
    switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_P:
            return plantCrop(context.playerPos, context.scene);
            
        case EventKeyboard::KeyCode::KEY_W:
            return waterCrop(context.playerPos, context.scene);
            
        case EventKeyboard::KeyCode::KEY_G:
            return harvestCrop(context.playerPos, context.scene);
            
        case EventKeyboard::KeyCode::KEY_ENTER:
        case EventKeyboard::KeyCode::KEY_KP_ENTER:
            return handleEnterInteraction(context);
            
        default:
            return false;
    }
}

bool SceneActionHandler::handleBeachActions(EventKeyboard::KeyCode keyCode, const GameContext& context) {
    switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_H:
            return startFishing(context.playerPos, context.scene);
            
        case EventKeyboard::KeyCode::KEY_ENTER:
        case EventKeyboard::KeyCode::KEY_KP_ENTER:
            return handleEnterInteraction(context);
            
        default:
            return false;
    }
}

bool SceneActionHandler::handleCaveActions(EventKeyboard::KeyCode keyCode, const GameContext& context) {
    switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_M:
            return mineOre(context.playerPos, context.scene);
            
        case EventKeyboard::KeyCode::KEY_ENTER:
        case EventKeyboard::KeyCode::KEY_KP_ENTER:
            return handleEnterInteraction(context);
            
        default:
            return false;
    }
}

bool SceneActionHandler::handleTownActions(EventKeyboard::KeyCode keyCode, const GameContext& context) {
    switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_ENTER:
        case EventKeyboard::KeyCode::KEY_KP_ENTER:
            return handleEnterInteraction(context);
            
        default:
            return false;
    }
}

bool SceneActionHandler::handleHouseActions(EventKeyboard::KeyCode keyCode, const GameContext& context) {
    switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_ENTER:
        case EventKeyboard::KeyCode::KEY_KP_ENTER:
            return handleEnterInteraction(context);
            
        default:
            return false;
    }
}

bool SceneActionHandler::handleForestActions(EventKeyboard::KeyCode keyCode, const GameContext& context) {
    switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_ENTER:
        case EventKeyboard::KeyCode::KEY_KP_ENTER:
            return handleEnterInteraction(context);
            
        default:
            return false;
    }
}

bool SceneActionHandler::handleBarnActions(EventKeyboard::KeyCode keyCode, const GameContext& context) {
    switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_ENTER:
        case EventKeyboard::KeyCode::KEY_KP_ENTER:
            return handleEnterInteraction(context);
            
        default:
            return false;
    }
}

bool SceneActionHandler::handleEnterInteraction(const GameContext& context) {
    if (!context.canPerformGameAction()) {
        return false;
    }
    
    logDebug("Enter key interaction in scene: " + context.currentScene);
    
    // 这里可以添加具体的交互逻辑，比如：
    // - 与NPC对话
    // - 打开门
    // - 使用物品
    // - 检查物体
    
    // 目前暂时只记录日志，具体逻辑可以后续添加
    CCLOG("Enter key pressed in %s", context.currentScene.c_str());
    
    return true;
}

bool SceneActionHandler::plantCrop(const cocos2d::Vec2& playerPos, cocos2d::Scene* scene) {
    if (!hasEnoughEnergy(5)) {
        logDebug("Not enough energy to plant crop");
        return false;
    }
    
    logDebug("Planting crop at position: (" + 
             std::to_string(playerPos.x) + ", " + 
             std::to_string(playerPos.y) + ")");
    
    // 消耗体力
    consumeEnergy(5);
    
    // 这里可以添加具体的种植逻辑
    CCLOG("Planting crop at (%.2f, %.2f)", playerPos.x, playerPos.y);
    
    return true;
}

bool SceneActionHandler::waterCrop(const cocos2d::Vec2& playerPos, cocos2d::Scene* scene) {
    if (!hasEnoughEnergy(3)) {
        logDebug("Not enough energy to water crop");
        return false;
    }
    
    logDebug("Watering crop at position: (" + 
             std::to_string(playerPos.x) + ", " + 
             std::to_string(playerPos.y) + ")");
    
    // 消耗体力
    consumeEnergy(3);
    
    // 这里可以添加具体的浇水逻辑
    CCLOG("Watering crop at (%.2f, %.2f)", playerPos.x, playerPos.y);
    
    return true;
}

bool SceneActionHandler::harvestCrop(const cocos2d::Vec2& playerPos, cocos2d::Scene* scene) {
    if (!hasEnoughEnergy(2)) {
        logDebug("Not enough energy to harvest crop");
        return false;
    }
    
    logDebug("Harvesting crop at position: (" + 
             std::to_string(playerPos.x) + ", " + 
             std::to_string(playerPos.y) + ")");
    
    // 消耗体力
    consumeEnergy(2);
    
    // 这里可以添加具体的收割逻辑
    CCLOG("Harvesting crop at (%.2f, %.2f)", playerPos.x, playerPos.y);
    
    return true;
}

bool SceneActionHandler::startFishing(const cocos2d::Vec2& playerPos, cocos2d::Scene* scene) {
    if (!hasEnoughEnergy(10)) {
        logDebug("Not enough energy to start fishing");
        return false;
    }
    
    // 检查是否已经有钓鱼游戏在进行
    if (scene && scene->getChildByName("FishingGameLayer")) {
        logDebug("Fishing game already active");
        return false;
    }
    
    logDebug("Starting fishing at position: (" + 
             std::to_string(playerPos.x) + ", " + 
             std::to_string(playerPos.y) + ")");
    
    // 消耗体力
    consumeEnergy(10);
    
    // 创建钓鱼游戏
    if (scene) {
        auto fishingGame = FishingGame::create(playerPos);
        scene->addChild(fishingGame, 10, "FishingGameLayer");
        CCLOG("Started fishing game at (%.2f, %.2f)", playerPos.x, playerPos.y);
    }
    
    return true;
}

bool SceneActionHandler::mineOre(const cocos2d::Vec2& playerPos, cocos2d::Scene* scene) {
    if (!hasEnoughEnergy(8)) {
        logDebug("Not enough energy to mine ore");
        return false;
    }
    
    logDebug("Mining ore at position: (" + 
             std::to_string(playerPos.x) + ", " + 
             std::to_string(playerPos.y) + ")");
    
    // 消耗体力
    consumeEnergy(8);
    
    // 这里可以添加具体的挖矿逻辑
    CCLOG("Mining ore at (%.2f, %.2f)", playerPos.x, playerPos.y);
    
    return true;
}

bool SceneActionHandler::hasEnoughEnergy(int requiredEnergy) {
    return strength >= requiredEnergy;
}

void SceneActionHandler::consumeEnergy(int energyCost) {
    strength = std::max(0, strength - energyCost);
    
    // 更新能量系统
    EnergySystem::getInstance()->setEnergy(strength);
    
    // 更新时间UI显示
    if (TimeUI) {
        TimeUI->UpdateEnergy();
    }
    
    logDebug("Energy consumed: " + std::to_string(energyCost) + 
             ", Remaining: " + std::to_string(strength));
}
