#ifndef __GAME_CONTEXT_H__
#define __GAME_CONTEXT_H__

#include "cocos2d.h"
#include <string>

USING_NS_CC;

// 前向声明 - 避免循环包含
class Player;

/**
 * 游戏上下文结构，包含输入处理所需的所有状态信息
 */
struct GameContext {
    std::string currentScene;     // 当前场景名称 (farm, Cave, Beach, Town等)
    cocos2d::Scene* scene;       // 当前场景指针
    Player* player;              // 玩家对象指针
    bool isUIOpen;               // 是否有UI界面打开
    std::string activeUI;        // 当前活跃的UI名称
    cocos2d::Vec2 playerPos;     // 玩家当前位置
    bool canMove;                // 玩家是否可以移动
    bool isGamePaused;           // 游戏是否暂停
    
    // 构造函数，设置默认值
    GameContext() : 
        currentScene(""),
        scene(nullptr),
        player(nullptr),
        isUIOpen(false),
        activeUI(""),
        playerPos(Vec2::ZERO),
        canMove(true),
        isGamePaused(false)
    {}
    
    // 更新玩家位置（通常每帧调用）
    void updatePlayerPosition();
    
    // 设置玩家引用
    void setPlayer(Player* playerPtr) {
        player = playerPtr;
    }
    
    // 设置UI状态
    void setUIState(bool open, const std::string& uiName = "") {
        isUIOpen = open;
        activeUI = open ? uiName : "";
        canMove = !open && !isGamePaused;
    }
    
    // 设置场景信息
    void setSceneInfo(const std::string& sceneName, cocos2d::Scene* scenePtr) {
        currentScene = sceneName;
        scene = scenePtr;
    }
    
    // 检查是否可以进行游戏内操作
    bool canPerformGameAction() const {
        return !isUIOpen && !isGamePaused && canMove;
    }
};

#endif // __GAME_CONTEXT_H__
