// OreFlyweight.cpp - 矿石享元类实现
#include "OreFlyweight.h"
#include "OreExtrinsicState.h"
#include "cocos2d.h"

USING_NS_CC;

OreFlyweight::OreFlyweight(const std::string& name,
                           const std::string& initial_pic,
                           const std::string& mining_pic,
                           int value,
                           int recover_time)
    : m_name(name)
    , m_initialPic(initial_pic)
    , m_miningPic(mining_pic)
    , m_value(value)
    , m_recoverTime(recover_time)
{
    CCLOG("OreFlyweight: Created '%s' (Value: %d, RecoverTime: %d)",
          name.c_str(), value, recover_time);
}

void OreFlyweight::render(const IExtrinsicState& state, cocos2d::Node* parent) {
    // 将接口转换为具体的OreExtrinsicState
    const OreExtrinsicState* oreState = dynamic_cast<const OreExtrinsicState*>(&state);
    if (!oreState) {
        CCLOG("OreFlyweight::render - Invalid state type");
        return;
    }

    // 如果矿石不可用，不渲染
    if (!oreState->isAvailable()) {
        return;
    }

    // 根据可用状态选择纹理
    std::string texturePath;
    if (oreState->isAvailable()) {
        texturePath = m_initialPic;
    } else {
        texturePath = m_miningPic;
    }

    // 创建精灵
    auto sprite = Sprite::create(texturePath);
    if (sprite) {
        sprite->setPosition(oreState->getPosition());
        sprite->setScale(1.0f); // 根据需要调整缩放比例

        parent->addChild(sprite, 2);
    } else {
        CCLOG("OreFlyweight::render - Failed to create sprite: %s", texturePath.c_str());
    }
}
