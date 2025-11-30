// IExtrinsicState.h - 外部状态接口
// 定义所有外部状态对象的通用接口
#ifndef __I_EXTRINSIC_STATE_H__
#define __I_EXTRINSIC_STATE_H__

#include "cocos2d.h"

/**
 * @class IExtrinsicState
 * @brief 外部状态接口
 *
 * 外部状态存储不可共享的数据（如位置、当前状态等）
 * 每个对象实例都有自己独立的外部状态
 */
class IExtrinsicState {
public:
    virtual ~IExtrinsicState() = default;

    /**
     * @brief 获取对象的位置
     * @return 对象在场景中的位置
     */
    virtual cocos2d::Vec2 getPosition() const = 0;

    /**
     * @brief 获取对象的可用状态
     * @return true表示对象可用，false表示不可用
     */
    virtual bool isAvailable() const = 0;
};

#endif // __I_EXTRINSIC_STATE_H__
