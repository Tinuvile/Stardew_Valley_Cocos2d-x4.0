// UITheme.h - 简化版UI工具类
// 只提供屏幕信息和基本计算，不做过度设计
#ifndef __UI_THEME_H__
#define __UI_THEME_H__

#include "cocos2d.h"

USING_NS_CC;

/**
 * @class UITheme
 * @brief 简化的UI工具类，只提供基本的屏幕信息和计算
 */
class UITheme {
public:
    static UITheme* getInstance();

    // 获取屏幕信息
    Size getVisibleSize() const;
    Vec2 getOrigin() const;
    Vec2 getCenter() const;

    // 相对位置计算（基于屏幕百分比）
    Vec2 getRelativePosition(float xPercent, float yPercent) const;

    // 计算适配缩放
    float calculateAdaptiveScale(float originalWidth, float originalHeight,
                                  float targetWidthPercent, float targetHeightPercent) const;

private:
    UITheme();
    ~UITheme();

    UITheme(const UITheme&) = delete;
    UITheme& operator=(const UITheme&) = delete;

private:
    static UITheme* s_instance;
    Size m_visibleSize;
    Vec2 m_origin;
};

#endif // __UI_THEME_H__
