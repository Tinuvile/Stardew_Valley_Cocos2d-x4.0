// SpriteBuilder.h - 简化版精灵建造者
#ifndef __SPRITE_BUILDER_H__
#define __SPRITE_BUILDER_H__

#include "cocos2d.h"
#include "../Core/UITheme.h"
#include <string>
#include <functional>

USING_NS_CC;

/**
 * @class SpriteBuilder
 * @brief 精灵建造者，使用链式调用简化Sprite创建
 */
class SpriteBuilder {
public:
    SpriteBuilder();
    ~SpriteBuilder();

    // 设置纹理
    SpriteBuilder& setTexture(const std::string& filename);

    // 设置缩放（使用原始代码的方式：scale / 某个值）
    SpriteBuilder& setScale(float scale);
    SpriteBuilder& setScale(float scaleX, float scaleY);

    // 自动计算缩放（根据屏幕适配）
    SpriteBuilder& setAutoScale(float divisor);  // 例如：setAutoScale(16.5) 替代原来的 scale/16.5

    // 设置位置
    SpriteBuilder& setPosition(const Vec2& position);
    SpriteBuilder& setPosition(float x, float y);
    SpriteBuilder& setRelativePosition(float xPercent, float yPercent);

    // 设置锚点
    SpriteBuilder& setAnchorPoint(const Vec2& anchor);
    SpriteBuilder& setAnchorPoint(float x, float y);

    // 设置Z顺序
    SpriteBuilder& setZOrder(int zOrder);

    // 设置透明度
    SpriteBuilder& setOpacity(GLubyte opacity);

    // 设置可见性
    SpriteBuilder& setVisible(bool visible);

    // 设置标签
    SpriteBuilder& setTag(int tag);

    // 添加到父节点
    SpriteBuilder& addToParent(Node* parent);

    // 自适应缩放
    SpriteBuilder& setAdaptiveScale(float targetWidthPercent, float targetHeightPercent);

    // 添加点击事件
    SpriteBuilder& setClickCallback(const std::function<void(Sprite*)>& callback);

    // 添加鼠标悬停效果
    SpriteBuilder& setHoverEffect(float hoverScale = 1.2f);

    // 构建
    Sprite* build();

private:
    Sprite* m_sprite;
    UITheme* m_theme;

    Vec2 m_position;
    Vec2 m_anchorPoint;
    float m_scaleX;
    float m_scaleY;
    int m_zOrder;
    GLubyte m_opacity;
    bool m_visible;
    int m_tag;
    Node* m_parent;

    bool m_hasPosition;
    bool m_hasScale;
    bool m_hasAnchor;

    std::function<void(Sprite*)> m_clickCallback;
    bool m_hasHoverEffect;
    float m_hoverScale;
    float m_normalScale;
};

#endif // __SPRITE_BUILDER_H__
