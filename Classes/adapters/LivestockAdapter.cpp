#include "LivestockAdapter.h"
#include "cocos2d.h"

USING_NS_CC;

LivestockAdapter::LivestockAdapter(Livestock* livestockPtr, const std::string& objectId)
    : livestock(livestockPtr), id(objectId), isActiveFlag(true), 
      lastMoveTime(0.0f), moveInterval(3.0f), 
      lastProductionTime(0.0f), productionInterval(24.0f * 60.0f * 60.0f) { // 24小时生产间隔
    
    if (!livestock) {
        CCLOG("LivestockAdapter::LivestockAdapter - Warning: null livestock pointer provided");
        isActiveFlag = false;
    }
}

// === 基础属性实现 ===

std::string LivestockAdapter::getName() const {
    if (!livestock) return "Unknown Livestock";
    
    return livestock->GetSpecies();
}

// === 位置管理实现 ===

cocos2d::Vec2 LivestockAdapter::getPosition() const {
    return livestock ? livestock->getPosition() : Vec2::ZERO;
}

void LivestockAdapter::setPosition(const cocos2d::Vec2& pos) {
    if (livestock) {
        livestock->setPosition(pos);
    }
}

cocos2d::Rect LivestockAdapter::getBounds() const {
    if (livestock) {
        return livestock->getBoundingBox();
    }
    return Rect::ZERO;
}

// === 渲染相关实现 ===

cocos2d::Node* LivestockAdapter::getRenderNode() const {
    return livestock;
}

void LivestockAdapter::updateTexture(float deltaTime) {
    if (!livestock) return;
    
    livestock->UpdateTexture(deltaTime);
}

bool LivestockAdapter::isVisible() const {
    return livestock ? livestock->isVisible() : false;
}

void LivestockAdapter::setVisible(bool visible) {
    if (livestock) {
        livestock->setVisible(visible);
    }
}

// === 生命周期管理实现 ===

void LivestockAdapter::update(float deltaTime) {
    if (!livestock || !isActiveFlag) return;
    
    updateBehavior(deltaTime);
    updateTexture(deltaTime);
}

void LivestockAdapter::cleanup() {
    // 注意：这里不删除livestock对象，因为它可能被其他地方管理
    livestock = nullptr;
    isActiveFlag = false;
}

// === 交互能力实现 ===

void LivestockAdapter::onInteract(GameObjectInterface* interactor) {
    if (!livestock || !interactor) return;
    
    CCLOG("LivestockAdapter::onInteract - %s interacted with %s %s", 
          interactor->getName().c_str(), getName().c_str(), livestock->GetSpecies().c_str());
    
    // 如果可以生产，尝试收集产品
    if (isReadyToProduce()) {
        auto product = produce();
        if (product) {
            CCLOG("Collected product: %s", product->GetName().c_str());
            // 这里可以将产品添加到玩家背包
        }
    } else {
        CCLOG("%s is not ready to produce yet", getName().c_str());
    }
}

std::string LivestockAdapter::getInteractionHint() const {
    if (!livestock) return "";
    
    if (isReadyToProduce()) {
        return "Collect from " + getName();
    } else {
        return getName() + " (Not ready)";
    }
}

// === 移动能力实现 ===

void LivestockAdapter::moveTo(const cocos2d::Vec2& target) {
    if (!livestock) return;
    
    // 检查目标位置是否在允许的移动范围内
    if (!isPositionInMoveArea(target)) {
        CCLOG("LivestockAdapter::moveTo - Target position is outside move area");
        return;
    }
    
    setPosition(target);
    setMoving(true);
}

void LivestockAdapter::randomMove() {
    if (!livestock) return;
    
    livestock->RandomMove();
}

void LivestockAdapter::stopMovement() {
    if (!livestock) return;
    
    livestock->SetMoving(false);
}

// === 生产能力实现 ===

bool LivestockAdapter::isReadyToProduce() const {
    if (!livestock) return false;
    
    return livestock->IsCanProduce();
}

std::shared_ptr<class Item> LivestockAdapter::produce() {
    if (!livestock || !isReadyToProduce()) {
        return nullptr;
    }
    
    CCLOG("LivestockAdapter::produce - %s is producing", getName().c_str());
    
    auto product = livestock->ProduceProduct();
    
    if (product) {
        // 重置生产状态
        livestock->SetCanProduce(false);
        lastProductionTime = 0.0f;
        
        CCLOG("LivestockAdapter::produce - Produced: %s", product->GetName().c_str());
    }
    
    return product;
}

float LivestockAdapter::getProductionProgress() const {
    if (!livestock) return 0.0f;
    
    if (isReadyToProduce()) {
        return 1.0f;
    }
    
    // 根据时间计算生产进度
    return std::min(1.0f, lastProductionTime / productionInterval);
}

// === 状态查询实现 ===

std::string LivestockAdapter::getStatusText() const {
    if (!livestock) return "Livestock (Invalid)";
    
    std::string status = getName() + " (" + livestock->GetSpecies() + ")";
    
    if (isReadyToProduce()) {
        status += " [Ready]";
    } else {
        int progressPercent = (int)(getProductionProgress() * 100);
        status += " [" + std::to_string(progressPercent) + "%]";
    }
    
    if (isMoving()) {
        status += " (Moving)";
    }
    
    return status;
}

// === 事件回调实现 ===

void LivestockAdapter::onCollisionEnter(GameObjectInterface* other) {
    if (!livestock || !other) return;
    
    CCLOG("LivestockAdapter::onCollisionEnter - %s collided with %s", 
          getName().c_str(), other->getName().c_str());
}

void LivestockAdapter::onCollisionExit(GameObjectInterface* other) {
    if (!livestock || !other) return;
    
    CCLOG("LivestockAdapter::onCollisionExit - %s stopped colliding with %s", 
          getName().c_str(), other->getName().c_str());
}

void LivestockAdapter::onDayPass() {
    if (!livestock) return;
    
    CCLOG("LivestockAdapter::onDayPass - New day for %s", getName().c_str());
    
    // 每天重置生产能力
    updateProduction(24.0f * 60.0f * 60.0f); // 24小时的秒数
}

void LivestockAdapter::onSeasonChange(const std::string& newSeason) {
    if (!livestock) return;
    
    CCLOG("LivestockAdapter::onSeasonChange - %s season change to: %s", 
          getName().c_str(), newSeason.c_str());
    
    // 不同季节可能影响家畜的生产效率
}

// === Livestock特有方法实现 ===

std::string LivestockAdapter::getSpecies() const {
    return livestock ? livestock->GetSpecies() : "";
}

cocos2d::Rect LivestockAdapter::getMoveArea() const {
    // 这个需要从Livestock类获取，如果没有公共接口，返回默认值
    return Rect(0, 0, 800, 600); // 默认移动区域
}

void LivestockAdapter::setMoveArea(const cocos2d::Rect& area) {
    // 如果Livestock类支持设置移动区域，在这里实现
    CCLOG("LivestockAdapter::setMoveArea - Set move area for %s", getName().c_str());
}

bool LivestockAdapter::isMoving() const {
    // 需要从Livestock类获取移动状态
    // 由于Livestock有moving成员变量，但可能是private，这里返回一个估算值
    return true; // 临时实现
}

void LivestockAdapter::setMoving(bool moving) {
    if (livestock) {
        livestock->SetMoving(moving);
    }
}

int LivestockAdapter::getMoveDirection() const {
    // 需要从Livestock类获取移动方向
    // 由于move_direction可能是private，这里返回默认值
    return 0; // 临时实现
}

void LivestockAdapter::setMoveDirection(int direction) {
    // 设置移动方向的实现
    CCLOG("LivestockAdapter::setMoveDirection - Set direction %d for %s", direction, getName().c_str());
}

void LivestockAdapter::setCanProduce(bool canProduce) {
    if (livestock) {
        livestock->SetCanProduce(canProduce);
    }
}

bool LivestockAdapter::isPositionInMoveArea(const cocos2d::Vec2& pos) const {
    Rect moveArea = getMoveArea();
    return moveArea.containsPoint(pos);
}

float LivestockAdapter::getDistanceToMoveAreaBoundary(const cocos2d::Vec2& pos) const {
    Rect moveArea = getMoveArea();
    
    if (moveArea.containsPoint(pos)) {
        // 计算到最近边界的距离
        float distances[4] = {
            pos.x - moveArea.getMinX(),           // 左边界
            moveArea.getMaxX() - pos.x,           // 右边界
            pos.y - moveArea.getMinY(),           // 下边界
            moveArea.getMaxY() - pos.y            // 上边界
        };
        
        return std::min({distances[0], distances[1], distances[2], distances[3]});
    } else {
        // 在区域外，返回负值
        return -1.0f;
    }
}

void LivestockAdapter::feed(const std::string& food) {
    if (!livestock) return;
    
    CCLOG("LivestockAdapter::feed - Fed %s to %s", food.c_str(), getName().c_str());
    
    // 喂食可以提高生产效率或心情
    // 这里可以根据食物类型调整生产间隔
}

bool LivestockAdapter::isHungry() const {
    // 简单的饥饿判断逻辑
    return getProductionProgress() < 0.5f;
}

std::string LivestockAdapter::getMoodStatus() const {
    if (!livestock) return "Unknown";
    
    if (isReadyToProduce()) {
        return "Happy";
    } else if (isHungry()) {
        return "Hungry";
    } else {
        return "Content";
    }
}

// === 私有方法实现 ===

void LivestockAdapter::updateBehavior(float deltaTime) {
    if (!livestock) return;
    
    updateMovement(deltaTime);
    updateProduction(deltaTime);
}

void LivestockAdapter::updateMovement(float deltaTime) {
    if (!livestock) return;
    
    lastMoveTime += deltaTime;
    
    // 定期进行随机移动
    if (lastMoveTime >= moveInterval) {
        randomMove();
        lastMoveTime = 0.0f;
    }
}

void LivestockAdapter::updateProduction(float deltaTime) {
    if (!livestock) return;
    
    lastProductionTime += deltaTime;
    
    // 检查是否达到生产时间
    if (lastProductionTime >= productionInterval && !isReadyToProduce()) {
        livestock->SetCanProduce(true);
        CCLOG("LivestockAdapter::updateProduction - %s is now ready to produce", getName().c_str());
    }
}

cocos2d::Vec2 LivestockAdapter::calculateNextMovePosition() const {
    if (!livestock) return Vec2::ZERO;
    
    Vec2 currentPos = getPosition();
    Rect moveArea = getMoveArea();
    
    // 生成随机移动位置
    float randomX = moveArea.getMinX() + (rand() % (int)moveArea.size.width);
    float randomY = moveArea.getMinY() + (rand() % (int)moveArea.size.height);
    
    return Vec2(randomX, randomY);
}

bool LivestockAdapter::isValidMovePosition(const cocos2d::Vec2& pos) const {
    return isPositionInMoveArea(pos);
}

std::shared_ptr<class Item> LivestockAdapter::getSpeciesSpecificProduct() const {
    if (!livestock) return nullptr;
    
    return livestock->ProduceProduct();
}
