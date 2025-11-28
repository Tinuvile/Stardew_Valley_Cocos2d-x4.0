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
        "=== 游戏控制帮助 ===\n"
        "移动: 方向键 ↑↓←→\n"
        "背包: ESC键\n"
        "吃食物: E键\n"
        "\n=== 农场操作 ===\n"
        "种植: P键\n"
        "浇水: W键\n"
        "收割: G键\n"
        "\n=== 其他操作 ===\n"
        "钓鱼: H键 (海滩)\n"
        "挖矿: M键 (洞穴)\n"
        "交互: ENTER键\n"
        "\n=== 全局快捷键 ===\n"
        "帮助: F1\n"
        "统计: F2\n"
        "调试: F3\n"
        "暂停: 空格键\n"
        "截图: F12\n";
    
    CCLOG("%s", helpText.c_str());
    
    return true;
}

bool GlobalActionHandler::takeScreenshot() {
    logDebug("Taking screenshot");
    
    // 获取当前时间作为文件名
    time_t now = time(0);
    tm* ltm = localtime(&now);
    
    std::ostringstream filename;
    filename << "screenshot_" 
             << (1900 + ltm->tm_year) 
             << std::setfill('0') << std::setw(2) << (1 + ltm->tm_mon)
             << std::setfill('0') << std::setw(2) << ltm->tm_mday << "_"
             << std::setfill('0') << std::setw(2) << ltm->tm_hour
             << std::setfill('0') << std::setw(2) << ltm->tm_min
             << std::setfill('0') << std::setw(2) << ltm->tm_sec
             << ".png";
    
    // 使用Cocos2d-x的截图功能
    auto director = cocos2d::Director::getInstance();
    if (director) {
        cocos2d::utils::captureScreen([filename](bool succeed, const std::string& outputFile) {
            if (succeed) {
                CCLOG("Screenshot saved: %s", outputFile.c_str());
            } else {
                CCLOG("Screenshot failed");
            }
        }, filename.str());
        
        return true;
    }
    
    return false;
}

bool GlobalActionHandler::showDebugInfo() {
    logDebug("Showing debug information");
    
    auto inputManager = InputManager::getInstance();
    const auto& context = inputManager->getGameContext();
    
    std::string debugInfo = 
        "=== 调试信息 ===\n"
        "当前场景: " + context.currentScene + "\n"
        "玩家位置: (" + std::to_string(context.playerPos.x) + ", " + std::to_string(context.playerPos.y) + ")\n"
        "UI状态: " + (context.isUIOpen ? ("打开 - " + context.activeUI) : "关闭") + "\n"
        "可移动: " + std::string(context.canMove ? "是" : "否") + "\n"
        "游戏暂停: " + std::string(context.isGamePaused ? "是" : "否") + "\n"
        "未处理按键数: " + std::to_string(unhandledKeyCount) + "\n";
    
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
        "=== 游戏统计 ===\n"
        "当前天数: " + std::to_string(day) + "\n"
        "剩余时间: " + std::to_string(remainingTime) + "\n"
        "金币: " + std::to_string(GoldAmount) + "\n"
        "体力: " + std::to_string(strength) + "/100\n"
        "季节: " + Season + "\n"
        "天气: " + Weather + "\n";
    
    CCLOG("%s", statsInfo.c_str());
    
    return true;
}

bool GlobalActionHandler::quickSave() {
    logDebug("Quick save requested");
    
    // 这里应该实现快速保存逻辑
    CCLOG("Quick save: 功能待实现");
    
    return true;
}

bool GlobalActionHandler::quickLoad() {
    logDebug("Quick load requested");
    
    // 这里应该实现快速加载逻辑
    CCLOG("Quick load: 功能待实现");
    
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
    
    std::ostringstream oss;
    oss << "Recent unhandled keys: ";
    for (size_t i = 0; i < recentUnhandledKeys.size(); ++i) {
        if (i > 0) oss << ", ";
        oss << static_cast<int>(recentUnhandledKeys[i]);
    }
    
    CCLOG("%s", oss.str().c_str());
}
