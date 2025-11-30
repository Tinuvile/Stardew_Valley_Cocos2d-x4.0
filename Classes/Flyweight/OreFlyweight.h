// OreFlyweight.h - 矿石享元类（内部状态）
// 存储所有相同类型矿石共享的数据
#ifndef __ORE_FLYWEIGHT_H__
#define __ORE_FLYWEIGHT_H__

#include "IFlyweight.h"
#include "cocos2d.h"
#include <string>

/**
 * @class OreFlyweight
 * @brief 矿石享元类
 *
 * 存储可共享的内部状态：
 * - 纹理路径（初始、开采后）
 * - 矿石名称
 * - 价值
 * - 恢复时间
 *
 * 这些数据对于同一类型的所有矿石都是相同的，因此可以共享
 */
class OreFlyweight : public IFlyweight {
public:
    /**
     * @brief 构造函数
     * @param name 矿石名称
     * @param initial_pic 初始纹理路径
     * @param mining_pic 开采后纹理路径
     * @param value 价值
     * @param recover_time 恢复时间
     */
    OreFlyweight(const std::string& name,
                 const std::string& initial_pic,
                 const std::string& mining_pic,
                 int value,
                 int recover_time);

    virtual ~OreFlyweight() = default;

    // ==================== IFlyweight接口实现 ====================

    /**
     * @brief 渲染矿石
     * @param state 外部状态（位置、可用状态等）
     * @param parent 父节点
     */
    void render(const IExtrinsicState& state, cocos2d::Node* parent) override;

    /**
     * @brief 获取矿石名称
     */
    const std::string& getName() const override { return m_name; }

    // ==================== 内部状态访问器 ====================

    const std::string& getInitialPic() const { return m_initialPic; }
    const std::string& getMiningPic() const { return m_miningPic; }
    int getValue() const { return m_value; }
    int getRecoverTime() const { return m_recoverTime; }

private:
    // 内部状态（可共享）
    std::string m_name;          // 矿石名称
    std::string m_initialPic;    // 初始纹理
    std::string m_miningPic;     // 开采后纹理
    int m_value;                 // 价值
    int m_recoverTime;           // 恢复时间
};

#endif // __ORE_FLYWEIGHT_H__
