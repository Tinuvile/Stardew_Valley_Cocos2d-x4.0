#include "GlobalActionHandler.h"
#include "InputManager.h"
#include "AppDelegate.h"
#include <ctime>
#include <iomanip>
#include <sstream>

GlobalActionHandler::GlobalActionHandler() 
    : isDebugMode(false)
    , unhandledKeyCount(0)
{
    // 构造函数
    recentUnhandledKeys.reserve(10); // 保留最近10个未处理的按键
}

bool GlobalActionHandler::handleKeyPressed(EventKeyboard::KeyCode keyCode, Event* event, const GameContext& context) {
    switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_F1:
            return showHelp();
            
        case EventKeyboard::KeyCode::KEY_F2:
            return showGameStats();
            
        case EventKeyboard::KeyCode::KEY_F3:
            isDebugMode = !isDebugMode;
            logDebug("Debug mode " + std::string(isDebugMode ? "enabled" : "disabled"));
            return true;
            
        case EventKeyboard::KeyCode::KEY_F4:
            return showDebugInfo();
            
        case EventKeyboard::KeyCode::KEY_F5:
            return quickSave();
            
        case EventKeyboard::KeyCode::KEY_F9:
            return quickLoad();
            
        case EventKeyboard::KeyCode::KEY_F11:
            return toggleFullscreen();
            
        case EventKeyboard::KeyCode::KEY_F12:
            return takeScreenshot();
            
        case EventKeyboard::KeyCode::KEY_PAUSE:
        case EventKeyboard::KeyCode::KEY_SPACE: // 空格也可以暂停
            if (context.isUIOpen) {
                // UI打开时空格不处理暂停
                recordUnhandledKey(keyCode);
                return false;
            }
            return togglePause();
            
        default:
            // 记录未处理的按键
            recordUnhandledKey(keyCode);
            
            if (isDebugMode) {
                logDebug("Unhandled key: " + std::to_string(static_cast<int>(keyCode)));
            }
            
            return false; // 表示未处理
    }
}

bool GlobalActionHandler::handleKeyReleased(EventKeyboard::KeyCode keyCode, Event* event, const GameContext& context) {
    // 全局动作处理器通常不需要处理按键释放事件
    return false;
}

bool GlobalActionHandler::showHelp() {
    logDebug("Showing help information");
    
    // 创建帮助信息字符串
    std::string helpText = 
        "=== Game Controls Help ===\n"
        "Move: Arrow Keys\n"
        "Inventory: ESC\n"
        "Eat Food: E\n"
        "\n=== Farm Operations ===\n"
        "Plant: P\n"
        "Water: W\n"
        "Harvest: G\n"
        "\n=== Other Actions ===\n"
        "Fishing: H (Beach)\n"
        "Mining: M (Cave)\n"
        "Interact: ENTER\n"
        "\n=== Global Shortcuts ===\n"
        "Help: F1\n"
        "Statistics: F2\n"
        "Debug: F3\n"
        "Pause: SPACE\n"
        "Screenshot: F12\n";
    
    CCLOG("%s", helpText.c_str());
    
    return true;
}

bool GlobalActionHandler::takeScreenshot() {
    logDebug("Taking screenshot");
    
    // Get current time for filename
    time_t now = time(0);
    tm* ltm = localtime(&now);
    
    char buffer[64];
    sprintf(buffer, "screenshot_%04d%02d%02d_%02d%02d%02d.png",
            1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday,
            ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
    
    std::string filename(buffer);
    
    // Use Cocos2d-x screenshot function
    auto director = cocos2d::Director::getInstance();
    if (director) {
        cocos2d::utils::captureScreen([filename](bool succeed, const std::string& outputFile) {
            if (succeed) {
                CCLOG("Screenshot saved: %s", outputFile.c_str());
            } else {
                CCLOG("Screenshot failed");
            }
        }, filename);
        
        return true;
    }
    
    return false;
}

bool GlobalActionHandler::showDebugInfo() {
    logDebug("Showing debug information");
    
    auto inputManager = InputManager::getInstance();
    const auto& context = inputManager->getGameContext();
    
    std::string debugInfo = 
        "=== Debug Info ===\n"
        "Current Scene: " + context.currentScene + "\n"
        "Player Position: (" + std::to_string(context.playerPos.x) + ", " + std::to_string(context.playerPos.y) + ")\n"
        "UI Status: " + (context.isUIOpen ? ("Open - " + context.activeUI) : "Closed") + "\n"
        "Can Move: " + std::string(context.canMove ? "Yes" : "No") + "\n"
        "Game Paused: " + std::string(context.isGamePaused ? "Yes" : "No") + "\n"
        "Unhandled Keys: " + std::to_string(unhandledKeyCount) + "\n";
    
    CCLOG("%s", debugInfo.c_str());
    
    printDebugStats();
    
    return true;
}

bool GlobalActionHandler::toggleFullscreen() {
    logDebug("Toggling fullscreen mode");
    
    auto director = cocos2d::Director::getInstance();
    if (director) {
        auto glView = director->getOpenGLView();
        if (glView) {
            // Cocos2d-x的全屏切换（需要平台特定实现）
            CCLOG("Fullscreen toggle requested (platform implementation required)");
            return true;
        }
    }
    
    return false;
}

bool GlobalActionHandler::togglePause() {
    logDebug("Toggling game pause");
    
    auto inputManager = InputManager::getInstance();
    const auto& context = inputManager->getGameContext();
    
    bool newPauseState = !context.isGamePaused;
    inputManager->setGamePaused(newPauseState);
    
    auto director = cocos2d::Director::getInstance();
    if (director) {
        if (newPauseState) {
            director->pause();
            CCLOG("Game paused");
        } else {
            director->resume();
            CCLOG("Game resumed");
        }
    }
    
    return true;
}

bool GlobalActionHandler::showGameStats() {
    logDebug("Showing game statistics");
    
    std::string statsInfo = 
        "=== Game Statistics ===\n"
        "Day: " + std::to_string(day) + "\n"
        "Time Left: " + std::to_string(remainingTime) + "\n"
        "Gold: " + std::to_string(GoldAmount) + "\n"
        "Energy: " + std::to_string(strength) + "/100\n"
        "Season: " + Season + "\n"
        "Weather: " + Weather + "\n";
    
    CCLOG("%s", statsInfo.c_str());
    
    return true;
}

bool GlobalActionHandler::quickSave() {
    logDebug("Quick save requested");
    
    // TODO: Implement quick save logic
    CCLOG("Quick save: Feature not implemented yet");
    
    return true;
}

bool GlobalActionHandler::quickLoad() {
    logDebug("Quick load requested");
    
    // TODO: Implement quick load logic
    CCLOG("Quick load: Feature not implemented yet");
    
    return true;
}

void GlobalActionHandler::recordUnhandledKey(EventKeyboard::KeyCode keyCode) {
    unhandledKeyCount++;
    
    // 保持最近的未处理按键记录
    if (recentUnhandledKeys.size() >= 10) {
        recentUnhandledKeys.erase(recentUnhandledKeys.begin());
    }
    recentUnhandledKeys.push_back(keyCode);
}

void GlobalActionHandler::printDebugStats() {
    if (recentUnhandledKeys.empty()) {
        CCLOG("No recent unhandled keys");
        return;
    }
    
    std::string output = "Recent unhandled keys: ";
    for (size_t i = 0; i < recentUnhandledKeys.size(); ++i) {
        if (i > 0) output += ", ";
        output += std::to_string(static_cast<int>(recentUnhandledKeys[i]));
    }
    
    CCLOG("%s", output.c_str());
}
