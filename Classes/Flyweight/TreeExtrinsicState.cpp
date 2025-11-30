// TreeExtrinsicState.cpp - 树木外部状态实现
#include "TreeExtrinsicState.h"
#include "TreeFlyweight.h"
#include "cocos2d.h"

USING_NS_CC;

TreeExtrinsicState::TreeExtrinsicState(TreeFlyweight* flyweight,
                                       cocos2d::Vec2 position,
                                       bool available,
                                       int mining_day)
    : m_flyweight(flyweight)
    , m_position(position)
    , m_available(available)
    , m_miningDay(mining_day)
{
}

void TreeExtrinsicState::updateRecovery() {
    if (!m_flyweight) {
        return;
    }

    // 如果树木已经被砍伐，检查是否恢复
    if (!m_available) {
        m_miningDay++;

        // 如果达到恢复时间，恢复树木
        if (m_miningDay >= m_flyweight->getRecoverTime()) {
            m_available = true;
            m_miningDay = 0;
            CCLOG("TreeExtrinsicState: Tree recovered at position (%.1f, %.1f)",
                  m_position.x, m_position.y);
        }
    }
}
