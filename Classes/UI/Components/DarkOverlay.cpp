// DarkOverlay.cpp - 半透明遮罩层组件实现
#include "DarkOverlay.h"
#include "../../AppDelegate.h"

DarkOverlay::DarkOverlay()
    : m_sceneName("")
    , m_theme(UITheme::getInstance())
    , m_config(UIConfig::getInstance()) {
}

DarkOverlay::~DarkOverlay() {
}

DarkOverlay* DarkOverlay::create(const std::string& sceneName, GLubyte opacity) {
    DarkOverlay* ret = new DarkOverlay();
    if (ret && ret->init(sceneName, opacity)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool DarkOverlay::init(const std::string& sceneName, GLubyte opacity) {
    m_sceneName = sceneName;

    // 获取屏幕尺寸
    Size visibleSize = m_theme->getVisibleSize();

    // 创建半透明黑色遮罩（足够大以覆盖整个场景）
    // 直接使用颜色，不用枚举
    Color4B overlayColor(0, 0, 0, opacity);

    if (!LayerColor::initWithColor(
        overlayColor,
        10 * visibleSize.width,
        5 * visibleSize.height)) {
        return false;
    }

    // 获取玩家位置并调整坐标
    Vec2 playerPos = player1->getPosition();
    Vec2 adjustedPos = m_config->adjustCoordinate(m_sceneName, playerPos);

    // 设置遮罩位置（居中在调整后的位置）
    this->setPosition(adjustedPos - visibleSize);

    return true;
}

void DarkOverlay::updatePosition(const Vec2& playerPosition) {
    Size visibleSize = m_theme->getVisibleSize();
    Vec2 adjustedPos = m_config->adjustCoordinate(m_sceneName, playerPosition);
    this->setPosition(adjustedPos - visibleSize);
}
