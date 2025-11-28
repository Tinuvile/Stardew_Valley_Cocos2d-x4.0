#ifndef __UI_HANDLER_H__
#define __UI_HANDLER_H__

#include "InputHandler.h"

/**
 * UI界面控制输入处理器
 * 负责处理所有与用户界面相关的按键输入
 */
class UIHandler : public InputHandler {
public:
    UIHandler();
    virtual ~UIHandler() = default;
    
    /**
     * 处理按键按下事件
     * 主要处理ESC键（背包）、E键（吃食物）等UI相关按键
     */
    bool handleKeyPressed(EventKeyboard::KeyCode keyCode, Event* event, const GameContext& context) override;
    
    /**
     * 处理按键释放事件
     */
    bool handleKeyReleased(EventKeyboard::KeyCode keyCode, Event* event, const GameContext& context) override;
    
    /**
     * 获取处理器类型名称
     */
    std::string getHandlerType() const override { return "UIHandler"; }

private:
    /**
     * 处理ESC键 - 打开/关闭背包
     * @param context 游戏上下文
     * @return 是否成功处理
     */
    bool handleEscapeKey(const GameContext& context);
    
    /**
     * 处理E键 - 吃食物
     * @param context 游戏上下文
     * @return 是否成功处理
     */
    bool handleEatFood(const GameContext& context);
    
    /**
     * 打开背包界面
     * @param sceneName 当前场景名称
     * @param scene 当前场景对象
     * @return 是否成功打开
     */
    bool openInventoryUI(const std::string& sceneName, cocos2d::Scene* scene);
    
    /**
     * 关闭当前UI界面
     * @param scene 当前场景对象
     * @param uiName 要关闭的UI名称
     * @return 是否成功关闭
     */
    bool closeUI(cocos2d::Scene* scene, const std::string& uiName);
    
    /**
     * 检查是否有UI界面当前打开
     * @param context 游戏上下文
     * @return 是否有UI打开
     */
    bool hasOpenUI(const GameContext& context);
    
    // E键按下状态，防止重复触发
    bool isEKeyPressed;
};

#endif // __UI_HANDLER_H__
