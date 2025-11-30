// ButtonBuilder.cpp - 简化版按钮建造者实现
#include "ButtonBuilder.h"

ButtonBuilder::ButtonBuilder()
    : m_button(nullptr)
    , m_theme(UITheme::getInstance())
    , m_normalTexture("")
    , m_pressedTexture("")
    , m_disabledTexture("")
    , m_position(0, 0)
    , m_anchorPoint(0.5f, 0.5f)
    , m_scaleX(1.0f)
    , m_scaleY(1.0f)
    , m_zOrder(0)
    , m_tag(0)
    , m_visible(true)
    , m_enabled(true)
    , m_parent(nullptr)
    , m_hasNormalTexture(false)
    , m_hasPosition(false)
    , m_hasScale(false)
    , m_hasAnchor(false)
    , m_hasHoverEffect(false)
    , m_hoverScale(1.2f)
    , m_normalScale(1.0f) {
}

ButtonBuilder::~ButtonBuilder() {
    m_button = nullptr;
    m_theme = nullptr;
}

ButtonBuilder& ButtonBuilder::setNormalTexture(const std::string& filename) {
    m_normalTexture = filename;
    m_hasNormalTexture = true;
    return *this;
}

ButtonBuilder& ButtonBuilder::setPressedTexture(const std::string& filename) {
    m_pressedTexture = filename;
    return *this;
}

ButtonBuilder& ButtonBuilder::setDisabledTexture(const std::string& filename) {
    m_disabledTexture = filename;
    return *this;
}

ButtonBuilder& ButtonBuilder::setScale(float scale) {
    m_scaleX = scale;
    m_scaleY = scale;
    m_hasScale = true;
    m_normalScale = scale;
    return *this;
}

ButtonBuilder& ButtonBuilder::setScale(float scaleX, float scaleY) {
    m_scaleX = scaleX;
    m_scaleY = scaleY;
    m_hasScale = true;
    m_normalScale = scaleX; // 默认使用X轴作为正常缩放
    return *this;
}

ButtonBuilder& ButtonBuilder::setAutoScale(float divisor) {
    // 获取可见尺寸来计算合适的缩放
    Size visibleSize = m_theme->getVisibleSize();

    // 尝试根据按钮纹理尺寸计算合适的缩放
    // 这里使用默认的按钮尺寸估算
    float targetWidth = visibleSize.width / divisor;
    float targetHeight = visibleSize.height / divisor;

    // 如果没有纹理，使用默认缩放
    if (m_normalTexture.empty()) {
        m_scaleX = targetWidth / 100.0f;  // 假设按钮默认宽度100
        m_scaleY = targetHeight / 100.0f;  // 假设按钮默认高度100
    } else {
        // 如果有纹理，可以基于纹理尺寸计算（但需要先加载纹理）
        // 这里简化处理，使用平均缩放
        float averageScale = (targetWidth / 100.0f + targetHeight / 100.0f) / 2.0f;
        m_scaleX = averageScale;
        m_scaleY = averageScale;
    }

    m_hasScale = true;
    m_normalScale = m_scaleX;
    return *this;
}

ButtonBuilder& ButtonBuilder::setPosition(const Vec2& position) {
    m_position = position;
    m_hasPosition = true;
    return *this;
}

ButtonBuilder& ButtonBuilder::setPosition(float x, float y) {
    m_position = Vec2(x, y);
    m_hasPosition = true;
    return *this;
}

ButtonBuilder& ButtonBuilder::setRelativePosition(float xPercent, float yPercent) {
    Size visibleSize = m_theme->getVisibleSize();
    m_position = Vec2(visibleSize.width * xPercent, visibleSize.height * yPercent);
    m_hasPosition = true;
    return *this;
}

ButtonBuilder& ButtonBuilder::setAnchorPoint(const Vec2& anchor) {
    m_anchorPoint = anchor;
    m_hasAnchor = true;
    return *this;
}

ButtonBuilder& ButtonBuilder::setAnchorPoint(float x, float y) {
    m_anchorPoint = Vec2(x, y);
    m_hasAnchor = true;
    return *this;
}

ButtonBuilder& ButtonBuilder::setZOrder(int zOrder) {
    m_zOrder = zOrder;
    return *this;
}

ButtonBuilder& ButtonBuilder::setTag(int tag) {
    m_tag = tag;
    return *this;
}

ButtonBuilder& ButtonBuilder::setVisible(bool visible) {
    m_visible = visible;
    return *this;
}

ButtonBuilder& ButtonBuilder::setEnabled(bool enabled) {
    m_enabled = enabled;
    return *this;
}

ButtonBuilder& ButtonBuilder::addToParent(Node* parent) {
    // 如果设置了父节点，则添加按钮并设置Z顺序
    if (parent) {
        parent->addChild(m_button, m_zOrder);
    }
    m_parent = parent;
    return *this;
}

ButtonBuilder& ButtonBuilder::setClickCallback(const std::function<void(Ref*)>& callback) {
    m_clickCallback = callback;
    return *this;
}

ButtonBuilder& ButtonBuilder::setHoverEffect(float hoverScale) {
    m_hasHoverEffect = true;
    m_hoverScale = hoverScale;
    return *this;
}

ButtonBuilder& ButtonBuilder::setAdaptiveScale(float targetWidthPercent, float targetHeightPercent) {
    Size visibleSize = m_theme->getVisibleSize();
    float targetWidth = visibleSize.width * targetWidthPercent;
    float targetHeight = visibleSize.height * targetHeightPercent;

    // 如果没有纹理，使用默认缩放
    if (m_normalTexture.empty()) {
        m_scaleX = targetWidth / 100.0f;  // 假设按钮默认宽度100
        m_scaleY = targetHeight / 100.0f;  // 假设按钮默认高度100
    } else {
        // 如果有纹理，可以基于纹理尺寸计算
        float averageScale = (targetWidth / 100.0f + targetHeight / 100.0f) / 2.0f;
        m_scaleX = averageScale;
        m_scaleY = averageScale;
    }

    m_hasScale = true;
    m_normalScale = m_scaleX;
    return *this;
}

ui::Button* ButtonBuilder::build() {
    if (!m_hasNormalTexture) {
        return nullptr;
    }

    // 创建按钮
    if (m_pressedTexture.empty()) {
        // 如果没有指定按下纹理，使用正常纹理作为按下纹理
        m_button = ui::Button::create(m_normalTexture, m_normalTexture);
    } else {
        m_button = ui::Button::create(m_normalTexture, m_pressedTexture);
    }

    if (!m_button) {
        return nullptr;
    }

    // 应用缩放
    if (m_hasScale) {
        m_button->setScale(m_scaleX, m_scaleY);
    }

    // 应用位置
    if (m_hasPosition) {
        m_button->setPosition(m_position);
    }

    // 应用锚点
    if (m_hasAnchor) {
        m_button->setAnchorPoint(m_anchorPoint);
    }

    // 应用其他属性
    m_button->setTag(m_tag);
    m_button->setVisible(m_visible);
    m_button->setEnabled(m_enabled);

    // Z顺序通过add时的层级参数设置，因为Button没有setZOrder方法

    // 设置点击回调
    if (m_clickCallback) {
        m_button->addClickEventListener(m_clickCallback);
    }

    // 添加到父节点（已经在addToParent中处理了）
    // 注意：如果需要重新设置Z顺序，可以在build()中调用
    if (m_parent && !m_button->getParent()) {
        m_parent->addChild(m_button, m_zOrder);
    }

    // 设置悬停效果
    if (m_hasHoverEffect) {
        // 创建悬停事件监听器
        auto hoverListener = EventListenerMouse::create();
        hoverListener->onMouseMove = [this](EventMouse* event) {
            Vec2 mousePos = Vec2(event->getCursorX(), event->getCursorY());

            if (m_button->getParent()) {
                mousePos = m_button->getParent()->convertToNodeSpace(mousePos);
            }

            if (m_button->getBoundingBox().containsPoint(mousePos)) {
                m_button->setScale(m_normalScale * m_hoverScale);
            } else {
                m_button->setScale(m_normalScale);
            }
        };

        m_button->getEventDispatcher()->addEventListenerWithSceneGraphPriority(hoverListener, m_button);
    }

    return m_button;
}