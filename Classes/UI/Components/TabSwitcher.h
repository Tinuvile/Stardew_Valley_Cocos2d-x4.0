// TabSwitcher.h - 标签切换器组件
// 统一管理4个UI切换按钮的可复用组件
#ifndef __TAB_SWITCHER_H__
#define __TAB_SWITCHER_H__

#include "cocos2d.h"
#include "../Core/UITheme.h"
#include "../Core/UIConfig.h"
#include <string>
#include <functional>

USING_NS_CC;

/**
 * @class TabSwitcher
 * @brief 标签切换器 - 统一的4按钮UI切换组件
 *
 * 这个组件替代了所有UI中重复的Buttons_switching代码
 * 提供统一的背包、技能树、亲密度、退出按钮
 */
class TabSwitcher : public Node {
public:
    // 标签类型
    enum class TabType {
        INVENTORY,   // 背包
        SKILL_TREE,  // 技能树
        INTIMACY,    // 亲密度
        QUIT         // 退出
    };

    // 创建方法
    static TabSwitcher* create(const std::string& currentSceneName, TabType activeTab = TabType::INVENTORY);

    // 初始化
    virtual bool init(const std::string& currentSceneName, TabType activeTab);

    // 设置按钮点击回调
    void setTabCallback(TabType tab, const std::function<void()>& callback);

    // 设置当前激活的标签
    void setActiveTab(TabType tab);

    // 更新位置（根据玩家位置）
    void updatePosition(const Vec2& playerPosition);

private:
    TabSwitcher();
    virtual ~TabSwitcher();

    // 创建按钮
    void createTabButtons();

    // 更新按钮状态
    void updateButtonStates();

    // 获取按钮位置
    Vec2 getButtonPosition(int index, const Vec2& basePosition);

    // 默认的标签点击处理
    void onTabClicked(TabType tab);

private:
    std::string m_sceneName;
    TabType m_activeTab;
    UITheme* m_theme;
    UIConfig* m_config;

    // 按钮精灵
    Sprite* m_bagButton;
    Sprite* m_skillButton;
    Sprite* m_intimacyButton;
    Sprite* m_quitButton;

    // 自定义回调
    std::map<TabType, std::function<void()>> m_callbacks;

    // 基准位置
    Vec2 m_basePosition;
};

#endif // __TAB_SWITCHER_H__
