// SpriteBuilder.cpp 
#include "SpriteBuilder.h"

SpriteBuilder::SpriteBuilder()
    : m_sprite(nullptr)
    , m_theme(UITheme::getInstance())
    , m_position(Vec2::ZERO)
    , m_anchorPoint(Vec2(0.5f, 0.5f))
    , m_scaleX(1.0f)
    , m_scaleY(1.0f)
    , m_zOrder(0)
    , m_opacity(255)
    , m_visible(true)
    , m_tag(0)
    , m_parent(nullptr)
    , m_hasPosition(false)
    , m_hasScale(false)
    , m_hasAnchor(false)
    , m_hasHoverEffect(false)
    , m_hoverScale(1.2f)
    , m_normalScale(1.0f) {
}

SpriteBuilder::~SpriteBuilder() {
}

SpriteBuilder& SpriteBuilder::setTexture(const std::string& filename) {
    m_sprite = Sprite::create(filename);
    if (m_sprite == nullptr) {
        CCLOG("Error: Failed to create sprite from %s", filename.c_str());
    }
    return *this;
}

SpriteBuilder& SpriteBuilder::setAutoScale(float divisor) {
    if (m_sprite) {
        Size originalSize = m_sprite->getContentSize();
        Size visibleSize = m_theme->getVisibleSize();

        float scaleX = visibleSize.width / originalSize.width;
        float scaleY = visibleSize.height / originalSize.height;
        float scale = std::min(scaleX, scaleY);

        m_scaleX = scale / divisor;
        m_scaleY = scale / divisor;
        m_normalScale = m_scaleX;
        m_hasScale = true;
    }
    return *this;
}

SpriteBuilder& SpriteBuilder::setScale(float scale) {
    m_scaleX = scale;
    m_scaleY = scale;
    m_normalScale = scale;
    m_hasScale = true;
    return *this;
}

SpriteBuilder& SpriteBuilder::setScale(float scaleX, float scaleY) {
    m_scaleX = scaleX;
    m_scaleY = scaleY;
    m_normalScale = scaleX;
    m_hasScale = true;
    return *this;
}

SpriteBuilder& SpriteBuilder::setRelativePosition(float xPercent, float yPercent) {
    m_position = m_theme->getRelativePosition(xPercent, yPercent);
    m_hasPosition = true;
    return *this;
}

SpriteBuilder& SpriteBuilder::setPosition(const Vec2& position) {
    m_position = position;
    m_hasPosition = true;
    return *this;
}

SpriteBuilder& SpriteBuilder::setPosition(float x, float y) {
    m_position = Vec2(x, y);
    m_hasPosition = true;
    return *this;
}

SpriteBuilder& SpriteBuilder::setAnchorPoint(const Vec2& anchor) {
    m_anchorPoint = anchor;
    m_hasAnchor = true;
    return *this;
}

SpriteBuilder& SpriteBuilder::setAnchorPoint(float x, float y) {
    m_anchorPoint = Vec2(x, y);
    m_hasAnchor = true;
    return *this;
}

SpriteBuilder& SpriteBuilder::setZOrder(int zOrder) {
    m_zOrder = zOrder;
    return *this;
}

SpriteBuilder& SpriteBuilder::setOpacity(GLubyte opacity) {
    m_opacity = opacity;
    return *this;
}

SpriteBuilder& SpriteBuilder::setVisible(bool visible) {
    m_visible = visible;
    return *this;
}

SpriteBuilder& SpriteBuilder::setTag(int tag) {
    m_tag = tag;
    return *this;
}

SpriteBuilder& SpriteBuilder::addToParent(Node* parent) {
    m_parent = parent;
    return *this;
}

SpriteBuilder& SpriteBuilder::setAdaptiveScale(float targetWidthPercent, float targetHeightPercent) {
    if (m_sprite) {
        Size originalSize = m_sprite->getContentSize();
        float scale = m_theme->calculateAdaptiveScale(
            originalSize.width,
            originalSize.height,
            targetWidthPercent,
            targetHeightPercent
        );
        m_scaleX = scale;
        m_scaleY = scale;
        m_normalScale = scale;
        m_hasScale = true;
    }
    return *this;
}

SpriteBuilder& SpriteBuilder::setClickCallback(const std::function<void(Sprite*)>& callback) {
    m_clickCallback = callback;
    return *this;
}

SpriteBuilder& SpriteBuilder::setHoverEffect(float hoverScale) {
    m_hasHoverEffect = true;
    m_hoverScale = hoverScale;
    return *this;
}

Sprite* SpriteBuilder::build() {
    if (m_sprite == nullptr) {
        CCLOG("Error: Sprite is null, cannot build");
        return nullptr;
    }

    // 应用设置
    if (m_hasAnchor) {
        m_sprite->setAnchorPoint(m_anchorPoint);
    }

    if (m_hasScale) {
        m_sprite->setScale(m_scaleX, m_scaleY);
    }

    if (m_hasPosition) {
        m_sprite->setPosition(m_position);
    }

    m_sprite->setOpacity(m_opacity);
    m_sprite->setVisible(m_visible);
    m_sprite->setTag(m_tag);

    // 添加点击事件和悬停效果 - 修复生命周期问题
    if (m_clickCallback || m_hasHoverEffect) {
        // 捕获必要的数据而不是this指针，避免生命周期问题
        Sprite* targetSprite = m_sprite;
        std::function<void(Sprite*)> clickCallback = m_clickCallback;
        bool hasHoverEffect = m_hasHoverEffect;
        float normalScale = m_normalScale;
        float hoverScale = m_hoverScale;

        auto listener = EventListenerMouse::create();

        // 点击事件
        if (clickCallback) {
            listener->onMouseDown = [targetSprite, clickCallback](EventMouse* event) {
                // 安全检查
                if (!targetSprite || !targetSprite->getParent()) {
                    return;
                }

                Vec2 mousePos = Vec2(event->getCursorX(), event->getCursorY());
                mousePos = targetSprite->getParent()->convertToNodeSpace(mousePos);

                if (targetSprite->getBoundingBox().containsPoint(mousePos)) {
                    if (clickCallback) {
                        clickCallback(targetSprite);
                    }
                }
            };
        }

        // 悬停效果
        if (hasHoverEffect) {
            listener->onMouseMove = [targetSprite, hasHoverEffect, normalScale, hoverScale](EventMouse* event) {
                // 安全检查
                if (!targetSprite || !targetSprite->getParent()) {
                    return;
                }

                Vec2 mousePos = Vec2(event->getCursorX(), event->getCursorY());
                mousePos = targetSprite->getParent()->convertToNodeSpace(mousePos);

                if (targetSprite->getBoundingBox().containsPoint(mousePos)) {
                    targetSprite->setScale(normalScale * hoverScale);
                } else {
                    targetSprite->setScale(normalScale);
                }
            };
        }

        // 只添加一个监听器，避免冲突
        if (targetSprite) {
            targetSprite->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, targetSprite);
        }
    }

    // 添加到父节点
    if (m_parent) {
        m_parent->addChild(m_sprite, m_zOrder);
    }

    return m_sprite;
}
