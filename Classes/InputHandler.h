#ifndef __INPUT_HANDLER_H__
#define __INPUT_HANDLER_H__

#include "cocos2d.h"
#include "GameContext.h"
#include <memory>

USING_NS_CC;

/**
 * 输入处理器抽象基类
 * 实现责任链模式，每个处理器负责特定类型的输入处理
 */
class InputHandler {
public:
    virtual ~InputHandler() = default;
    
    /**
     * 处理按键按下事件
     * @param keyCode 按键代码
     * @param event 事件对象
     * @param context 游戏上下文
     * @return true表示已处理该事件，false表示未处理
     */
    virtual bool handleKeyPressed(EventKeyboard::KeyCode keyCode, Event* event, const GameContext& context) = 0;
    
    /**
     * 处理按键释放事件
     * @param keyCode 按键代码
     * @param event 事件对象
     * @param context 游戏上下文
     * @return true表示已处理该事件，false表示未处理
     */
    virtual bool handleKeyReleased(EventKeyboard::KeyCode keyCode, Event* event, const GameContext& context) = 0;
    
    /**
     * 设置责任链中的下一个处理器
     * @param next 下一个处理器
     */
    void setNext(std::shared_ptr<InputHandler> next) { 
        nextHandler = next; 
    }
    
    /**
     * 获取处理器类型名称（用于调试）
     * @return 处理器类型名称
     */
    virtual std::string getHandlerType() const = 0;

protected:
    std::shared_ptr<InputHandler> nextHandler = nullptr;
    
    /**
     * 将事件传递给责任链中的下一个处理器
     * @param keyCode 按键代码
     * @param event 事件对象
     * @param context 游戏上下文
     * @return 下一个处理器的处理结果
     */
    bool passToNext(EventKeyboard::KeyCode keyCode, Event* event, const GameContext& context) {
        if (nextHandler) {
            return nextHandler->handleKeyPressed(keyCode, event, context);
        }
        return false;
    }
    
    /**
     * 将按键释放事件传递给责任链中的下一个处理器
     */
    bool passReleaseToNext(EventKeyboard::KeyCode keyCode, Event* event, const GameContext& context) {
        if (nextHandler) {
            return nextHandler->handleKeyReleased(keyCode, event, context);
        }
        return false;
    }
    
    /**
     * 记录调试信息
     * @param message 调试消息
     */
    void logDebug(const std::string& message) const {
        CCLOG("[%s] %s", getHandlerType().c_str(), message.c_str());
    }
};

#endif // __INPUT_HANDLER_H__
