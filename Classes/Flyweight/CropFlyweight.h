// CropFlyweight.h - 农作物享元类（内部状态）
// 存储所有相同类型农作物共享的数据
#ifndef __CROP_FLYWEIGHT_H__
#define __CROP_FLYWEIGHT_H__

#include "IFlyweight.h"
#include "cocos2d.h"
#include <string>

/**
 * @class CropFlyweight
 * @brief 农作物享元类
 *
 * 存储可共享的内部状态：
 * - 纹理路径（种子、生长中、成熟）
 * - 作物名称
 * - 生长季节
 * - 成熟所需天数
 *
 * 这些数据对于同一类型的所有农作物都是相同的，因此可以共享
 */
class CropFlyweight : public IFlyweight {
public:
    /**
     * @brief 构造函数
     * @param name 作物名称
     * @param initial_pic 种子纹理路径
     * @param growing_pic 生长中纹理路径
     * @param mature_pic 成熟纹理路径
     * @param season 生长季节
     * @param mature_needed 成熟所需天数
     */
    CropFlyweight(const std::string& name,
                  const std::string& initial_pic,
                  const std::string& growing_pic,
                  const std::string& mature_pic,
                  const std::string& season,
                  int mature_needed);

    virtual ~CropFlyweight() = default;

    // ==================== IFlyweight接口实现 ====================

    /**
     * @brief 渲染农作物
     * @param state 外部状态（位置、生长阶段等）
     * @param parent 父节点
     */
    void render(const IExtrinsicState& state, cocos2d::Node* parent) override;

    /**
     * @brief 获取作物名称
     */
    const std::string& getName() const override { return m_name; }

    // ==================== 内部状态访问器 ====================

    const std::string& getInitialPic() const { return m_initialPic; }
    const std::string& getGrowingPic() const { return m_growingPic; }
    const std::string& getMaturePic() const { return m_maturePic; }
    const std::string& getSeason() const { return m_season; }
    int getMatureNeeded() const { return m_matureNeeded; }

private:
    // 内部状态（可共享）
    std::string m_name;          // 作物名称
    std::string m_initialPic;    // 种子纹理
    std::string m_growingPic;    // 生长中纹理
    std::string m_maturePic;     // 成熟纹理
    std::string m_season;        // 生长季节
    int m_matureNeeded;          // 成熟所需天数
};

#endif // __CROP_FLYWEIGHT_H__
