// CropExtrinsicState.cpp - 农作物外部状态实现
#include "CropExtrinsicState.h"
#include "CropFlyweight.h"
#include "cocos2d.h"

USING_NS_CC;

CropExtrinsicState::CropExtrinsicState(CropFlyweight* flyweight,
                                       int nums,
                                       Phase phase,
                                       int plant_day,
                                       bool watered)
    : m_flyweight(flyweight)
    , m_nums(nums)
    , m_phase(phase)
    , m_plantDay(plant_day)
    , m_watered(watered)
{
}

cocos2d::Vec2 CropExtrinsicState::getPosition() const {
    // 根据nums计算在农场中的实际位置
    // 农场是19x11的网格，nums范围是1-209

    // 获取可见区域大小
    auto visibleSize = Director::getInstance()->getVisibleSize();

    // 计算行列（nums从1开始，需要减1）
    int index = m_nums - 1;
    int row = index / 19;  // 每行19个
    int col = index % 19;

    // 计算实际位置（根据原farm.cpp的布局）
    // 这里使用一个基准位置加上偏移
    float baseX = visibleSize.width * 0.3f;  // 农场起始X位置
    float baseY = visibleSize.height * 0.6f; // 农场起始Y位置
    float cellWidth = 64.0f;   // 每个格子的宽度
    float cellHeight = 64.0f;  // 每个格子的高度

    float x = baseX + col * cellWidth;
    float y = baseY - row * cellHeight;

    return Vec2(x, y);
}

bool CropExtrinsicState::isAvailable() const {
    // 死亡状态的作物不可用
    return m_phase != Phase::DEAD;
}

void CropExtrinsicState::updateGrowth() {
    if (!m_flyweight) {
        return;
    }

    // 如果已经死亡，不更新
    if (m_phase == Phase::DEAD) {
        return;
    }

    // 如果没有浇水，进入枯萎状态
    if (!m_watered && m_phase != Phase::SEED) {
        m_phase = Phase::SAPLESS;
        return;
    }

    // 如果浇水了，增加生长天数
    if (m_watered) {
        m_plantDay++;
        m_watered = false; // 重置浇水状态
    }

    // 根据生长天数更新阶段
    int matureNeeded = m_flyweight->getMatureNeeded();

    if (m_phase == Phase::SEED && m_plantDay > 0) {
        m_phase = Phase::GROWING;
    }
    else if (m_phase == Phase::GROWING && m_plantDay >= matureNeeded) {
        m_phase = Phase::MATURE;
    }
    else if (m_phase == Phase::SAPLESS && m_watered) {
        // 枯萎状态浇水后可以恢复
        m_phase = Phase::GROWING;
    }
}
