// TreeFlyweight.h - 树木享元类（内部状态）
// 存储所有相同类型树木共享的数据
#ifndef __TREE_FLYWEIGHT_H__
#define __TREE_FLYWEIGHT_H__

#include "IFlyweight.h"
#include "cocos2d.h"
#include <string>

/**
 * @class TreeFlyweight
 * @brief 树木享元类
 *
 * 存储可共享的内部状态：
 * - 纹理路径（初始、砍伐后、黄色初始）
 * - 树木名称
 * - 价值
 * - 恢复时间
 * - 砍伐次数
 *
 * 这些数据对于同一类型的所有树木都是相同的，因此可以共享
 */
class TreeFlyweight : public IFlyweight {
public:
    /**
     * @brief 构造函数
     * @param name 树木名称
     * @param initial_pic 初始纹理路径
     * @param g_cut_pic 砍伐后纹理路径
     * @param y_ini_pic 黄色初始纹理路径
     * @param value 价值
     * @param recover_time 恢复时间
     * @param removetimes 砍伐次数
     */
    TreeFlyweight(const std::string& name,
                  const std::string& initial_pic,
                  const std::string& g_cut_pic,
                  const std::string& y_ini_pic,
                  int value,
                  int recover_time,
                  int removetimes);

    virtual ~TreeFlyweight() = default;

    // ==================== IFlyweight接口实现 ====================

    /**
     * @brief 渲染树木
     * @param state 外部状态（位置、可用状态等）
     * @param parent 父节点
     */
    void render(const IExtrinsicState& state, cocos2d::Node* parent) override;

    /**
     * @brief 获取树木名称
     */
    const std::string& getName() const override { return m_name; }

    // ==================== 内部状态访问器 ====================

    const std::string& getInitialPic() const { return m_initialPic; }
    const std::string& getGCutPic() const { return m_gCutPic; }
    const std::string& getYIniPic() const { return m_yIniPic; }
    int getValue() const { return m_value; }
    int getRecoverTime() const { return m_recoverTime; }
    int getRemoveTimes() const { return m_removetimes; }

private:
    // 内部状态（可共享）
    std::string m_name;          // 树木名称
    std::string m_initialPic;    // 初始纹理
    std::string m_gCutPic;       // 砍伐后纹理
    std::string m_yIniPic;       // 黄色初始纹理
    int m_value;                 // 价值
    int m_recoverTime;           // 恢复时间
    int m_removetimes;           // 砍伐次数
};

#endif // __TREE_FLYWEIGHT_H__
