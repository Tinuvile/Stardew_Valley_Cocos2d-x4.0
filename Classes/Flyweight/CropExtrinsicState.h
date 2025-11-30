// CropExtrinsicState.h - 农作物外部状态类
// 存储每个农作物实例独有的数据
#ifndef __CROP_EXTRINSIC_STATE_H__
#define __CROP_EXTRINSIC_STATE_H__

#include "IExtrinsicState.h"
#include "cocos2d.h"

// 前向声明
class CropFlyweight;

// 生长阶段枚举（与原Crop.h保持一致）
enum Phase {
    SEED,    // 种子
    GROWING, // 生长中
    MATURE,  // 成熟
    SAPLESS, // 枯萎状态
    DEAD     // 死亡
};

/**
 * @class CropExtrinsicState
 * @brief 农作物外部状态类
 *
 * 存储不可共享的外部状态：
 * - 种植位置（nums）
 * - 生长阶段（phase）
 * - 种植天数（plant_day）
 * - 浇水状态（watered）
 *
 * 每个农作物实例都有自己独立的外部状态
 */
class CropExtrinsicState : public IExtrinsicState {
public:
    /**
     * @brief 构造函数
     * @param flyweight 指向共享的享元对象
     * @param nums 种植位置（1-209）
     * @param phase 生长阶段
     * @param plant_day 种植天数
     * @param watered 是否浇水
     */
    CropExtrinsicState(CropFlyweight* flyweight,
                       int nums,
                       Phase phase = Phase::SEED,
                       int plant_day = 0,
                       bool watered = false);

    virtual ~CropExtrinsicState() = default;

    // ==================== IExtrinsicState接口实现 ====================

    /**
     * @brief 获取作物位置
     * 根据nums计算在农场中的实际位置
     */
    cocos2d::Vec2 getPosition() const override;

    /**
     * @brief 获取可用状态
     * 死亡状态的作物不可用
     */
    bool isAvailable() const override;

    // ==================== 外部状态访问器 ====================

    int getNums() const { return m_nums; }
    Phase getPhase() const { return m_phase; }
    int getPlantDay() const { return m_plantDay; }
    bool isWatered() const { return m_watered; }
    CropFlyweight* getFlyweight() const { return m_flyweight; }

    // ==================== 状态修改器 ====================

    void setPhase(Phase phase) { m_phase = phase; }
    void setWatered(bool watered) { m_watered = watered; }
    void incrementPlantDay() { m_plantDay++; }
    void setPlantDay(int day) { m_plantDay = day; }

    /**
     * @brief 浇水
     */
    void water() { m_watered = true; }

    /**
     * @brief 更新生长状态
     * 每天调用一次，更新作物的生长阶段
     */
    void updateGrowth();

    /**
     * @brief 设置为死亡状态
     */
    void setDead() {
        m_phase = Phase::DEAD;
        m_plantDay = -1;
    }

    /**
     * @brief 判断是否为种子状态
     */
    bool isSeed() const { return m_phase == Phase::SEED; }

    /**
     * @brief 判断是否成熟
     */
    bool isMature() const { return m_phase == Phase::MATURE; }

    /**
     * @brief 判断是否可收获
     */
    bool isHarvestable() const { return m_phase == Phase::MATURE; }

private:
    // 外部状态（不可共享）
    CropFlyweight* m_flyweight;  // 指向共享的享元对象
    int m_nums;                  // 种植位置（1-209）
    Phase m_phase;               // 生长阶段
    int m_plantDay;              // 种植天数
    bool m_watered;              // 浇水状态
};

#endif // __CROP_EXTRINSIC_STATE_H__
