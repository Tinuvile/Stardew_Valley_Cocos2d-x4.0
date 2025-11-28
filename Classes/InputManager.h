#ifndef __INPUT_MANAGER_H__
#define __INPUT_MANAGER_H__

#include "cocos2d.h"
#include "InputHandler.h"
#include "GameContext.h"
#include <memory>

USING_NS_CC;

/**
 * 输入管理器单例类
 * 负责管理整个输入处理责任链和游戏上下文
 */
class InputManager {
public:
    /**
     * 获取单例实例
     */
    static InputManager* getInstance();
    
    /**
     * 释放单例实例
     */
    static void destroyInstance();
    
    /**
     * 初始化输入管理器
     * 设置责任链和键盘监听器
     */
    void initialize();
    
    /**
     * 更新游戏上下文信息
     * @param sceneName 当前场景名称
     * @param scene 当前场景指针
     */
    void updateGameContext(const std::string& sceneName, cocos2d::Scene* scene);
    
    /**
     * 设置UI状态
     * @param isOpen UI是否打开
     * @param uiName UI名称
     */
    void setUIState(bool isOpen, const std::string& uiName = "");
    
    /**
     * 设置游戏暂停状态
     * @param paused 是否暂停
     */
    void setGamePaused(bool paused);
    
    // 不再需要场景相关的注册方法，已改用全局监听器
    // void registerWithScene(cocos2d::Scene* scene);
    // void unregisterFromScene(cocos2d::Scene* scene);
    
    /**
     * 获取当前游戏上下文（只读）
     */
    const GameContext& getGameContext() const { return gameContext; }
    
    /**
     * 打开背包界面
     * @param sceneName 当前场景名称
     */
    void openInventory(const std::string& sceneName);
    
    /**
     * 关闭当前UI
     */
    void closeCurrentUI();
    
    /**
     * 更新玩家对象引用
     * @param player 玩家对象指针
     */
    void setPlayer(Player* player);

private:
    InputManager();
    ~InputManager();
    
    // 禁用拷贝构造和赋值操作
    InputManager(const InputManager&) = delete;
    InputManager& operator=(const InputManager&) = delete;
    
    /**
     * 设置输入处理责任链
     */
    void setupHandlerChain();
    
    /**
     * 设置键盘监听器
     */
    void setupKeyboardListener();
    
    /**
     * 按键按下回调函数
     */
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    
    /**
     * 按键释放回调函数
     */
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
    
    /**
     * 每帧更新游戏上下文
     */
    void update(float deltaTime);

private:
    static InputManager* instance;
    
    GameContext gameContext;
    std::shared_ptr<InputHandler> handlerChain;
    cocos2d::EventListenerKeyboard* keyboardListener;
    
    bool isInitialized;
    // cocos2d::Scene* currentRegisteredScene;  // 不再需要跟踪当前场景
    
    // 用于调试的统计信息
    int totalKeyPressedCount;
    int handledKeyCount;
};

#endif // __INPUT_MANAGER_H__
