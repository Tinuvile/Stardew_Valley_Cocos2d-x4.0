#pragma once
#include "../GameObjectInterface.h"
#include "../Player.h"
#include "cocos2d.h"
#include <string>

/**
 * Player类的适配器
 * 将Player对象适配到统一的GameObjectInterface接口
 */
class PlayerAdapter : public GameObjectInterface {
private:
    Player* player;
    std::string id;
    bool isActiveFlag;
    float interactionRange;
    
public:
    /**
     * 构造函数
     * @param playerPtr 玩家对象指针
     * @param objectId 对象ID
     */
    PlayerAdapter(Player* playerPtr, const std::string& objectId);
    
    /**
     * 析构函数
     */
    virtual ~PlayerAdapter() = default;

    // === 基础属性实现 ===
    std::string getId() const override { return id; }
    std::string getType() const override { return "Player"; }
    std::string getName() const override { return "Player"; }

    // === 位置管理实现 ===
    cocos2d::Vec2 getPosition() const override;
    void setPosition(const cocos2d::Vec2& pos) override;
    cocos2d::Rect getBounds() const override;

    // === 渲染相关实现 ===
    cocos2d::Node* getRenderNode() const override;
    void updateTexture(float deltaTime) override;
    bool isVisible() const override;
    void setVisible(bool visible) override;

    // === 生命周期管理实现 ===
    void update(float deltaTime) override;
    bool isActive() const override { return isActiveFlag && player != nullptr; }
    void setActive(bool active) override { isActiveFlag = active; }
    void cleanup() override;

    // === 交互能力实现 ===
    bool canInteract() const override { return true; }
    void onInteract(GameObjectInterface* interactor = nullptr) override;
    std::string getInteractionHint() const override { return "Player"; }

    // === 移动能力实现 ===
    bool canMove() const override { return true; }
    float getMovementSpeed() const override;
    void moveTo(const cocos2d::Vec2& target) override;
    void randomMove() override {} // 玩家不执行随机移动
    void stopMovement() override;

    // === 库存管理能力实现 ===
    bool hasInventory() const override { return true; }
    bool canStore(std::shared_ptr<class Item> item) const override;
    bool addItem(std::shared_ptr<class Item> item) override;
    std::shared_ptr<class Item> removeItem(const std::string& itemName) override;
    std::vector<std::shared_ptr<class Item>> getInventoryItems() const override;

    // === 状态查询实现 ===
    std::string getStatusText() const override;
    float getHealth() const override { return 1.0f; } // 玩家默认满血
    void setHealth(float health) override {} // 当前版本不支持生命值

    // === 事件回调实现 ===
    void onCollisionEnter(GameObjectInterface* other) override;
    void onCollisionExit(GameObjectInterface* other) override;
    void onDayPass() override;
    void onSeasonChange(const std::string& newSeason) override;

    // === 玩家特有方法 ===
    
    /**
     * 获取玩家移动状态
     * @param direction 方向 (0=上, 1=下, 2=左, 3=右)
     * @return 是否在该方向移动
     */
    bool getMovementState(int direction) const;
    
    /**
     * 设置玩家移动状态
     * @param direction 移动方向
     * @param isPressed 是否按下
     */
    void setMovementState(Player::MovementDirection direction, bool isPressed);
    
    /**
     * 获取玩家当前朝向
     * @return 朝向状态
     */
    int getLookState() const;
    
    /**
     * 设置交互范围
     * @param range 交互范围（像素）
     */
    void setInteractionRange(float range) { interactionRange = range; }
    
    /**
     * 获取交互范围
     * @return 交互范围
     */
    float getInteractionRange() const { return interactionRange; }
    
    /**
     * 检查是否可以与指定位置的对象交互
     * @param targetPos 目标位置
     * @return 是否在交互范围内
     */
    bool canInteractWith(const cocos2d::Vec2& targetPos) const;
    
    /**
     * 获取原始Player对象指针
     * @return Player对象指针
     */
    Player* getPlayerPtr() const { return player; }

private:
    /**
     * 更新玩家动画状态
     */
    void updateAnimation();
    
    /**
     * 检查玩家是否在移动
     * @return 是否在移动
     */
    bool isMoving() const;
};
