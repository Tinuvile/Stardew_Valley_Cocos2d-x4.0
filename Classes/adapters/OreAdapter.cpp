#include "OreAdapter.h"
#include "cocos2d.h"

USING_NS_CC;

// 外部全局变量
extern int day;

OreAdapter::OreAdapter(std::shared_ptr<Ore> orePtr, const std::string& objectId)
    : ore(orePtr), id(objectId), sprite(nullptr), isActiveFlag(true), isBeingMined(false) {
    
    if (!ore) {
        CCLOG("OreAdapter::OreAdapter - Warning: null ore pointer provided");
        isActiveFlag = false;
        return;
    }
    
    initializeSprite();
}

OreAdapter::~OreAdapter() {
    cleanup();
}

// === 基础属性实现 ===

std::string OreAdapter::getName() const {
    return ore ? ore->GetName() : "Unknown Ore";
}

// === 位置管理实现 ===

cocos2d::Vec2 OreAdapter::getPosition() const {
    return ore ? ore->position : Vec2::ZERO;
}

void OreAdapter::setPosition(const cocos2d::Vec2& pos) {
    if (ore) {
        ore->position = pos;
        if (sprite) {
            sprite->setPosition(pos);
        }
    }
}

cocos2d::Rect OreAdapter::getBounds() const {
    if (sprite) {
        return sprite->getBoundingBox();
    }
    
    // 返回默认大小的边界框
    Vec2 pos = getPosition();
    return Rect(pos.x - 24, pos.y - 24, 48, 48);
}

// === 渲染相关实现 ===

void OreAdapter::updateTexture(float deltaTime) {
    if (!ore || !sprite) return;
    
    updateOreAppearance();
}

bool OreAdapter::isVisible() const {
    return sprite ? sprite->isVisible() : false;
}

void OreAdapter::setVisible(bool visible) {
    if (sprite) {
        sprite->setVisible(visible);
    }
}

// === 生命周期管理实现 ===

void OreAdapter::update(float deltaTime) {
    if (!ore || !isActiveFlag) return;
    
    checkRecovery();
    updateTexture(deltaTime);
}

void OreAdapter::cleanup() {
    if (sprite) {
        sprite->removeFromParent();
        sprite = nullptr;
    }
    ore.reset();
    isActiveFlag = false;
}

// === 交互能力实现 ===

bool OreAdapter::canInteract() const {
    return ore && ore->available && !isBeingMined;
}

void OreAdapter::onInteract(GameObjectInterface* interactor) {
    if (!ore || !interactor || !canInteract()) return;
    
    CCLOG("OreAdapter::onInteract - %s is mining ore %s", 
          interactor->getName().c_str(), getName().c_str());
    
    // 执行挖掘
    if (mineOre()) {
        CCLOG("Ore mined successfully!");
    } else {
        CCLOG("Failed to mine ore");
    }
}

std::string OreAdapter::getInteractionHint() const {
    if (!ore) return "";
    
    if (!ore->available) {
        int daysLeft = getRecoverTime() - (day - ore->mining_day);
        return getName() + " (Recovering: " + std::to_string(daysLeft) + " days)";
    } else if (isBeingMined) {
        return getName() + " (Being mined...)";
    } else {
        return "Mine " + getName();
    }
}

// === 收获能力实现 ===

bool OreAdapter::isHarvestable() const {
    return ore && ore->available;
}

std::shared_ptr<class Item> OreAdapter::harvest() {
    if (!ore || !isHarvestable()) {
        return nullptr;
    }
    
    CCLOG("OreAdapter::harvest - Mining ore %s", getName().c_str());
    
    // 获取产品
    auto product = ore->GetCopy();
    
    // 更新矿石状态
    ore->mining_day = day;
    ore->available = false; // 矿石被挖空，需要恢复
    
    updateOreAppearance();
    
    return product;
}

// === 状态查询实现 ===

std::string OreAdapter::getStatusText() const {
    if (!ore) return "Ore (Invalid)";
    
    std::string status = getName();
    
    if (!ore->available) {
        status += " (Recovering)";
        float progress = getRecoveryProgress();
        status += " [" + std::to_string((int)(progress * 100)) + "%]";
    } else {
        status += " (Available)";
    }
    
    return status;
}

float OreAdapter::getHealth() const {
    if (!ore) return 0.0f;
    
    if (!ore->available) {
        return getRecoveryProgress();
    }
    
    return 1.0f; // 矿石要么可用要么不可用
}

// === 事件回调实现 ===

void OreAdapter::onCollisionEnter(GameObjectInterface* other) {
    if (!ore || !other) return;
    
    CCLOG("OreAdapter::onCollisionEnter - %s collided with ore %s", 
          other->getName().c_str(), getName().c_str());
}

void OreAdapter::onCollisionExit(GameObjectInterface* other) {
    // 矿石通常不需要处理碰撞退出事件
}

void OreAdapter::onDayPass() {
    if (!ore) return;
    
    CCLOG("OreAdapter::onDayPass - New day for ore %s", getName().c_str());
    
    checkRecovery();
}

void OreAdapter::onSeasonChange(const std::string& newSeason) {
    if (!ore) return;
    
    CCLOG("OreAdapter::onSeasonChange - Ore %s season change to: %s", 
          getName().c_str(), newSeason.c_str());
    
    // 矿石通常不受季节影响
}

// === Ore特有方法实现 ===

int OreAdapter::getRecoverTime() const {
    return ore ? ore->recover_time : 0;
}

int OreAdapter::getMiningDay() const {
    return ore ? ore->mining_day : 0;
}

bool OreAdapter::isAvailable() const {
    return ore ? ore->available : false;
}

void OreAdapter::setAvailable(bool available) {
    if (ore) {
        ore->available = available;
        updateOreAppearance();
    }
}

bool OreAdapter::mineOre() {
    if (!ore || !ore->available || isBeingMined) {
        return false;
    }
    
    isBeingMined = true;
    
    // 执行挖掘逻辑
    auto product = harvest();
    
    isBeingMined = false;
    
    return product != nullptr;
}

std::string OreAdapter::getCurrentTexturePath() const {
    if (!ore) return "";
    
    if (ore->available) {
        return ore->initial_pic;
    } else {
        return ore->mining_pic; // 被挖掘后的样子
    }
}

bool OreAdapter::isRecovering() const {
    return ore && !ore->available;
}

float OreAdapter::getRecoveryProgress() const {
    return calculateRecoveryProgress();
}

void OreAdapter::forceRecover() {
    if (ore) {
        ore->available = true;
        ore->mining_day = 0;
        updateOreAppearance();
        
        CCLOG("OreAdapter::forceRecover - Ore %s recovered", getName().c_str());
    }
}

std::shared_ptr<class Item> OreAdapter::getProduct() const {
    return ore ? ore->GetCopy() : nullptr;
}

int OreAdapter::getOreValue() const {
    return ore ? ore->GetValue() : 0;
}

void OreAdapter::setOreValue(int value) {
    if (ore) {
        ore->SetValue(value);
    }
}

// === 私有方法实现 ===

void OreAdapter::initializeSprite() {
    if (!ore) return;
    
    // 创建精灵并设置初始纹理
    sprite = Sprite::create(ore->initial_pic);
    if (sprite) {
        sprite->setPosition(ore->position);
        updateOreAppearance();
    } else {
        CCLOG("OreAdapter::initializeSprite - Failed to create sprite for %s", getName().c_str());
    }
}

void OreAdapter::updateOreAppearance() {
    if (!ore || !sprite) return;
    
    std::string texturePath = getCurrentTexturePath();
    if (!texturePath.empty()) {
        auto texture = Director::getInstance()->getTextureCache()->addImage(texturePath);
        if (texture) {
            sprite->setTexture(texture);
        }
    }
    
    // 根据矿石状态调整外观
    if (!ore->available) {
        // 被挖掘的矿石显示为较暗的颜色
        sprite->setColor(Color3B(120, 120, 120));
    } else {
        // 正常矿石
        sprite->setColor(Color3B::WHITE);
    }
}

void OreAdapter::checkRecovery() {
    if (!ore || ore->available) return;
    
    // 检查是否到了恢复时间
    int daysSinceMined = day - ore->mining_day;
    if (daysSinceMined >= ore->recover_time) {
        ore->available = true;
        updateOreAppearance();
        
        CCLOG("OreAdapter::checkRecovery - Ore %s has recovered", getName().c_str());
    }
}

float OreAdapter::calculateRecoveryProgress() const {
    if (!ore || ore->available) {
        return 1.0f;
    }
    
    int daysSinceMined = day - ore->mining_day;
    if (ore->recover_time <= 0) {
        return 1.0f;
    }
    
    return std::min(1.0f, (float)daysSinceMined / (float)ore->recover_time);
}
