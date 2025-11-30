// OreExtrinsicState.cpp - 矿石外部状态实现
#include "OreExtrinsicState.h"
#include "OreFlyweight.h"
#include "cocos2d.h"

USING_NS_CC;

OreExtrinsicState::OreExtrinsicState(OreFlyweight* flyweight,
                                     cocos2d::Vec2 position,
                                     bool available,
                                     int mining_day)
    : m_flyweight(flyweight)
    , m_position(position)
    , m_available(available)
    , m_miningDay(mining_day)
{
}

void OreExtrinsicState::updateRecovery() {
    if (!m_flyweight) {
        return;
    }

    // 如果矿石已经被开采，检查是否恢复
    if (!m_available) {
        m_miningDay++;

        // 如果达到恢复时间，恢复矿石
        if (m_miningDay >= m_flyweight->getRecoverTime()) {
            m_available = true;
            m_miningDay = 0;
            CCLOG("OreExtrinsicState: Ore recovered at position (%.1f, %.1f)",
                  m_position.x, m_position.y);
        }
    }
}
