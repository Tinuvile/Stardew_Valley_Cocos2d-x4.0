#ifndef __GLOBAL_ACTION_HANDLER_H__
#define __GLOBAL_ACTION_HANDLER_H__

#include "InputHandler.h"

/**
 * 全局动作输入处理器
 * 作为责任链的最后一环，处理全局性的按键操作
 */
class GlobalActionHandler : public InputHandler {
public:
    GlobalActionHandler();
    virtual ~GlobalActionHandler() = default;
    
    /**
     * 处理按键按下事件
     * 处理全局按键，如F1(帮助)、F12(截图)等
     */
    bool handleKeyPressed(EventKeyboard::KeyCode keyCode, Event* event, const GameContext& context) override;
    
    /**
     * 处理按键释放事件
     */
    bool handleKeyReleased(EventKeyboard::KeyCode keyCode, Event* event, const GameContext& context) override;
    
    /**
     * 获取处理器类型名称
     */
    std::string getHandlerType() const override { return "GlobalActionHandler"; }

private:
    /**
     * 显示帮助信息
     * @return 是否成功显示
     */
    bool showHelp();
    
    /**
     * 截图功能
     * @return 是否成功截图
     */
    bool takeScreenshot();
    
    /**
     * 显示调试信息
     * @return 是否成功显示
     */
    bool showDebugInfo();
    
    /**
     * 切换全屏模式
     * @return 是否成功切换
     */
    bool toggleFullscreen();
    
    /**
     * 暂停/恢复游戏
     * @return 是否成功切换暂停状态
     */
    bool togglePause();
    
    /**
     * 显示游戏统计信息
     * @return 是否成功显示
     */
    bool showGameStats();
    
    /**
     * 快速保存游戏
     * @return 是否成功保存
     */
    bool quickSave();
    
    /**
     * 快速加载游戏
     * @return 是否成功加载
     */
    bool quickLoad();
    
    // 调试和统计相关
    bool isDebugMode;
    int unhandledKeyCount;
    std::vector<EventKeyboard::KeyCode> recentUnhandledKeys;
    
    /**
     * 记录未处理的按键
     * @param keyCode 按键代码
     */
    void recordUnhandledKey(EventKeyboard::KeyCode keyCode);
    
    /**
     * 输出调试统计信息
     */
    void printDebugStats();
};

#endif // __GLOBAL_ACTION_HANDLER_H__
