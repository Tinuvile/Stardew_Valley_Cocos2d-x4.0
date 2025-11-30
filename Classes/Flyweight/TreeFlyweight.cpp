// TreeFlyweight.cpp - 树木享元类实现
#include "TreeFlyweight.h"
#include "TreeExtrinsicState.h"
#include "cocos2d.h"

USING_NS_CC;

TreeFlyweight::TreeFlyweight(const std::string& name,
                             const std::string& initial_pic,
                             const std::string& g_cut_pic,
                             const std::string& y_ini_pic,
                             int value,
                             int recover_time,
                             int removetimes)
    : m_name(name)
    , m_initialPic(initial_pic)
    , m_gCutPic(g_cut_pic)
    , m_yIniPic(y_ini_pic)
    , m_value(value)
    , m_recoverTime(recover_time)
    , m_removetimes(removetimes)
{
    CCLOG("TreeFlyweight: Created '%s' (Value: %d, RecoverTime: %d)",
          name.c_str(), value, recover_time);
}

void TreeFlyweight::render(const IExtrinsicState& state, cocos2d::Node* parent) {
    // 将接口转换为具体的TreeExtrinsicState
    const TreeExtrinsicState* treeState = dynamic_cast<const TreeExtrinsicState*>(&state);
    if (!treeState) {
        CCLOG("TreeFlyweight::render - Invalid state type");
        return;
    }

    // 如果树木不可用，不渲染
    if (!treeState->isAvailable()) {
        return;
    }

    // 根据可用状态选择纹理
    std::string texturePath;
    if (treeState->isAvailable()) {
        texturePath = m_initialPic;
    } else {
        texturePath = m_gCutPic;
    }

    // 创建精灵
    auto sprite = Sprite::create(texturePath);
    if (sprite) {
        sprite->setPosition(treeState->getPosition());
        sprite->setScale(1.0f); // 根据需要调整缩放比例

        parent->addChild(sprite, 2);
    } else {
        CCLOG("TreeFlyweight::render - Failed to create sprite: %s", texturePath.c_str());
    }
}
