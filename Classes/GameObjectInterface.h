#pragma once
#include "cocos2d.h"
#include <string>
#include <memory>

/**
 * 统一的游戏对象接口
 * 使用适配器模式为不同类型的游戏对象提供一致的接口
 */
class GameObjectInterface {
public:
    virtual ~GameObjectInterface() = default;

    // === 基础属性 ===
    virtual std::string getId() const = 0;
    virtual std::string getType() const = 0;
    virtual std::string getName() const = 0;

    // === 位置管理 ===
    virtual cocos2d::Vec2 getPosition() const = 0;
    virtual void setPosition(const cocos2d::Vec2& pos) = 0;
    virtual cocos2d::Rect getBounds() const = 0;

    // === 渲染相关 ===
    virtual cocos2d::Node* getRenderNode() const = 0;
    virtual void updateTexture(float deltaTime) = 0;
    virtual bool isVisible() const = 0;
    virtual void setVisible(bool visible) = 0;

    // === 生命周期管理 ===
    virtual void update(float deltaTime) = 0;
    virtual bool isActive() const = 0;
    virtual void setActive(bool active) = 0;
    virtual void cleanup() = 0;

    // === 交互能力 ===
    virtual bool canInteract() const = 0;
    virtual void onInteract(class GameObjectInterface* interactor = nullptr) = 0;
    virtual std::string getInteractionHint() const = 0;

    // === 可选能力接口 ===
    
    // 移动能力
    virtual bool canMove() const { return false; }
    virtual float getMovementSpeed() const { return 0.0f; }
    virtual void moveTo(const cocos2d::Vec2& target) {}
    virtual void randomMove() {}
    virtual void stopMovement() {}

    // 生产能力  
    virtual bool canProduce() const { return false; }
    virtual bool isReadyToProduce() const { return false; }
    virtual std::shared_ptr<class Item> produce() { return nullptr; }
    virtual float getProductionProgress() const { return 0.0f; }

    // 收获能力
    virtual bool isHarvestable() const { return false; }
    virtual std::shared_ptr<class Item> harvest() { return nullptr; }
    virtual bool requiresTool() const { return false; }
    virtual std::string getRequiredTool() const { return ""; }

    // 成长能力
    virtual bool canGrow() const { return false; }
    virtual float getGrowthProgress() const { return 0.0f; }
    virtual void water() {}
    virtual bool needsWater() const { return false; }
    virtual void advanceGrowth() {}

    // 库存管理能力
    virtual bool hasInventory() const { return false; }
    virtual bool canStore(std::shared_ptr<class Item> item) const { return false; }
    virtual bool addItem(std::shared_ptr<class Item> item) { return false; }
    virtual std::shared_ptr<class Item> removeItem(const std::string& itemName) { return nullptr; }
    virtual std::vector<std::shared_ptr<class Item>> getInventoryItems() const { 
        return std::vector<std::shared_ptr<class Item>>(); 
    }

    // 对话能力
    virtual bool canTalk() const { return false; }
    virtual std::vector<std::string> getDialogOptions() const { 
        return std::vector<std::string>(); 
    }
    virtual void startDialog() {}

    // 状态查询
    virtual std::string getStatusText() const { return ""; }
    virtual float getHealth() const { return 1.0f; }
    virtual void setHealth(float health) {}
    
    // 序列化支持
    virtual std::string serialize() const { return ""; }
    virtual bool deserialize(const std::string& data) { return false; }

    // 事件回调
    virtual void onCollisionEnter(GameObjectInterface* other) {}
    virtual void onCollisionExit(GameObjectInterface* other) {}
    virtual void onDayPass() {}
    virtual void onSeasonChange(const std::string& newSeason) {}
};

/**
 * 游戏对象类型枚举
 */
enum class GameObjectType {
    PLAYER,
    NPC, 
    CROP,
    LIVESTOCK,
    TREE,
    ORE,
    FISH,
    BUILDING,
    ITEM_ON_GROUND,
    UNKNOWN
};

/**
 * 辅助函数：将类型枚举转换为字符串
 */
inline std::string gameObjectTypeToString(GameObjectType type) {
    switch (type) {
        case GameObjectType::PLAYER: return "Player";
        case GameObjectType::NPC: return "NPC";
        case GameObjectType::CROP: return "Crop";
        case GameObjectType::LIVESTOCK: return "Livestock";
        case GameObjectType::TREE: return "Tree";
        case GameObjectType::ORE: return "Ore";
        case GameObjectType::FISH: return "Fish";
        case GameObjectType::BUILDING: return "Building";
        case GameObjectType::ITEM_ON_GROUND: return "ItemOnGround";
        default: return "Unknown";
    }
}
