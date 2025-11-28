#include "PlayerAdapter.h"
#include "../Inventory.h"
#include "cocos2d.h"

USING_NS_CC;

PlayerAdapter::PlayerAdapter(Player* playerPtr, const std::string& objectId)
    : player(playerPtr), id(objectId), isActiveFlag(true), interactionRange(50.0f) {
    if (!player) {
        CCLOG("PlayerAdapter::PlayerAdapter - Warning: null player pointer provided");
        isActiveFlag = false;
    }
}

// === 位置管理实现 ===

cocos2d::Vec2 PlayerAdapter::getPosition() const {
    return player ? player->getPosition() : Vec2::ZERO;
}

void PlayerAdapter::setPosition(const cocos2d::Vec2& pos) {
    if (player) {
        player->setPosition(pos);
    }
}

cocos2d::Rect PlayerAdapter::getBounds() const {
    if (player) {
        return player->getBoundingBox();
    }
    return Rect::ZERO;
}

// === 渲染相关实现 ===

cocos2d::Node* PlayerAdapter::getRenderNode() const {
    return player;
}

void PlayerAdapter::updateTexture(float deltaTime) {
    if (!player) return;
    
    updateAnimation();
}

bool PlayerAdapter::isVisible() const {
    return player ? player->isVisible() : false;
}

void PlayerAdapter::setVisible(bool visible) {
    if (player) {
        player->setVisible(visible);
    }
}

// === 生命周期管理实现 ===

void PlayerAdapter::update(float deltaTime) {
    if (!player || !isActiveFlag) return;
    
    // 执行玩家的移动逻辑
    player->player1_move();
    
    // 更新纹理和动画
    updateTexture(deltaTime);
}

void PlayerAdapter::cleanup() {
    // 注意：这里不删除player对象，因为它可能被其他地方管理
    player = nullptr;
    isActiveFlag = false;
}

// === 交互能力实现 ===

void PlayerAdapter::onInteract(GameObjectInterface* interactor) {
    if (!player || !interactor) return;
    
    CCLOG("PlayerAdapter::onInteract - Player interacted with %s", 
          interactor->getName().c_str());
}

// === 移动能力实现 ===

float PlayerAdapter::getMovementSpeed() const {
    return player ? player->speed : 0.0f;
}

void PlayerAdapter::moveTo(const cocos2d::Vec2& target) {
    if (!player) return;
    
    // 计算移动方向
    Vec2 currentPos = player->getPosition();
    Vec2 direction = target - currentPos;
    direction.normalize();
    
    // 根据方向设置移动状态
    // 这是一个简化的实现，实际可能需要更复杂的路径寻找
    if (abs(direction.x) > abs(direction.y)) {
        if (direction.x > 0) {
            setMovementState(Player::DIRECTION_RIGHT, true);
        } else {
            setMovementState(Player::DIRECTION_LEFT, true);
        }
    } else {
        if (direction.y > 0) {
            setMovementState(Player::DIRECTION_UP, true);
        } else {
            setMovementState(Player::DIRECTION_DOWN, true);
        }
    }
}

void PlayerAdapter::stopMovement() {
    if (!player) return;
    
    // 停止所有方向的移动
    player->moveLeft = false;
    player->moveRight = false;
    player->moveUp = false;
    player->moveDown = false;
    
    player->leftpressed = false;
    player->rightpressed = false;
    player->uppressed = false;
    player->downpressed = false;
}

// === 库存管理能力实现 ===

bool PlayerAdapter::canStore(std::shared_ptr<class Item> item) const {
    if (!player || !item) return false;
    
    // 这里需要访问玩家的库存系统
    // 假设有全局的库存管理器或者Player类有inventory成员
    // 目前返回true作为占位符
    return true;
}

bool PlayerAdapter::addItem(std::shared_ptr<class Item> item) {
    if (!player || !item) return false;
    
    // TODO: 实现添加物品到玩家库存的逻辑
    // 这需要与现有的库存系统集成
    CCLOG("PlayerAdapter::addItem - Added item: %s", item->GetName().c_str());
    return true;
}

std::shared_ptr<class Item> PlayerAdapter::removeItem(const std::string& itemName) {
    if (!player) return nullptr;
    
    // TODO: 实现从玩家库存移除物品的逻辑
    CCLOG("PlayerAdapter::removeItem - Removed item: %s", itemName.c_str());
    return nullptr;
}

std::vector<std::shared_ptr<class Item>> PlayerAdapter::getInventoryItems() const {
    std::vector<std::shared_ptr<class Item>> items;
    
    if (!player) return items;
    
    // TODO: 实现获取玩家库存物品列表的逻辑
    return items;
}

// === 状态查询实现 ===

std::string PlayerAdapter::getStatusText() const {
    if (!player) return "Player (Invalid)";
    
    std::string status = "Player";
    if (isMoving()) {
        status += " (Moving)";
    } else {
        status += " (Idle)";
    }
    
    return status;
}

// === 事件回调实现 ===

void PlayerAdapter::onCollisionEnter(GameObjectInterface* other) {
    if (!player || !other) return;
    
    CCLOG("PlayerAdapter::onCollisionEnter - Player collided with %s", 
          other->getName().c_str());
    
    // 可以在这里实现碰撞逻辑，如拾取物品、触发对话等
}

void PlayerAdapter::onCollisionExit(GameObjectInterface* other) {
    if (!player || !other) return;
    
    CCLOG("PlayerAdapter::onCollisionExit - Player stopped colliding with %s", 
          other->getName().c_str());
}

void PlayerAdapter::onDayPass() {
    if (!player) return;
    
    CCLOG("PlayerAdapter::onDayPass - New day for player");
    // 可以在这里实现新一天的玩家状态重置逻辑
}

void PlayerAdapter::onSeasonChange(const std::string& newSeason) {
    if (!player) return;
    
    CCLOG("PlayerAdapter::onSeasonChange - New season: %s", newSeason.c_str());
    // 可以在这里实现季节变化对玩家的影响
}

// === 玩家特有方法实现 ===

bool PlayerAdapter::getMovementState(int direction) const {
    if (!player) return false;
    
    return player->getMovementState(direction);
}

void PlayerAdapter::setMovementState(Player::MovementDirection direction, bool isPressed) {
    if (!player) return;
    
    player->setMovementState(direction, isPressed);
}

int PlayerAdapter::getLookState() const {
    return player ? player->look_state : 0;
}

bool PlayerAdapter::canInteractWith(const cocos2d::Vec2& targetPos) const {
    if (!player) return false;
    
    float distance = getPosition().distance(targetPos);
    return distance <= interactionRange;
}

// === 私有方法实现 ===

void PlayerAdapter::updateAnimation() {
    if (!player) return;
    
    // 如果玩家在移动，触发动画切换
    if (isMoving()) {
        player->player_change();
    }
    
    // 根据移动状态更新纹理
    int direction = 0; // 默认向下
    if (player->moveUp) direction = 0;
    else if (player->moveDown) direction = 1; 
    else if (player->moveLeft) direction = 2;
    else if (player->moveRight) direction = 3;
    
    player->updateTexture(direction);
}

bool PlayerAdapter::isMoving() const {
    if (!player) return false;
    
    return player->moveLeft || player->moveRight || 
           player->moveUp || player->moveDown;
}
