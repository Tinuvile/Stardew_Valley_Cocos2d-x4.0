// IFlyweight.h - 享元接口
// 定义所有享元对象的通用接口
#ifndef __I_FLYWEIGHT_H__
#define __I_FLYWEIGHT_H__

#include "cocos2d.h"
#include <string>

// 前向声明
class IExtrinsicState;

/**
 * @class IFlyweight
 * @brief 享元模式的核心接口
 *
 * 享元对象存储可共享的内部状态（如纹理路径、配置数据）
 * 通过render方法接收外部状态来完成渲染
 */
class IFlyweight {
public:
    virtual ~IFlyweight() = default;

    /**
     * @brief 渲染享元对象
     * @param state 外部状态（位置、状态等不可共享的数据）
     * @param parent 父节点，用于添加渲染的Sprite
     */
    virtual void render(const IExtrinsicState& state, cocos2d::Node* parent) = 0;

    /**
     * @brief 获取享元对象的名称
     * @return 对象名称
     */
    virtual const std::string& getName() const = 0;
};

#endif // __I_FLYWEIGHT_H__
