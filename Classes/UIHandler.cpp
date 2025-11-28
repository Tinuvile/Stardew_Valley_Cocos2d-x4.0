#include "UIHandler.h"
#include "InputManager.h"
#include "InventoryUI.h"
#include "mini_bag.h"
#include "Food.h"
#include "Player.h"
#include "AppDelegate.h"
#include "EnergySystem.h"
#include "Timesystem.h"

UIHandler::UIHandler() : isEKeyPressed(false) {
    // 构造函数
}

bool UIHandler::handleKeyPressed(EventKeyboard::KeyCode keyCode, Event* event, const GameContext& context) {
    switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_ESCAPE:
            return handleEscapeKey(context);
            
        case EventKeyboard::KeyCode::KEY_E:
            if (!isEKeyPressed) {
                isEKeyPressed = true;
                return handleEatFood(context);
            }
            return true; // 已经处理过了，防止重复触发
            
        default:
            return passToNext(keyCode, event, context);
    }
}

bool UIHandler::handleKeyReleased(EventKeyboard::KeyCode keyCode, Event* event, const GameContext& context) {
    switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_E:
            isEKeyPressed = false;
            return true;
            
        default:
            return passReleaseToNext(keyCode, event, context);
    }
}

bool UIHandler::handleEscapeKey(const GameContext& context) {
    if (!context.scene) {
        logDebug("No scene available for UI operations");
        return false;
    }
    
    // 如果当前有UI打开，则关闭它
    if (context.isUIOpen && !context.activeUI.empty()) {
        bool success = closeUI(context.scene, context.activeUI);
        if (success) {
            InputManager::getInstance()->setUIState(false);
            logDebug("Closed UI: " + context.activeUI);
        }
        return success;
    }
    
    // 如果没有UI打开，则打开背包
    bool success = openInventoryUI(context.currentScene, context.scene);
    if (success) {
        InputManager::getInstance()->setUIState(true, "InventoryUI");
        logDebug("Opened inventory for scene: " + context.currentScene);
    }
    return success;
}

bool UIHandler::handleEatFood(const GameContext& context) {
    // 检查是否有UI打开或游戏不可操作
    if (!context.canPerformGameAction()) {
        return passToNext(EventKeyboard::KeyCode::KEY_E, nullptr, context);
    }
    
    // 从mini_bag获取当前选中的物品
    if (!miniBag) {
        logDebug("Mini bag not available");
        return false;
    }
    
    auto selectedItem = miniBag->getSelectedItem();
    if (!selectedItem) {
        logDebug("No item selected in mini bag");
        return false;
    }
    
    // 尝试转换为Food类型
    auto foodItem = std::dynamic_pointer_cast<Food>(selectedItem);
    if (!foodItem) {
        logDebug("Selected item is not food");
        return false;
    }
    
    // 吃食物 - 恢复体力
    int energyGain = foodItem->GetEnergy();
    strength = std::min(100, strength + energyGain);
    
    // 更新能量系统
    EnergySystem::getInstance()->setEnergy(strength);
    
    // 从背包中移除食物
    if (inventory) {
        inventory->RemoveItem(*foodItem);
        inventory->DisplayPackageInCCLOG();
    }
    
    // 更新时间UI的能量显示
    if (TimeUI) {
        TimeUI->UpdateEnergy();
    }
    
    logDebug("Ate food: " + foodItem->GetName() + ", Energy gain: " + std::to_string(energyGain));
    CCLOG("EAT FOOD! Energy: %d", strength);
    
    return true;
}

bool UIHandler::openInventoryUI(const std::string& sceneName, cocos2d::Scene* scene) {
    if (!scene || !inventory) {
        logDebug("Scene or inventory not available");
        return false;
    }
    
    // 检查是否已经有背包界面打开
    auto existingUI = scene->getChildByName("InventoryUI");
    if (existingUI) {
        logDebug("Inventory UI already exists");
        return false;
    }
    
    // 创建新的背包界面
    auto inventoryUI = InventoryUI::create(inventory, sceneName);
    if (!inventoryUI) {
        logDebug("Failed to create inventory UI");
        return false;
    }
    
    // 设置名称以便后续查找
    inventoryUI->setName("InventoryUI");
    
    // 添加到场景中，使用高层级确保显示在最上方
    scene->addChild(inventoryUI, 20);
    
    logDebug("Successfully opened inventory UI");
    return true;
}

bool UIHandler::closeUI(cocos2d::Scene* scene, const std::string& uiName) {
    if (!scene || uiName.empty()) {
        logDebug("Scene or UI name not available");
        return false;
    }
    
    // 查找UI节点
    auto uiNode = scene->getChildByName(uiName);
    if (!uiNode) {
        logDebug("UI node not found: " + uiName);
        return false;
    }
    
    // 移除UI节点
    scene->removeChild(uiNode, true);
    
    logDebug("Successfully closed UI: " + uiName);
    return true;
}

bool UIHandler::hasOpenUI(const GameContext& context) {
    return context.isUIOpen && !context.activeUI.empty();
}
