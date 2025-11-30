// UITheme.cpp - 简化版实现
#include "UITheme.h"

UITheme* UITheme::s_instance = nullptr;

UITheme* UITheme::getInstance() {
    if (s_instance == nullptr) {
        s_instance = new UITheme();
    }
    return s_instance;
}

UITheme::UITheme() {
    auto director = Director::getInstance();
    m_visibleSize = director->getVisibleSize();
    m_origin = director->getVisibleOrigin();
}

UITheme::~UITheme() {
}

Size UITheme::getVisibleSize() const {
    return m_visibleSize;
}

Vec2 UITheme::getOrigin() const {
    return m_origin;
}

Vec2 UITheme::getCenter() const {
    return Vec2(
        m_origin.x + m_visibleSize.width / 2,
        m_origin.y + m_visibleSize.height / 2
    );
}

Vec2 UITheme::getRelativePosition(float xPercent, float yPercent) const {
    return Vec2(
        m_origin.x + m_visibleSize.width * xPercent,
        m_origin.y + m_visibleSize.height * yPercent
    );
}

float UITheme::calculateAdaptiveScale(float originalWidth, float originalHeight,
                                      float targetWidthPercent, float targetHeightPercent) const {
    float targetWidth = m_visibleSize.width * targetWidthPercent;
    float targetHeight = m_visibleSize.height * targetHeightPercent;

    float scaleX = targetWidth / originalWidth;
    float scaleY = targetHeight / originalHeight;

    return std::min(scaleX, scaleY);
}
