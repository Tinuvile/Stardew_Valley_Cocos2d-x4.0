// ClosableUI.h - 可关闭UI基类
// 提供ESC键关闭功能的通用基类，避免代码重复
#ifndef __CLOSABLE_UI_H__
#define __CLOSABLE_UI_H__

#include "cocos2d.h"

USING_NS_CC;

/**
 * @class ClosableUI
 * @brief 可关闭的UI基类
 *
 * 为所有需要ESC键关闭功能的UI提供统一的实现
 * 子类只需继承此类并在init()中调用setupEscCloseListener()即可
 *
 * @usage
 * class MyUI : public ClosableUI {
 * public:
 *     virtual bool init() override {
 *         if (!ClosableUI::init()) return false;
 *         setupEscCloseListener();  // 启用ESC键关闭
 *         return true;
 *     }
 * };
 */
class ClosableUI : public cocos2d::Layer {
public:
    /**
     * @brief 默认构造函数
     */
    ClosableUI();

    /**
     * @brief 默认析构函数
     */
    virtual ~ClosableUI();

    /**
     * @brief 初始化方法
     */
    virtual bool init() override;

protected:
    /**
     * @brief 设置ESC键关闭监听器
     *
     * 子类在init()方法中调用此方法来启用ESC键关闭功能
     * 按下ESC键后会调用onEscPressed()方法
     */
    void setupEscCloseListener();

    /**
     * @brief ESC键按下时的回调方法
     *
     * 默认行为是移除当前UI (this->removeFromParent())
     * 子类可以重写此方法来实现自定义的关闭逻辑
     * 例如：显示确认对话框、保存数据等
     */
    virtual void onEscPressed();

private:
    EventListenerKeyboard* m_keyboardListener;  // 键盘监听器
};

#endif // __CLOSABLE_UI_H__
