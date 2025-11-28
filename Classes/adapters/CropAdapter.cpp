#include "CropAdapter.h"
#include "cocos2d.h"

USING_NS_CC;

// 外部全局变量声明（来自AppDelegate.h）
extern int day;
extern std::string Season;

CropAdapter::CropAdapter(std::shared_ptr<Crop> cropPtr, const std::string& objectId, 
                        const cocos2d::Vec2& pos)
    : crop(cropPtr), id(objectId), position(pos), sprite(nullptr), 
      isActiveFlag(true), lastUpdateTime(0.0f) {
    
    if (!crop) {
        CCLOG("CropAdapter::CropAdapter - Warning: null crop pointer provided");
        isActiveFlag = false;
        return;
    }
    
    initializeSprite();
}

CropAdapter::~CropAdapter() {
    cleanup();
}

// === 基础属性实现 ===

std::string CropAdapter::getName() const {
    return crop ? crop->GetName() : "Unknown Crop";
}

// === 位置管理实现 ===

void CropAdapter::setPosition(const cocos2d::Vec2& pos) {
    position = pos;
    if (sprite) {
        sprite->setPosition(pos);
    }
}

cocos2d::Rect CropAdapter::getBounds() const {
    if (sprite) {
        return sprite->getBoundingBox();
    }
    
    // 返回默认大小的边界框
    return Rect(position.x - 16, position.y - 16, 32, 32);
}

// === 渲染相关实现 ===

void CropAdapter::updateTexture(float deltaTime) {
    if (!crop || !sprite) return;
    
    lastUpdateTime += deltaTime;
    
    // 每0.5秒检查一次是否需要更新纹理
    if (lastUpdateTime >= 0.5f) {
        updateCropAppearance();
        lastUpdateTime = 0.0f;
    }
}

bool CropAdapter::isVisible() const {
    return sprite ? sprite->isVisible() : false;
}

void CropAdapter::setVisible(bool visible) {
    if (sprite) {
        sprite->setVisible(visible);
    }
}

// === 生命周期管理实现 ===

void CropAdapter::update(float deltaTime) {
    if (!crop || !isActiveFlag) return;
    
    // 更新纹理
    updateTexture(deltaTime);
    
    // 检查生长条件并更新作物状态
    if (checkGrowthConditions()) {
        // 作物生长逻辑在onDayPass中处理
    }
}

void CropAdapter::cleanup() {
    if (sprite) {
        sprite->removeFromParent();
        sprite = nullptr;
    }
    crop.reset();
    isActiveFlag = false;
}

// === 交互能力实现 ===

bool CropAdapter::canInteract() const {
    if (!crop) return false;
    
    // 成熟的作物可以收获，种子可以浇水
    return isHarvestable() || needsWater() || crop->IsSeed();
}

void CropAdapter::onInteract(GameObjectInterface* interactor) {
    if (!crop || !interactor) return;
    
    CCLOG("CropAdapter::onInteract - %s interacted with crop %s", 
          interactor->getName().c_str(), getName().c_str());
    
    // 根据作物状态决定交互行为
    if (isHarvestable()) {
        CCLOG("Crop is ready to harvest!");
        // 这里可以触发收获UI或直接收获
    } else if (needsWater()) {
        CCLOG("Crop needs water!");
        // 这里可以提示玩家浇水
    }
}

std::string CropAdapter::getInteractionHint() const {
    if (!crop) return "";
    
    if (isHarvestable()) {
        return "Harvest " + getName();
    } else if (needsWater()) {
        return "Water " + getName();
    } else if (crop->IsSeed()) {
        return getName() + " (Growing)";
    }
    
    return getName();
}

// === 收获能力实现 ===

bool CropAdapter::isHarvestable() const {
    return crop ? crop->IsHarvestable() : false;
}

std::shared_ptr<class Item> CropAdapter::harvest() {
    if (!crop || !isHarvestable()) {
        return nullptr;
    }
    
    CCLOG("CropAdapter::harvest - Harvesting %s", getName().c_str());
    
    // 获取作物副本作为收获物
    auto harvestedItem = crop->GetCopy();
    
    // 销毁作物
    crop.reset();
    isActiveFlag = false;
    
    return harvestedItem;
}

// === 成长能力实现 ===

float CropAdapter::getGrowthProgress() const {
    return calculateGrowthPercentage();
}

void CropAdapter::water() {
    if (!crop) return;
    
    crop->Water();
    CCLOG("CropAdapter::water - Watered %s", getName().c_str());
}

bool CropAdapter::needsWater() const {
    if (!crop) return false;
    
    // 只有在生长期且今天未浇水时才需要浇水
    return !crop->watered && !crop->IsMature() && crop->GetPhase() != DEAD;
}

void CropAdapter::advanceGrowth() {
    if (!crop) return;
    
    crop->UpdateGrowth();
    updateCropAppearance();
}

// === 状态查询实现 ===

std::string CropAdapter::getStatusText() const {
    if (!crop) return "Crop (Invalid)";
    
    std::string status = getName();
    
    switch (crop->GetPhase()) {
        case SEED:
            status += " (Seed)";
            break;
        case GROWING:
            status += " (Growing " + std::to_string((int)(getGrowthProgress() * 100)) + "%)";
            break;
        case MATURE:
            status += " (Ready to Harvest)";
            break;
        case SAPLESS:
            status += " (Withered)";
            break;
        case DEAD:
            status += " (Dead)";
            break;
    }
    
    if (needsWater()) {
        status += " [Needs Water]";
    } else if (crop->watered) {
        status += " [Watered]";
    }
    
    return status;
}

float CropAdapter::getHealth() const {
    if (!crop) return 0.0f;
    
    // 根据作物阶段计算"健康度"
    switch (crop->GetPhase()) {
        case DEAD: return 0.0f;
        case SAPLESS: return 0.2f;
        case SEED: return 0.5f;
        case GROWING: return 0.8f;
        case MATURE: return 1.0f;
        default: return 0.5f;
    }
}

// === 事件回调实现 ===

void CropAdapter::onCollisionEnter(GameObjectInterface* other) {
    if (!crop || !other) return;
    
    CCLOG("CropAdapter::onCollisionEnter - %s collided with crop %s", 
          other->getName().c_str(), getName().c_str());
}

void CropAdapter::onCollisionExit(GameObjectInterface* other) {
    // 作物通常不需要处理碰撞退出事件
}

void CropAdapter::onDayPass() {
    if (!crop) return;
    
    CCLOG("CropAdapter::onDayPass - New day for crop %s", getName().c_str());
    
    // 更新作物生长
    advanceGrowth();
    
    // 重置浇水状态
    crop->watered = false;
}

void CropAdapter::onSeasonChange(const std::string& newSeason) {
    if (!crop) return;
    
    CCLOG("CropAdapter::onSeasonChange - Crop %s season change to: %s", 
          getName().c_str(), newSeason.c_str());
    
    // 如果作物不适合新季节，设为枯死
    if (!isSuitableForSeason(newSeason)) {
        setDead();
    }
}

// === Crop特有方法实现 ===

Phase CropAdapter::getCropPhase() const {
    return crop ? crop->GetPhase() : DEAD;
}

std::string CropAdapter::getCropSeason() const {
    return crop ? crop->GetSeason() : "";
}

int CropAdapter::getPlantDay() const {
    return crop ? crop->GetGrowthProgress() : 0;
}

int CropAdapter::getMatureNeeded() const {
    // 这个方法在Crop类中可能没有直接暴露，可能需要添加
    return 4; // 默认值，应该从Crop类获取
}

bool CropAdapter::isWateredToday() const {
    return crop ? crop->watered : false;
}

void CropAdapter::setWatered(bool watered) {
    if (crop) {
        crop->watered = watered;
    }
}

int CropAdapter::getCropValue() const {
    return crop ? crop->GetValue() : 0;
}

void CropAdapter::setDead() {
    if (crop) {
        crop->SetDead();
        updateCropAppearance();
    }
}

bool CropAdapter::isSeed() const {
    return crop ? crop->IsSeed() : false;
}

bool CropAdapter::isMature() const {
    return crop ? crop->IsMature() : false;
}

bool CropAdapter::isDead() const {
    return crop ? (crop->GetPhase() == DEAD) : true;
}

void CropAdapter::forceGrowthUpdate() {
    if (crop) {
        crop->UpdateGrowth();
        updateCropAppearance();
    }
}

std::shared_ptr<Crop> CropAdapter::getCropCopy() const {
    return crop ? crop->GetCropCopy() : nullptr;
}

std::string CropAdapter::getTexturePathForPhase(Phase phase) const {
    if (!crop) return "";
    
    switch (phase) {
        case SEED:
        case GROWING:
            return crop->growing_pic;
        case MATURE:
            return crop->mature_pic;
        case SAPLESS:
        case DEAD:
        default:
            return crop->initial_pic;
    }
}

bool CropAdapter::isSuitableForSeason(const std::string& currentSeason) const {
    if (!crop) return false;
    
    return crop->GetSeason() == currentSeason;
}

// === 私有方法实现 ===

void CropAdapter::initializeSprite() {
    if (!crop) return;
    
    // 创建精灵并设置初始纹理
    sprite = Sprite::create(crop->initial_pic);
    if (sprite) {
        sprite->setPosition(position);
        updateCropAppearance();
    } else {
        CCLOG("CropAdapter::initializeSprite - Failed to create sprite for %s", getName().c_str());
    }
}

void CropAdapter::updateCropAppearance() {
    if (!crop || !sprite) return;
    
    std::string texturePath = getTexturePathForPhase(crop->GetPhase());
    if (!texturePath.empty()) {
        auto texture = Director::getInstance()->getTextureCache()->addImage(texturePath);
        if (texture) {
            sprite->setTexture(texture);
        }
    }
    
    // 根据作物状态调整透明度或颜色
    switch (crop->GetPhase()) {
        case DEAD:
            sprite->setColor(Color3B(100, 100, 100)); // 灰色
            break;
        case SAPLESS:
            sprite->setColor(Color3B(150, 120, 100)); // 褐色
            break;
        default:
            sprite->setColor(Color3B::WHITE); // 正常颜色
            break;
    }
}

bool CropAdapter::checkGrowthConditions() const {
    if (!crop) return false;
    
    // 检查作物是否适合当前季节
    if (!isSuitableForSeason(Season)) {
        return false;
    }
    
    // 检查是否已死亡
    if (crop->GetPhase() == DEAD) {
        return false;
    }
    
    return true;
}

float CropAdapter::calculateGrowthPercentage() const {
    if (!crop) return 0.0f;
    
    if (crop->GetPhase() == MATURE) {
        return 1.0f;
    }
    
    int growthDays = crop->GetGrowthProgress();
    int requiredDays = getMatureNeeded();
    
    if (requiredDays <= 0) {
        return 1.0f;
    }
    
    return std::min(1.0f, (float)growthDays / (float)requiredDays);
}
