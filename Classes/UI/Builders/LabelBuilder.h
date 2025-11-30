// LabelBuilder.h - 简化版标签建造者
#ifndef __LABEL_BUILDER_H__
#define __LABEL_BUILDER_H__

#include "cocos2d.h"
#include "../Core/UITheme.h"
#include <string>

USING_NS_CC;

/**
 * @class LabelBuilder
 * @brief 标签建造者，使用链式调用简化Label创建
 */
class LabelBuilder {
public:
    LabelBuilder();
    ~LabelBuilder();

    // 设置文本
    LabelBuilder& setText(const std::string& text);

    // 设置字体（直接使用字符串和数字，不用枚举）
    LabelBuilder& setFont(const std::string& fontName, float fontSize);

    // 设置颜色（直接使用Color，不用枚举）
    LabelBuilder& setColor(const Color4B& color);
    LabelBuilder& setColor(const Color3B& color);

    // 设置位置
    LabelBuilder& setPosition(const Vec2& position);
    LabelBuilder& setPosition(float x, float y);
    LabelBuilder& setRelativePosition(float xPercent, float yPercent);

    // 设置锚点
    LabelBuilder& setAnchorPoint(const Vec2& anchor);
    LabelBuilder& setAnchorPoint(float x, float y);

    // 设置Z顺序
    LabelBuilder& setZOrder(int zOrder);

    // 设置透明度
    LabelBuilder& setOpacity(GLubyte opacity);

    // 设置标签
    LabelBuilder& setTag(int tag);

    // 设置文本对齐
    LabelBuilder& setAlignment(TextHAlignment hAlignment, TextVAlignment vAlignment = TextVAlignment::CENTER);

    // 设置最大宽度
    LabelBuilder& setMaxWidth(float width);

    // 添加到父节点
    LabelBuilder& addToParent(Node* parent);

    // 构建
    Label* build();

private:
    Label* m_label;
    UITheme* m_theme;

    std::string m_text;
    std::string m_fontName;
    float m_fontSize;
    Color4B m_color;

    Vec2 m_position;
    Vec2 m_anchorPoint;
    int m_zOrder;
    GLubyte m_opacity;
    int m_tag;
    Node* m_parent;

    bool m_hasPosition;
    bool m_hasColor;
    bool m_hasFont;

    TextHAlignment m_hAlignment;
    TextVAlignment m_vAlignment;
    float m_maxWidth;
    bool m_hasMaxWidth;
};

#endif // __LABEL_BUILDER_H__
