// OreExtrinsicState.h - 矿石外部状态类
// 存储每个矿石实例独有的数据
#ifndef __ORE_EXTRINSIC_STATE_H__
#define __ORE_EXTRINSIC_STATE_H__

#include "IExtrinsicState.h"
#include "cocos2d.h"

// 前向声明
class OreFlyweight;

/**
 * @class OreExtrinsicState
 * @brief 矿石外部状态类
 *
 * 存储不可共享的外部状态：
 * - 位置（position）
 * - 可用状态（available）
 * - 开采日期（mining_day）
 *
 * 每个矿石实例都有自己独立的外部状态
 */
class OreExtrinsicState : public IExtrinsicState {
public:
    /**
     * @brief 构造函数
     * @param flyweight 指向共享的享元对象
     * @param position 矿石位置
     * @param available 是否可用
     * @param mining_day 开采日期
     */
    OreExtrinsicState(OreFlyweight* flyweight,
                      cocos2d::Vec2 position,
                      bool available = true,
                      int mining_day = 0);

    virtual ~OreExtrinsicState() = default;

    // ==================== IExtrinsicState接口实现 ====================

    /**
     * @brief 获取矿石位置
     */
    cocos2d::Vec2 getPosition() const override { return m_position; }

    /**
     * @brief 获取可用状态
     */
    bool isAvailable() const override { return m_available; }

    // ==================== 外部状态访问器 ====================

    int getMiningDay() const { return m_miningDay; }
    OreFlyweight* getFlyweight() const { return m_flyweight; }

    // ==================== 状态修改器 ====================

    void setPosition(cocos2d::Vec2 position) { m_position = position; }
    void setAvailable(bool available) { m_available = available; }
    void setMiningDay(int day) { m_miningDay = day; }

    /**
     * @brief 开采矿石
     */
    void mine() {
        m_available = false;
        m_miningDay = 0; // 记录开采时间
    }

    /**
     * @brief 更新恢复状态
     * 每天调用一次，检查矿石是否恢复
     */
    void updateRecovery();

private:
    // 外部状态（不可共享）
    OreFlyweight* m_flyweight;  // 指向共享的享元对象
    cocos2d::Vec2 m_position;   // 矿石位置
    bool m_available;           // 是否可用
    int m_miningDay;            // 开采日期
};

#endif // __ORE_EXTRINSIC_STATE_H__
