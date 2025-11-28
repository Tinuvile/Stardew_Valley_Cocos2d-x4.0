#include "TreeAdapter.h"
#include "cocos2d.h"

USING_NS_CC;

// 外部全局变量
extern int day;

TreeAdapter::TreeAdapter(std::shared_ptr<Tree> treePtr, const std::string& objectId)
    : tree(treePtr), id(objectId), sprite(nullptr), isActiveFlag(true), isBeingHarvested(false) {
    
    if (!tree) {
        CCLOG("TreeAdapter::TreeAdapter - Warning: null tree pointer provided");
        isActiveFlag = false;
        return;
    }
    
    initializeSprite();
}

TreeAdapter::~TreeAdapter() {
    cleanup();
}

// === 基础属性实现 ===

std::string TreeAdapter::getName() const {
    return tree ? tree->GetName() : "Unknown Tree";
}

// === 位置管理实现 ===

cocos2d::Vec2 TreeAdapter::getPosition() const {
    return tree ? tree->position : Vec2::ZERO;
}

void TreeAdapter::setPosition(const cocos2d::Vec2& pos) {
    if (tree) {
        tree->position = pos;
        if (sprite) {
            sprite->setPosition(pos);
        }
    }
}

cocos2d::Rect TreeAdapter::getBounds() const {
    if (sprite) {
        return sprite->getBoundingBox();
    }
    
    // 返回默认大小的边界框
    Vec2 pos = getPosition();
    return Rect(pos.x - 32, pos.y - 32, 64, 64);
}

// === 渲染相关实现 ===

void TreeAdapter::updateTexture(float deltaTime) {
    if (!tree || !sprite) return;
    
    updateTreeAppearance();
}

bool TreeAdapter::isVisible() const {
    return sprite ? sprite->isVisible() : false;
}

void TreeAdapter::setVisible(bool visible) {
    if (sprite) {
        sprite->setVisible(visible);
    }
}

// === 生命周期管理实现 ===

void TreeAdapter::update(float deltaTime) {
    if (!tree || !isActiveFlag) return;
    
    checkRecovery();
    updateTexture(deltaTime);
}

void TreeAdapter::cleanup() {
    if (sprite) {
        sprite->removeFromParent();
        sprite = nullptr;
    }
    tree.reset();
    isActiveFlag = false;
}

// === 交互能力实现 ===

bool TreeAdapter::canInteract() const {
    return tree && tree->available && !isBeingHarvested;
}

void TreeAdapter::onInteract(GameObjectInterface* interactor) {
    if (!tree || !interactor || !canInteract()) return;
    
    CCLOG("TreeAdapter::onInteract - %s is chopping tree %s", 
          interactor->getName().c_str(), getName().c_str());
    
    // 执行砍伐
    if (chopTree()) {
        CCLOG("Tree chopped successfully!");
    } else {
        CCLOG("Failed to chop tree");
    }
}

std::string TreeAdapter::getInteractionHint() const {
    if (!tree) return "";
    
    if (!tree->available) {
        int daysLeft = getRecoverTime() - (day - tree->mining_day);
        return getName() + " (Recovering: " + std::to_string(daysLeft) + " days)";
    } else if (isBeingHarvested) {
        return getName() + " (Being chopped...)";
    } else {
        return "Chop " + getName();
    }
}

// === 收获能力实现 ===

bool TreeAdapter::isHarvestable() const {
    return tree && tree->available;
}

std::shared_ptr<class Item> TreeAdapter::harvest() {
    if (!tree || !isHarvestable()) {
        return nullptr;
    }
    
    CCLOG("TreeAdapter::harvest - Chopping tree %s", getName().c_str());
    
    // 获取产品
    auto product = tree->GetCopy();
    
    // 更新树木状态
    tree->removetimes--;
    tree->mining_day = day;
    
    if (tree->removetimes <= 0) {
        // 树木被完全砍伐，需要恢复
        tree->available = false;
        tree->removetimes = 2; // 重置砍伐次数
    }
    
    updateTreeAppearance();
    
    return product;
}

// === 状态查询实现 ===

std::string TreeAdapter::getStatusText() const {
    if (!tree) return "Tree (Invalid)";
    
    std::string status = getName();
    
    if (!tree->available) {
        status += " (Recovering)";
        float progress = getRecoveryProgress();
        status += " [" + std::to_string((int)(progress * 100)) + "%]";
    } else {
        status += " (Available)";
        status += " [" + std::to_string(tree->removetimes) + " chops left]";
    }
    
    return status;
}

float TreeAdapter::getHealth() const {
    if (!tree) return 0.0f;
    
    if (!tree->available) {
        return getRecoveryProgress();
    }
    
    // 根据剩余砍伐次数计算健康度
    return (float)tree->removetimes / 2.0f;
}

// === 事件回调实现 ===

void TreeAdapter::onCollisionEnter(GameObjectInterface* other) {
    if (!tree || !other) return;
    
    CCLOG("TreeAdapter::onCollisionEnter - %s collided with tree %s", 
          other->getName().c_str(), getName().c_str());
}

void TreeAdapter::onCollisionExit(GameObjectInterface* other) {
    // 树木通常不需要处理碰撞退出事件
}

void TreeAdapter::onDayPass() {
    if (!tree) return;
    
    CCLOG("TreeAdapter::onDayPass - New day for tree %s", getName().c_str());
    
    checkRecovery();
}

void TreeAdapter::onSeasonChange(const std::string& newSeason) {
    if (!tree) return;
    
    CCLOG("TreeAdapter::onSeasonChange - Tree %s season change to: %s", 
          getName().c_str(), newSeason.c_str());
    
    // 不同季节可能影响树木的外观或生长速度
    updateTreeAppearance();
}

// === Tree特有方法实现 ===

int TreeAdapter::getRemoveTimes() const {
    return tree ? tree->removetimes : 0;
}

int TreeAdapter::getRecoverTime() const {
    return tree ? tree->recover_time : 0;
}

int TreeAdapter::getMiningDay() const {
    return tree ? tree->mining_day : 0;
}

bool TreeAdapter::isAvailable() const {
    return tree ? tree->available : false;
}

void TreeAdapter::setAvailable(bool available) {
    if (tree) {
        tree->available = available;
        updateTreeAppearance();
    }
}

bool TreeAdapter::chopTree() {
    if (!tree || !tree->available || isBeingHarvested) {
        return false;
    }
    
    isBeingHarvested = true;
    
    // 执行砍伐逻辑
    auto product = harvest();
    
    isBeingHarvested = false;
    
    return product != nullptr;
}

std::string TreeAdapter::getCurrentTexturePath() const {
    if (!tree) return "";
    
    if (tree->available) {
        return tree->initial_pic;
    } else {
        return tree->G_Cut_pic; // 被砍伐后的样子
    }
}

bool TreeAdapter::isRecovering() const {
    return tree && !tree->available;
}

float TreeAdapter::getRecoveryProgress() const {
    return calculateRecoveryProgress();
}

void TreeAdapter::forceRecover() {
    if (tree) {
        tree->available = true;
        tree->removetimes = 2;
        tree->mining_day = 0;
        updateTreeAppearance();
        
        CCLOG("TreeAdapter::forceRecover - Tree %s recovered", getName().c_str());
    }
}

std::shared_ptr<class Item> TreeAdapter::getProduct() const {
    return tree ? tree->GetCopy() : nullptr;
}

// === 私有方法实现 ===

void TreeAdapter::initializeSprite() {
    if (!tree) return;
    
    // 创建精灵并设置初始纹理
    sprite = Sprite::create(tree->initial_pic);
    if (sprite) {
        sprite->setPosition(tree->position);
        updateTreeAppearance();
    } else {
        CCLOG("TreeAdapter::initializeSprite - Failed to create sprite for %s", getName().c_str());
    }
}

void TreeAdapter::updateTreeAppearance() {
    if (!tree || !sprite) return;
    
    std::string texturePath = getCurrentTexturePath();
    if (!texturePath.empty()) {
        auto texture = Director::getInstance()->getTextureCache()->addImage(texturePath);
        if (texture) {
            sprite->setTexture(texture);
        }
    }
    
    // 根据树木状态调整外观
    if (!tree->available) {
        // 被砍伐的树显示为较暗的颜色
        sprite->setColor(Color3B(150, 150, 150));
    } else {
        // 正常树木
        sprite->setColor(Color3B::WHITE);
    }
}

void TreeAdapter::checkRecovery() {
    if (!tree || tree->available) return;
    
    // 检查是否到了恢复时间
    int daysSinceChopped = day - tree->mining_day;
    if (daysSinceChopped >= tree->recover_time) {
        tree->available = true;
        updateTreeAppearance();
        
        CCLOG("TreeAdapter::checkRecovery - Tree %s has recovered", getName().c_str());
    }
}

float TreeAdapter::calculateRecoveryProgress() const {
    if (!tree || tree->available) {
        return 1.0f;
    }
    
    int daysSinceChopped = day - tree->mining_day;
    if (tree->recover_time <= 0) {
        return 1.0f;
    }
    
    return std::min(1.0f, (float)daysSinceChopped / (float)tree->recover_time);
}
