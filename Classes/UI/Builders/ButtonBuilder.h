// ButtonBuilder.h - 简化版按钮建造者
#ifndef __BUTTON_BUILDER_H__
#define __BUTTON_BUILDER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "../Core/UITheme.h"
#include <string>
#include <functional>

USING_NS_CC;

/**
 * @class ButtonBuilder
 * @brief 按钮建造者，使用链式调用简化Button创建
 */
class ButtonBuilder {
public:
    ButtonBuilder();
    ~ButtonBuilder();

    // 设置正常状态纹理
    ButtonBuilder& setNormalTexture(const std::string& filename);

    // 设置按下状态纹理（可选）
    ButtonBuilder& setPressedTexture(const std::string& filename);

    // 设置禁用状态纹理（可选）
    ButtonBuilder& setDisabledTexture(const std::string& filename);

    // 设置缩放（使用原始代码的方式：scale / 某个值）
    ButtonBuilder& setScale(float scale);
    ButtonBuilder& setScale(float scaleX, float scaleY);

    // 自动计算缩放（根据屏幕适配）
    ButtonBuilder& setAutoScale(float divisor);  // 例如：setAutoScale(8.0) 替代原来的 scale/8.0

    // 设置位置
    ButtonBuilder& setPosition(const Vec2& position);
    ButtonBuilder& setPosition(float x, float y);
    ButtonBuilder& setRelativePosition(float xPercent, float yPercent);

    // 设置锚点
    ButtonBuilder& setAnchorPoint(const Vec2& anchor);
    ButtonBuilder& setAnchorPoint(float x, float y);

    // 设置Z顺序
    ButtonBuilder& setZOrder(int zOrder);

    // 设置标签
    ButtonBuilder& setTag(int tag);

    // 设置可见性
    ButtonBuilder& setVisible(bool visible);

    // 设置启用状态
    ButtonBuilder& setEnabled(bool enabled);

    // 添加到父节点
    ButtonBuilder& addToParent(Node* parent);

    // 设置点击回调
    ButtonBuilder& setClickCallback(const std::function<void(Ref*)>& callback);

    // 设置悬停效果
    ButtonBuilder& setHoverEffect(float hoverScale = 1.2f);

    // 自适应缩放
    ButtonBuilder& setAdaptiveScale(float targetWidthPercent, float targetHeightPercent);

    // 构建
    ui::Button* build();

private:
    ui::Button* m_button;
    UITheme* m_theme;

    // 构建参数
    std::string m_normalTexture;
    std::string m_pressedTexture;
    std::string m_disabledTexture;
    Vec2 m_position;
    Vec2 m_anchorPoint;
    float m_scaleX;
    float m_scaleY;
    int m_zOrder;
    int m_tag;
    bool m_visible;
    bool m_enabled;
    Node* m_parent;

    bool m_hasNormalTexture;
    bool m_hasPosition;
    bool m_hasScale;
    bool m_hasAnchor;

    std::function<void(Ref*)> m_clickCallback;
    bool m_hasHoverEffect;
    float m_hoverScale;
    float m_normalScale;
};

#endif // __BUTTON_BUILDER_H__