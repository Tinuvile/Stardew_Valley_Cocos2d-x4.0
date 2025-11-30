// LabelBuilder.cpp - 简化版标签建造者实现
#include "LabelBuilder.h"

LabelBuilder::LabelBuilder()
    : m_label(nullptr)
    , m_theme(UITheme::getInstance())
    , m_text("")
    , m_fontName("")
    , m_fontSize(24.0f)
    , m_color(Color4B::BLACK)
    , m_position(Vec2::ZERO)
    , m_anchorPoint(Vec2(0.5f, 0.5f))
    , m_zOrder(0)
    , m_opacity(255)
    , m_tag(0)
    , m_parent(nullptr)
    , m_hasPosition(false)
    , m_hasColor(false)
    , m_hasFont(false)
    , m_hAlignment(TextHAlignment::CENTER)
    , m_vAlignment(TextVAlignment::CENTER)
    , m_maxWidth(0.0f)
    , m_hasMaxWidth(false) {
}

LabelBuilder::~LabelBuilder() {
}

LabelBuilder& LabelBuilder::setText(const std::string& text) {
    m_text = text;
    return *this;
}

LabelBuilder& LabelBuilder::setFont(const std::string& fontName, float fontSize) {
    m_fontName = fontName;
    m_fontSize = fontSize;
    m_hasFont = true;
    return *this;
}

LabelBuilder& LabelBuilder::setColor(const Color4B& color) {
    m_color = color;
    m_hasColor = true;
    return *this;
}

LabelBuilder& LabelBuilder::setColor(const Color3B& color) {
    m_color = Color4B(color.r, color.g, color.b, 255);
    m_hasColor = true;
    return *this;
}

LabelBuilder& LabelBuilder::setRelativePosition(float xPercent, float yPercent) {
    m_position = m_theme->getRelativePosition(xPercent, yPercent);
    m_hasPosition = true;
    return *this;
}

LabelBuilder& LabelBuilder::setPosition(const Vec2& position) {
    m_position = position;
    m_hasPosition = true;
    return *this;
}

LabelBuilder& LabelBuilder::setPosition(float x, float y) {
    m_position = Vec2(x, y);
    m_hasPosition = true;
    return *this;
}

LabelBuilder& LabelBuilder::setAnchorPoint(const Vec2& anchor) {
    m_anchorPoint = anchor;
    return *this;
}

LabelBuilder& LabelBuilder::setAnchorPoint(float x, float y) {
    m_anchorPoint = Vec2(x, y);
    return *this;
}

LabelBuilder& LabelBuilder::setZOrder(int zOrder) {
    m_zOrder = zOrder;
    return *this;
}

LabelBuilder& LabelBuilder::setOpacity(GLubyte opacity) {
    m_opacity = opacity;
    return *this;
}

LabelBuilder& LabelBuilder::setTag(int tag) {
    m_tag = tag;
    return *this;
}

LabelBuilder& LabelBuilder::setAlignment(TextHAlignment hAlignment, TextVAlignment vAlignment) {
    m_hAlignment = hAlignment;
    m_vAlignment = vAlignment;
    return *this;
}

LabelBuilder& LabelBuilder::setMaxWidth(float width) {
    m_maxWidth = width;
    m_hasMaxWidth = true;
    return *this;
}

LabelBuilder& LabelBuilder::addToParent(Node* parent) {
    m_parent = parent;
    return *this;
}

Label* LabelBuilder::build() {
    // 如果没有设置字体，使用默认字体
    if (!m_hasFont) {
        m_fontName = "fonts/Marker Felt.ttf";  // 使用原始代码的默认字体
        m_fontSize = 24.0f;
    }

    // 创建Label - 优先使用createWithTTF，如果失败则使用createWithSystemFont
    m_label = Label::createWithTTF(m_text, m_fontName, m_fontSize);

    if (m_label == nullptr) {
        // 尝试使用createWithSystemFont（某些场景下需要）
        m_label = Label::createWithSystemFont(m_text, m_fontName, m_fontSize);
    }

    if (m_label == nullptr) {
        CCLOG("Error: Failed to create label with text: %s", m_text.c_str());
        return nullptr;
    }

    // 应用设置
    m_label->setAnchorPoint(m_anchorPoint);

    if (m_hasPosition) {
        m_label->setPosition(m_position);
    }

    if (m_hasColor) {
        m_label->setTextColor(m_color);
    }

    m_label->setOpacity(m_opacity);
    m_label->setTag(m_tag);
    m_label->setAlignment(m_hAlignment, m_vAlignment);

    if (m_hasMaxWidth) {
        m_label->setMaxLineWidth(m_maxWidth);
    }

    // 添加到父节点
    if (m_parent) {
        m_parent->addChild(m_label, m_zOrder);
    }

    return m_label;
}
