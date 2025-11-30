// CropFlyweight.cpp - 农作物享元类实现
#include "CropFlyweight.h"
#include "CropExtrinsicState.h"
#include "cocos2d.h"

USING_NS_CC;

CropFlyweight::CropFlyweight(const std::string& name,
                             const std::string& initial_pic,
                             const std::string& growing_pic,
                             const std::string& mature_pic,
                             const std::string& season,
                             int mature_needed)
    : m_name(name)
    , m_initialPic(initial_pic)
    , m_growingPic(growing_pic)
    , m_maturePic(mature_pic)
    , m_season(season)
    , m_matureNeeded(mature_needed)
{
    CCLOG("CropFlyweight: Created '%s' (Season: %s, Days: %d)",
          name.c_str(), season.c_str(), mature_needed);
}

void CropFlyweight::render(const IExtrinsicState& state, cocos2d::Node* parent) {
    // 将接口转换为具体的CropExtrinsicState
    const CropExtrinsicState* cropState = dynamic_cast<const CropExtrinsicState*>(&state);
    if (!cropState) {
        CCLOG("CropFlyweight::render - Invalid state type");
        return;
    }

    // 如果作物不可用，不渲染
    if (!cropState->isAvailable()) {
        return;
    }

    // 根据生长阶段选择纹理
    std::string texturePath;
    Phase phase = cropState->getPhase();

    switch (phase) {
        case Phase::SEED:
            texturePath = m_initialPic;
            break;
        case Phase::GROWING:
            texturePath = m_growingPic;
            break;
        case Phase::MATURE:
            texturePath = m_maturePic;
            break;
        case Phase::SAPLESS:
        case Phase::DEAD:
            // 枯萎或死亡状态不渲染
            return;
        default:
            texturePath = m_initialPic;
            break;
    }

    // 创建精灵
    auto sprite = Sprite::create(texturePath);
    if (sprite) {
        sprite->setPosition(cropState->getPosition());
        sprite->setScale(0.7f); // 根据原代码的缩放比例

        // 设置标签以便后续识别
        sprite->setTag(cropState->getNums());

        parent->addChild(sprite, 2);

        // 如果浇水了，可以添加视觉效果（可选）
        if (cropState->isWatered()) {
            // TODO: 添加浇水效果
        }
    } else {
        CCLOG("CropFlyweight::render - Failed to create sprite: %s", texturePath.c_str());
    }
}
