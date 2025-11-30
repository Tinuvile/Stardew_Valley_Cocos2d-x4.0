// UIConfig.cpp - UI配置管理器实现
#include "UIConfig.h"

UIConfig* UIConfig::s_instance = nullptr;

UIConfig* UIConfig::getInstance() {
    if (s_instance == nullptr) {
        s_instance = new UIConfig();
    }
    return s_instance;
}

UIConfig::UIConfig() {
    initializeSceneBounds();
}

UIConfig::~UIConfig() {
}

void UIConfig::initializeSceneBounds() {
    // 初始化各个场景的边界信息
    m_sceneBounds["Town"] = SceneBounds(-170.0f, 1773.0f, 1498.0f, -222.0f);
    m_sceneBounds["Cave"] = SceneBounds(786.0f, 817.0f, 808.0f, 460.0f);
    m_sceneBounds["Beach"] = SceneBounds(-315.0f, 20000.0f, 920.0f, 360.0f);
    m_sceneBounds["Forest"] = SceneBounds(-600.0f, 2197.0f, 2200.0f, -850.0f);
    m_sceneBounds["farm"] = SceneBounds(637.0f, 960.0f, 777.0f, 500.0f);
    m_sceneBounds["Barn"] = SceneBounds(805.0f, 805.0f, 569.0f, 569.0f);
    m_sceneBounds["Myhouse"] = SceneBounds(800.0f, 800.0f, 580.0f, 580.0f);
}

UIConfig::SceneBounds UIConfig::getSceneBounds(const std::string& sceneName) const {
    auto it = m_sceneBounds.find(sceneName);
    if (it != m_sceneBounds.end()) {
        return it->second;
    }
    // 返回默认边界（无限制）
    return SceneBounds();
}

Vec2 UIConfig::adjustCoordinate(const std::string& sceneName, const Vec2& position) const {
    SceneBounds bounds = getSceneBounds(sceneName);

    float x = position.x;
    float y = position.y;

    // 应用边界限制
    if (x <= bounds.leftBoundary) {
        x = bounds.leftBoundary;
    }
    else if (x >= bounds.rightBoundary) {
        x = bounds.rightBoundary;
    }

    if (y >= bounds.upperBoundary) {
        y = bounds.upperBoundary;
    }
    else if (y <= bounds.lowerBoundary) {
        y = bounds.lowerBoundary;
    }

    return Vec2(x, y);
}

std::string UIConfig::getUIResourcePath(const std::string& resourceName) const {
    // 这里可以根据需要添加资源路径映射
    // 目前直接返回资源名称
    return resourceName;
}
