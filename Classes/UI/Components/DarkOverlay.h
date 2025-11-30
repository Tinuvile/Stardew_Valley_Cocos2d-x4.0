// DarkOverlay.h - 半透明遮罩层组件
// 统一管理UI背景遮罩的可复用组件
#ifndef __DARK_OVERLAY_H__
#define __DARK_OVERLAY_H__

#include "cocos2d.h"
#include "../Core/UITheme.h"
#include "../Core/UIConfig.h"

USING_NS_CC;

/**
 * @class DarkOverlay
 * @brief 半透明遮罩层 - 用于UI背景的暗色遮罩
 *
 * 替代了所有UI中重复的darkLayer创建代码
 */
class DarkOverlay : public LayerColor {
public:
    // 创建方法
    static DarkOverlay* create(const std::string& sceneName, GLubyte opacity = 120);

    // 初始化
    virtual bool init(const std::string& sceneName, GLubyte opacity);

    // 更新位置（根据玩家位置）
    void updatePosition(const Vec2& playerPosition);

private:
    DarkOverlay();
    virtual ~DarkOverlay();

private:
    std::string m_sceneName;
    UITheme* m_theme;
    UIConfig* m_config;
};

#endif // __DARK_OVERLAY_H__
