// TreeExtrinsicState.h - 树木外部状态类
// 存储每个树木实例独有的数据
#ifndef __TREE_EXTRINSIC_STATE_H__
#define __TREE_EXTRINSIC_STATE_H__

#include "IExtrinsicState.h"
#include "cocos2d.h"

// 前向声明
class TreeFlyweight;

/**
 * @class TreeExtrinsicState
 * @brief 树木外部状态类
 *
 * 存储不可共享的外部状态：
 * - 位置（position）
 * - 可用状态（available）
 * - 砍伐日期（mining_day）
 *
 * 每个树木实例都有自己独立的外部状态
 */
class TreeExtrinsicState : public IExtrinsicState {
public:
    /**
     * @brief 构造函数
     * @param flyweight 指向共享的享元对象
     * @param position 树木位置
     * @param available 是否可用
     * @param mining_day 砍伐日期
     */
    TreeExtrinsicState(TreeFlyweight* flyweight,
                       cocos2d::Vec2 position,
                       bool available = true,
                       int mining_day = 0);

    virtual ~TreeExtrinsicState() = default;

    // ==================== IExtrinsicState接口实现 ====================

    /**
     * @brief 获取树木位置
     */
    cocos2d::Vec2 getPosition() const override { return m_position; }

    /**
     * @brief 获取可用状态
     */
    bool isAvailable() const override { return m_available; }

    // ==================== 外部状态访问器 ====================

    int getMiningDay() const { return m_miningDay; }
    TreeFlyweight* getFlyweight() const { return m_flyweight; }

    // ==================== 状态修改器 ====================

    void setPosition(cocos2d::Vec2 position) { m_position = position; }
    void setAvailable(bool available) { m_available = available; }
    void setMiningDay(int day) { m_miningDay = day; }

    /**
     * @brief 砍伐树木
     */
    void mine() {
        m_available = false;
        m_miningDay = 0; // 记录砍伐时间
    }

    /**
     * @brief 更新恢复状态
     * 每天调用一次，检查树木是否恢复
     */
    void updateRecovery();

private:
    // 外部状态（不可共享）
    TreeFlyweight* m_flyweight;  // 指向共享的享元对象
    cocos2d::Vec2 m_position;    // 树木位置
    bool m_available;            // 是否可用
    int m_miningDay;             // 砍伐日期
};

#endif // __TREE_EXTRINSIC_STATE_H__
