#include "GameObjectManager.h"
#include "cocos2d.h"

USING_NS_CC;

// === 对象管理 ===

bool GameObjectManager::addObject(std::unique_ptr<GameObjectInterface> obj) {
    if (!obj) {
        CCLOG("GameObjectManager::addObject - Null object provided");
        return false;
    }
    
    std::string id = obj->getId();
    std::string type = obj->getType();
    
    if (id.empty()) {
        CCLOG("GameObjectManager::addObject - Object ID cannot be empty");
        return false;
    }
    
    if (hasObject(id)) {
        CCLOG("GameObjectManager::addObject - Object with ID '%s' already exists", id.c_str());
        return false;
    }
    
    // 添加到主存储
    auto objPtr = obj.get();
    objects[id] = std::move(obj);
    
    // 添加到类型组
    addToTypeGroup(type, id);
    
    // 触发事件
    triggerObjectAddedEvent(objPtr);
    
    CCLOG("GameObjectManager::addObject - Added object '%s' of type '%s'", 
          id.c_str(), type.c_str());
    return true;
}

GameObjectInterface* GameObjectManager::getObject(const std::string& id) const {
    auto it = objects.find(id);
    return it != objects.end() ? it->second.get() : nullptr;
}

std::vector<GameObjectInterface*> GameObjectManager::getObjectsByType(const std::string& type) const {
    std::vector<GameObjectInterface*> result;
    
    auto it = typeGroups.find(type);
    if (it != typeGroups.end()) {
        for (const auto& id : it->second) {
            auto obj = getObject(id);
            if (obj && obj->isActive()) {
                result.push_back(obj);
            }
        }
    }
    
    return result;
}

void GameObjectManager::removeObject(const std::string& id) {
    if (isUpdating) {
        // 如果正在更新中，添加到待删除列表
        if (std::find(objectsToRemove.begin(), objectsToRemove.end(), id) == objectsToRemove.end()) {
            objectsToRemove.push_back(id);
        }
    } else {
        removeObjectImmediate(id);
    }
}

void GameObjectManager::removeObjectImmediate(const std::string& id) {
    auto it = objects.find(id);
    if (it == objects.end()) {
        return;
    }
    
    std::string type = it->second->getType();
    
    // 清理对象
    it->second->cleanup();
    
    // 触发移除事件
    triggerObjectRemovedEvent(id, type);
    
    // 从类型组中移除
    removeFromTypeGroup(type, id);
    
    // 从主存储中移除
    objects.erase(it);
    
    CCLOG("GameObjectManager::removeObjectImmediate - Removed object '%s' of type '%s'", 
          id.c_str(), type.c_str());
}

void GameObjectManager::clear() {
    for (auto& pair : objects) {
        pair.second->cleanup();
    }
    
    objects.clear();
    typeGroups.clear();
    objectsToRemove.clear();
    
    CCLOG("GameObjectManager::clear - Cleared all objects");
}

bool GameObjectManager::hasObject(const std::string& id) const {
    return objects.find(id) != objects.end();
}

// === 更新和渲染 ===

void GameObjectManager::updateAll(float deltaTime) {
    isUpdating = true;
    
    // 更新所有激活的对象
    for (auto& pair : objects) {
        auto obj = pair.second.get();
        if (obj && obj->isActive()) {
            obj->update(deltaTime);
        }
    }
    
    isUpdating = false;
    
    // 处理待删除的对象
    processPendingRemovals();
}

void GameObjectManager::addToScene(cocos2d::Scene* scene) {
    if (!scene) {
        CCLOG("GameObjectManager::addToScene - Scene is null");
        return;
    }
    
    for (auto& pair : objects) {
        auto obj = pair.second.get();
        if (obj && obj->isActive()) {
            auto renderNode = obj->getRenderNode();
            if (renderNode && renderNode->getParent() == nullptr) {
                scene->addChild(renderNode);
            }
        }
    }
    
    CCLOG("GameObjectManager::addToScene - Added %zu objects to scene", objects.size());
}

void GameObjectManager::removeFromScene(cocos2d::Scene* scene) {
    if (!scene) {
        return;
    }
    
    for (auto& pair : objects) {
        auto obj = pair.second.get();
        if (obj) {
            auto renderNode = obj->getRenderNode();
            if (renderNode && renderNode->getParent() == scene) {
                renderNode->removeFromParent();
            }
        }
    }
    
    CCLOG("GameObjectManager::removeFromScene - Removed objects from scene");
}

// === 查询功能 ===

std::vector<GameObjectInterface*> GameObjectManager::getObjectsInRange(
    const cocos2d::Vec2& center, 
    float radius,
    const std::string& filterType) const {
    
    std::vector<GameObjectInterface*> result;
    
    for (auto& pair : objects) {
        auto obj = pair.second.get();
        if (!obj || !obj->isActive()) {
            continue;
        }
        
        // 类型过滤
        if (!filterType.empty() && obj->getType() != filterType) {
            continue;
        }
        
        // 距离检查
        float distance = center.distance(obj->getPosition());
        if (distance <= radius) {
            result.push_back(obj);
        }
    }
    
    return result;
}

std::vector<GameObjectInterface*> GameObjectManager::getObjectsInArea(
    const cocos2d::Rect& area,
    const std::string& filterType) const {
    
    std::vector<GameObjectInterface*> result;
    
    for (auto& pair : objects) {
        auto obj = pair.second.get();
        if (!obj || !obj->isActive()) {
            continue;
        }
        
        // 类型过滤
        if (!filterType.empty() && obj->getType() != filterType) {
            continue;
        }
        
        // 区域检查
        if (area.containsPoint(obj->getPosition()) || 
            area.intersectsRect(obj->getBounds())) {
            result.push_back(obj);
        }
    }
    
    return result;
}

std::vector<GameObjectInterface*> GameObjectManager::getInteractableObjects(
    const cocos2d::Vec2& position, 
    float radius) const {
    
    std::vector<GameObjectInterface*> result;
    
    auto nearbyObjects = getObjectsInRange(position, radius);
    for (auto obj : nearbyObjects) {
        if (obj->canInteract()) {
            result.push_back(obj);
        }
    }
    
    return result;
}

GameObjectInterface* GameObjectManager::getNearestObject(
    const cocos2d::Vec2& position,
    const std::string& filterType) const {
    
    GameObjectInterface* nearest = nullptr;
    float minDistance = std::numeric_limits<float>::max();
    
    for (auto& pair : objects) {
        auto obj = pair.second.get();
        if (!obj || !obj->isActive()) {
            continue;
        }
        
        // 类型过滤
        if (!filterType.empty() && obj->getType() != filterType) {
            continue;
        }
        
        float distance = position.distance(obj->getPosition());
        if (distance < minDistance) {
            minDistance = distance;
            nearest = obj;
        }
    }
    
    return nearest;
}

// === 碰撞检测 ===

std::vector<std::pair<GameObjectInterface*, GameObjectInterface*>> 
GameObjectManager::checkAllCollisions() const {
    std::vector<std::pair<GameObjectInterface*, GameObjectInterface*>> collisions;
    
    std::vector<GameObjectInterface*> activeObjects;
    for (auto& pair : objects) {
        auto obj = pair.second.get();
        if (obj && obj->isActive()) {
            activeObjects.push_back(obj);
        }
    }
    
    for (size_t i = 0; i < activeObjects.size(); ++i) {
        for (size_t j = i + 1; j < activeObjects.size(); ++j) {
            if (isColliding(activeObjects[i], activeObjects[j])) {
                collisions.push_back({activeObjects[i], activeObjects[j]});
                
                // 触发碰撞事件
                activeObjects[i]->onCollisionEnter(activeObjects[j]);
                activeObjects[j]->onCollisionEnter(activeObjects[i]);
            }
        }
    }
    
    return collisions;
}

std::vector<GameObjectInterface*> GameObjectManager::checkCollisions(
    const std::string& objectId) const {
    
    std::vector<GameObjectInterface*> collisions;
    
    auto targetObj = getObject(objectId);
    if (!targetObj || !targetObj->isActive()) {
        return collisions;
    }
    
    for (auto& pair : objects) {
        auto obj = pair.second.get();
        if (obj && obj != targetObj && obj->isActive()) {
            if (isColliding(targetObj, obj)) {
                collisions.push_back(obj);
            }
        }
    }
    
    return collisions;
}

bool GameObjectManager::isColliding(GameObjectInterface* obj1, GameObjectInterface* obj2) {
    if (!obj1 || !obj2) {
        return false;
    }
    
    return obj1->getBounds().intersectsRect(obj2->getBounds());
}

// === 事件系统 ===

void GameObjectManager::onObjectAdded(std::function<void(GameObjectInterface*)> callback) {
    onObjectAddedCallbacks.push_back(callback);
}

void GameObjectManager::onObjectRemoved(std::function<void(const std::string&, const std::string&)> callback) {
    onObjectRemovedCallbacks.push_back(callback);
}

void GameObjectManager::broadcastDayPass() {
    for (auto& pair : objects) {
        auto obj = pair.second.get();
        if (obj && obj->isActive()) {
            obj->onDayPass();
        }
    }
    
    CCLOG("GameObjectManager::broadcastDayPass - Day pass event sent to %zu objects", objects.size());
}

void GameObjectManager::broadcastSeasonChange(const std::string& newSeason) {
    for (auto& pair : objects) {
        auto obj = pair.second.get();
        if (obj && obj->isActive()) {
            obj->onSeasonChange(newSeason);
        }
    }
    
    CCLOG("GameObjectManager::broadcastSeasonChange - Season change to '%s' sent to %zu objects", 
          newSeason.c_str(), objects.size());
}

// === 调试和统计 ===

std::unordered_map<std::string, int> GameObjectManager::getObjectStats() const {
    std::unordered_map<std::string, int> stats;
    
    for (auto& pair : objects) {
        auto obj = pair.second.get();
        if (obj) {
            stats[obj->getType()]++;
        }
    }
    
    return stats;
}

void GameObjectManager::printDebugInfo() const {
    CCLOG("=== GameObjectManager Debug Info ===");
    CCLOG("Total objects: %zu", objects.size());
    
    auto stats = getObjectStats();
    for (auto& pair : stats) {
        CCLOG("  %s: %d", pair.first.c_str(), pair.second);
    }
    
    CCLOG("Type groups: %zu", typeGroups.size());
    CCLOG("Pending removals: %zu", objectsToRemove.size());
    CCLOG("=====================================");
}

bool GameObjectManager::validateIntegrity() const {
    // 检查所有对象在类型组中都有对应条目
    for (auto& pair : objects) {
        auto obj = pair.second.get();
        if (!obj) continue;
        
        std::string type = obj->getType();
        std::string id = obj->getId();
        
        auto typeIt = typeGroups.find(type);
        if (typeIt == typeGroups.end()) {
            CCLOG("GameObjectManager::validateIntegrity - Type group missing for type '%s'", type.c_str());
            return false;
        }
        
        auto& ids = typeIt->second;
        if (std::find(ids.begin(), ids.end(), id) == ids.end()) {
            CCLOG("GameObjectManager::validateIntegrity - Object '%s' not found in type group '%s'", 
                  id.c_str(), type.c_str());
            return false;
        }
    }
    
    return true;
}

// === 私有方法 ===

void GameObjectManager::processPendingRemovals() {
    for (const auto& id : objectsToRemove) {
        removeObjectImmediate(id);
    }
    objectsToRemove.clear();
}

void GameObjectManager::removeFromTypeGroup(const std::string& type, const std::string& id) {
    auto it = typeGroups.find(type);
    if (it != typeGroups.end()) {
        auto& ids = it->second;
        ids.erase(std::remove(ids.begin(), ids.end(), id), ids.end());
        
        // 如果类型组为空，移除它
        if (ids.empty()) {
            typeGroups.erase(it);
        }
    }
}

void GameObjectManager::addToTypeGroup(const std::string& type, const std::string& id) {
    typeGroups[type].push_back(id);
}

void GameObjectManager::triggerObjectAddedEvent(GameObjectInterface* obj) {
    for (auto& callback : onObjectAddedCallbacks) {
        callback(obj);
    }
}

void GameObjectManager::triggerObjectRemovedEvent(const std::string& id, const std::string& type) {
    for (auto& callback : onObjectRemovedCallbacks) {
        callback(id, type);
    }
}
