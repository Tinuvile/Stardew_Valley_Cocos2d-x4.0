#include "GameObjectManagerExample.h"
#include "Chicken.h"
#include "Cow.h"
#include "Sheep.h"
#include "cocos2d.h"

USING_NS_CC;

// 外部全局变量
extern int day;
extern std::string Season;
extern std::map<std::string, Crop> cropbasicinformation;

GameObjectManagerExample::GameObjectManagerExample()
    : objectManager(nullptr), currentScene(nullptr) {
    objectManager = new GameObjectManager();
}

GameObjectManagerExample::~GameObjectManagerExample() {
    cleanup();
}

bool GameObjectManagerExample::initialize(cocos2d::Scene* scene) {
    if (!scene || !objectManager) {
        CCLOG("GameObjectManagerExample::initialize - Invalid parameters");
        return false;
    }
    
    currentScene = scene;
    
    // 设置事件回调
    setupEventCallbacks();
    
    // 初始化作物数据
    initializeCropData();
    
    CCLOG("GameObjectManagerExample::initialize - Successfully initialized");
    return true;
}

void GameObjectManagerExample::cleanup() {
    if (objectManager) {
        objectManager->clear();
        delete objectManager;
        objectManager = nullptr;
    }
    currentScene = nullptr;
}

void GameObjectManagerExample::update(float deltaTime) {
    if (objectManager) {
        objectManager->updateAll(deltaTime);
    }
}

// === 示例功能实现 ===

std::string GameObjectManagerExample::createExamplePlayer(const cocos2d::Vec2& position) {
    // 创建玩家对象
    auto player = Player::create();
    if (!player) {
        CCLOG("GameObjectManagerExample::createExamplePlayer - Failed to create player");
        return "";
    }
    
    player->setPosition(position);
    
    // 创建适配器并添加到管理器
    std::string playerId = AdapterFactory::generateId("player");
    auto playerAdapter = AdapterFactory::createPlayerAdapter(player, playerId);
    
    if (objectManager->addObject(std::move(playerAdapter))) {
        // 添加到场景
        if (currentScene) {
            currentScene->addChild(player);
        }
        
        CCLOG("GameObjectManagerExample::createExamplePlayer - Created player with ID: %s", 
              playerId.c_str());
        return playerId;
    }
    
    return "";
}

std::string GameObjectManagerExample::createExampleNPC(const std::string& name, 
                                                      const cocos2d::Vec2& position) {
    // 创建NPC动画帧数据（简化示例）
    std::vector<std::vector<std::string>> animations = {
        {"npc/npc_up1.png", "npc/npc_up2.png"},     // 上
        {"npc/npc_down1.png", "npc/npc_down2.png"}, // 下
        {"npc/npc_left1.png", "npc/npc_left2.png"}, // 左
        {"npc/npc_right1.png", "npc/npc_right2.png"} // 右
    };
    
    std::vector<cocos2d::Vec2> validPositions = {position}; // 简化的有效位置
    
    // 创建NPC对象
    auto npc = new NPC(name, position, animations, validPositions);
    if (!npc) {
        CCLOG("GameObjectManagerExample::createExampleNPC - Failed to create NPC");
        return "";
    }
    
    // 创建适配器并添加到管理器
    std::string npcId = AdapterFactory::generateId("npc");
    auto npcAdapter = AdapterFactory::createNPCAdapter(npc, npcId);
    
    if (objectManager->addObject(std::move(npcAdapter))) {
        // 添加到场景
        if (currentScene) {
            currentScene->addChild(npc);
        }
        
        CCLOG("GameObjectManagerExample::createExampleNPC - Created NPC '%s' with ID: %s", 
              name.c_str(), npcId.c_str());
        return npcId;
    }
    
    return "";
}

std::string GameObjectManagerExample::createExampleCrop(const std::string& cropName, 
                                                       const cocos2d::Vec2& position) {
    // 从全局作物信息中获取作物数据
    auto it = cropbasicinformation.find(cropName);
    if (it == cropbasicinformation.end()) {
        CCLOG("GameObjectManagerExample::createExampleCrop - Unknown crop: %s", cropName.c_str());
        return "";
    }
    
    // 创建作物副本
    auto crop = std::make_shared<Crop>(it->second);
    
    // 创建适配器并添加到管理器
    std::string cropId = AdapterFactory::generateId("crop");
    auto cropAdapter = AdapterFactory::createCropAdapter(crop, cropId, position);
    
    if (objectManager->addObject(std::move(cropAdapter))) {
        CCLOG("GameObjectManagerExample::createExampleCrop - Created crop '%s' with ID: %s", 
              cropName.c_str(), cropId.c_str());
        return cropId;
    }
    
    return "";
}

std::string GameObjectManagerExample::createExampleLivestock(const std::string& species, 
                                                          const cocos2d::Vec2& position,
                                                          const cocos2d::Rect& area) {
    Livestock* livestock = nullptr;
    
    // 根据种类创建不同的家畜
    if (species == "chicken") {
        livestock = Chicken::create(area);
    } else if (species == "cow") {
        livestock = Cow::create(area);
    } else if (species == "sheep") {
        livestock = Sheep::create(area);
    } else {
        CCLOG("GameObjectManagerExample::createExampleLivestock - Unknown species: %s", 
              species.c_str());
        return "";
    }
    
    if (!livestock) {
        CCLOG("GameObjectManagerExample::createExampleLivestock - Failed to create livestock");
        return "";
    }
    
    livestock->setPosition(position);
    
    // 创建适配器并添加到管理器
    std::string livestockId = AdapterFactory::generateId("livestock");
    auto livestockAdapter = AdapterFactory::createLivestockAdapter(livestock, livestockId);
    
    if (objectManager->addObject(std::move(livestockAdapter))) {
        // 添加到场景
        if (currentScene) {
            currentScene->addChild(livestock);
        }
        
        CCLOG("GameObjectManagerExample::createExampleLivestock - Created %s with ID: %s", 
              species.c_str(), livestockId.c_str());
        return livestockId;
    }
    
    return "";
}

std::string GameObjectManagerExample::createExampleTree(const cocos2d::Vec2& position) {
    // 创建树木对象
    auto tree = std::make_shared<Tree>("Oak Tree", "Tree/oak_normal.png", "Tree/oak_cut.png", 
                                      "Tree/oak_young.png", 50, 3, position);
    
    // 创建适配器并添加到管理器
    std::string treeId = AdapterFactory::generateId("tree");
    auto treeAdapter = AdapterFactory::createTreeAdapter(tree, treeId);
    
    if (objectManager->addObject(std::move(treeAdapter))) {
        CCLOG("GameObjectManagerExample::createExampleTree - Created tree with ID: %s", 
              treeId.c_str());
        return treeId;
    }
    
    return "";
}

std::string GameObjectManagerExample::createExampleOre(const cocos2d::Vec2& position) {
    // 创建矿石对象
    auto ore = std::make_shared<Ore>("Iron Ore", "Ore/iron_normal.png", "Ore/iron_mined.png", 
                                    100, 5, position);
    
    // 创建适配器并添加到管理器
    std::string oreId = AdapterFactory::generateId("ore");
    auto oreAdapter = AdapterFactory::createOreAdapter(ore, oreId);
    
    if (objectManager->addObject(std::move(oreAdapter))) {
        CCLOG("GameObjectManagerExample::createExampleOre - Created ore with ID: %s", 
              oreId.c_str());
        return oreId;
    }
    
    return "";
}

// === 演示功能实现 ===

void GameObjectManagerExample::demonstrateCollisionDetection() {
    CCLOG("=== Collision Detection Demo ===");
    
    auto collisions = objectManager->checkAllCollisions();
    for (auto& collision : collisions) {
        CCLOG("Collision detected: %s <-> %s", 
              collision.first->getName().c_str(),
              collision.second->getName().c_str());
    }
    
    if (collisions.empty()) {
        CCLOG("No collisions detected");
    }
}

void GameObjectManagerExample::demonstrateRangeQuery(const cocos2d::Vec2& center, float radius) {
    CCLOG("=== Range Query Demo (Center: %.1f,%.1f Radius: %.1f) ===", 
          center.x, center.y, radius);
    
    auto objects = objectManager->getObjectsInRange(center, radius);
    for (auto obj : objects) {
        CCLOG("Found object: %s (%s) at %.1f,%.1f", 
              obj->getName().c_str(), obj->getType().c_str(),
              obj->getPosition().x, obj->getPosition().y);
    }
    
    if (objects.empty()) {
        CCLOG("No objects found in range");
    }
}

void GameObjectManagerExample::demonstrateInteraction(const cocos2d::Vec2& playerPos) {
    CCLOG("=== Interaction Demo (Player at: %.1f,%.1f) ===", playerPos.x, playerPos.y);
    
    auto interactableObjects = objectManager->getInteractableObjects(playerPos, 60.0f);
    for (auto obj : interactableObjects) {
        CCLOG("Can interact with: %s - %s", 
              obj->getName().c_str(), obj->getInteractionHint().c_str());
    }
    
    if (interactableObjects.empty()) {
        CCLOG("No interactable objects nearby");
    }
}

void GameObjectManagerExample::demonstrateDayPass() {
    CCLOG("=== Day Pass Demo (Day %d -> Day %d) ===", day, day + 1);
    
    day++; // 增加天数
    objectManager->broadcastDayPass();
    
    CCLOG("Day pass event broadcasted to all objects");
}

void GameObjectManagerExample::demonstrateSeasonChange(const std::string& newSeason) {
    CCLOG("=== Season Change Demo (%s -> %s) ===", Season.c_str(), newSeason.c_str());
    
    Season = newSeason;
    objectManager->broadcastSeasonChange(newSeason);
    
    CCLOG("Season change event broadcasted to all objects");
}

void GameObjectManagerExample::demonstrateObjectStats() {
    CCLOG("=== Object Statistics Demo ===");
    
    auto stats = objectManager->getObjectStats();
    for (auto& pair : stats) {
        CCLOG("Type: %s, Count: %d", pair.first.c_str(), pair.second);
    }
    
    CCLOG("Total objects: %zu", objectManager->getObjectCount());
}

void GameObjectManagerExample::createFarmSceneExample() {
    CCLOG("=== Creating Farm Scene Example ===");
    
    // 创建玩家
    createExamplePlayer(Vec2(400, 300));
    
    // 创建一些作物
    createExampleCrop("wheat", Vec2(200, 200));
    createExampleCrop("corn", Vec2(220, 200));
    createExampleCrop("potato", Vec2(240, 200));
    
    // 创建家畜
    createExampleLivestock("chicken", Vec2(500, 200), Rect(450, 150, 100, 100));
    createExampleLivestock("cow", Vec2(600, 200), Rect(550, 150, 100, 100));
    
    // 创建树木和矿石
    createExampleTree(Vec2(100, 400));
    createExampleOre(Vec2(700, 400));
    
    // 添加到场景渲染
    if (currentScene) {
        objectManager->addToScene(currentScene);
    }
    
    CCLOG("Farm scene created with %zu objects", objectManager->getObjectCount());
}

void GameObjectManagerExample::createTownSceneExample() {
    CCLOG("=== Creating Town Scene Example ===");
    
    // 创建玩家
    createExamplePlayer(Vec2(400, 300));
    
    // 创建NPC
    createExampleNPC("Shopkeeper", Vec2(200, 300));
    createExampleNPC("Mayor", Vec2(600, 300));
    createExampleNPC("Blacksmith", Vec2(400, 500));
    
    // 添加到场景渲染
    if (currentScene) {
        objectManager->addToScene(currentScene);
    }
    
    CCLOG("Town scene created with %zu objects", objectManager->getObjectCount());
}

// === 工具方法实现 ===

void GameObjectManagerExample::printAllObjects() const {
    CCLOG("=== All Objects List ===");
    
    auto stats = objectManager->getObjectStats();
    for (auto& pair : stats) {
        auto objects = objectManager->getObjectsByType(pair.first);
        CCLOG("--- %s Objects (%d) ---", pair.first.c_str(), (int)objects.size());
        
        for (auto obj : objects) {
            CCLOG("  %s: %s at (%.1f,%.1f)", 
                  obj->getId().c_str(), obj->getName().c_str(),
                  obj->getPosition().x, obj->getPosition().y);
        }
    }
}

bool GameObjectManagerExample::validateSystem() const {
    if (!objectManager) {
        CCLOG("GameObjectManagerExample::validateSystem - Object manager is null");
        return false;
    }
    
    bool isValid = objectManager->validateIntegrity();
    CCLOG("GameObjectManagerExample::validateSystem - System integrity: %s", 
          isValid ? "VALID" : "INVALID");
    
    return isValid;
}

// === 私有方法实现 ===

void GameObjectManagerExample::setupEventCallbacks() {
    if (!objectManager) return;
    
    // 设置对象添加事件回调
    objectManager->onObjectAdded([](GameObjectInterface* obj) {
        CCLOG("Event: Object added - %s (%s)", obj->getName().c_str(), obj->getType().c_str());
    });
    
    // 设置对象移除事件回调
    objectManager->onObjectRemoved([](const std::string& id, const std::string& type) {
        CCLOG("Event: Object removed - %s (%s)", id.c_str(), type.c_str());
    });
}

void GameObjectManagerExample::initializeCropData() {
    // 这里初始化一些基础作物数据，如果全局数据为空的话
    if (cropbasicinformation.empty()) {
        cropbasicinformation.emplace("wheat", 
            Crop("wheat", "Crops/wheat1.png", "Crops/wheat2.png", "Crops/wheat3.png", 
                 "All", Phase::SEED, 50, 0, false, 4));
        cropbasicinformation.emplace("corn", 
            Crop("corn", "Crops/corn1.png", "Crops/corn2.png", "Crops/corn3.png", 
                 "Spring", Phase::SEED, 50, 0, false, 6));
        cropbasicinformation.emplace("potato", 
            Crop("potato", "Crops/potato1.png", "Crops/potato2.png", "Crops/potato3.png", 
                 "All", Phase::SEED, 30, 0, false, 2));
        
        CCLOG("GameObjectManagerExample::initializeCropData - Initialized crop data");
    }
}
